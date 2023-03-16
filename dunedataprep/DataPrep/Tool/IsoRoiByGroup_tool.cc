#include "IsoRoiByGroup.h"

#include "dunecore/ArtSupport/DuneToolManager.h"
#include "dunecore/DuneInterface/Data/IndexRange.h"
#include "dunecore/DuneInterface/Data/IndexRangeGroup.h"
#include "dunecore/DuneInterface/Tool/IndexRangeGroupTool.h"
#include <iostream>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;
using std::setw;

//
// Ctor
IsoRoiByGroup::IsoRoiByGroup(fhicl::ParameterSet const& ps)
: m_LogLevel(ps.get<int>("LogLevel")),
  m_Groups(ps.get<NameVector>("Groups")),
  m_NchEz(ps.get<Index>("NChanEz")),
  m_NtickEz(ps.get<Index>("NTickEz")) {
  
  //
  const string myname = "IsoRoiByGroup::ctor: ";

  // Build the channel map from options.
  string crtName = "channelGroups";
  DuneToolManager* ptm = DuneToolManager::instance();
  const IndexRangeGroupTool* pcrt = ptm == nullptr ? nullptr : ptm->getShared<IndexRangeGroupTool>(crtName);
  int nerr = 0;
  for ( Name sgrp : m_Groups ) {
    IndexRangeGroup grp;
    if ( pcrt != nullptr ) grp = pcrt->get(sgrp);
    if ( ! grp.isValid() ) {
      grp = IndexRangeGroup(sgrp);
    }
    if ( ! grp.isValid() || grp.name.size() == 0 ) {
      cout << myname << "WARNING: Unable to find range group " << sgrp << endl;
      ++nerr;
    } else {
      grp.getIndices(m_chg[grp.name]);
    }
  }
  if ( nerr ) {
    if ( pcrt == nullptr ) {
      cout << myname << "Channel groups tool " << crtName << " was not found." << endl;
    } else {
      cout << myname << "Channel groups tool " << crtName << " listing:" << endl;
      pcrt->get("list");
    }
  }

  // Log the configuration.
  if ( m_LogLevel >= 1 ) {
    cout << myname << "  LogLevel: " << m_LogLevel << endl;
    cout << myname << "    Groups: [";
    int count = 0;
    for ( Name nam : m_Groups ) {
      if ( count && count%10 == 0 ) cout << "\n" + myname + "             ";
      if ( count++ ) cout << ", ";
      cout << nam;
    }
    cout << "]" << endl;
    
    if ( m_chg.size() ) {
      cout << myname << "     Group   #chan" << endl;
      for ( const auto& ient : m_chg ) {
        cout << myname << setw(10) << ient.first << setw(8) << ient.second.size() << endl;
      }
    } else {
      cout << myname << "No channel groups found." << endl;
    }
    cout<<myname<<"Channel exclusion zone : "<<m_NchEz<<endl;
    cout<<myname<<"Tick exclusion zone    : "<<m_NtickEz<<endl;
  }
}

//
//
DataMap IsoRoiByGroup::updateMap(AdcChannelDataMap& acds) const {
  const string myname = "IsoRoiByGroup::updateMap: ";
  DataMap ret;
  
  if ( acds.size() == 0 ) {
    cout << myname << "WARNING: No channels found." << endl;
    return ret.setStatus(1);
  }

  std::map<Name, int> stats;
  for ( const auto& entry : m_chg ) {   
    stats[entry.first] = 0;
    const IndexVector& channels = entry.second;
    if( channels.size() < 2 * m_NchEz ){
      cout<<myname<< "WARNING: not enough channels in group "<<entry.first<<endl;
      continue;
    }
    auto isorois = buildIsodepRois(channels, acds);
    for(Index ich : channels){
      auto iacd = acds.find(ich);
      if ( iacd == acds.end() ) continue;
      AdcChannelData& acd = iacd->second;
      if ( acd.samples.size() == 0 ) continue;

      Index nsa = acd.samples.size();
      acd.signal.clear();
      acd.signal.resize(nsa, false);
      auto irois = isorois.find(ich);
      if( irois == isorois.end() ) continue;
      //cout<<entry.first<<" "<<ich<<" "<<nsa<<" "<<irois->second.size()<<endl;
      acd.signal = buildFilterVector(nsa, irois->second);
      stats[entry.first] += irois->second.size();
      acd.roisFromSignal();
    }
  }
  
  if( m_LogLevel >= 2 ){
    cout << myname << "     Group   #ROIs" << endl;
    for ( const auto& ient : stats ) {
      cout << myname << setw(10) << ient.first << setw(8) << ient.second << endl;
    }    
  }
  
  for ( const auto& ient : stats ) {
    Name s = "nisoroi_" + ient.first;
    ret.setInt(s, ient.second );
  }
  
  return ret;
}


//
//
IsoRoiByGroup::AdcRoiMap 
IsoRoiByGroup::buildIsodepRois( const IndexVector& channels, 
				const AdcChannelDataMap& acds) const
{
  const string myname = "IsoRoiByGroup::buildIsodepRois: ";
  //
  Index nch = channels.size();
  std::vector<AdcRoiVector> rois(nch);
  std::vector<AdcRoiVector> rois_selected(nch);
  std::vector<Index>        nsam(nch);
  Index count_rois1 = 0;
  for( Index idx=0;idx<nch;++idx){
    Index ich = channels[idx];
    auto iacd = acds.find( ich );
    if( iacd == acds.end() ) {
      continue;
    }
    auto const &acd = iacd->second;
    rois[idx] = acd.rois;
    nsam[idx] = acd.samples.size();
    count_rois1 += rois[idx].size();
  }
  
  Index ich_start = m_NchEz;
  Index ich_end   = nch - m_NchEz + 1;
  for( Index ich = ich_start;ich<ich_end;++ich ){
    if( rois[ich].empty() ) continue;
    if( nsam[ich] < 2 * m_NtickEz ) continue;
    Index nsa           = nsam[ich];
    Index ch_loop_start = (ich<m_NchEz)?0:(ich-m_NchEz);
    Index ch_loop_end   = ich + m_NchEz + 1;
    if(ch_loop_end > nch ) ch_loop_end = nch;

    for(const auto &roi : rois[ich] ){
      //
      Index trstart = roi.first;
      Index trend   = roi.second;
      // too close to start of readout window
      if( trstart < m_NtickEz ) continue; // onto next ROI ...

      Index tlo = (trstart < m_NtickEz)?0:(trstart - m_NtickEz);
      Index thi = trend + m_NtickEz;
      
      // too close to end of readout window
      if( thi > nsa ) continue; //

      // this channel
      bool keep     = true;
      for( auto const &rroi: rois[ich] ){
	// skip current ROI on this wire
	if( rroi.first == trstart ) continue;
	// no overlaps
        keep = rroi.second < tlo || rroi.first > thi;
	if( !keep ){
	  break;
	}
      }
      if( !keep ) continue; // onto next ROI ...
      
      // check other nearby channels
      for(Index iich=ch_loop_start;iich<ch_loop_end;++iich){
	if( iich == ich ) continue; // this channel
	if( rois[iich].empty() ) continue;
	// loop over rois for other channels
	for( auto const &rroi: rois[iich] ){
	  keep = rroi.second < tlo || rroi.first > thi;
	  if( !keep ) break;
	}
	if( !keep ) break; 	
      }
      if( !keep ) continue;
      
      // save this roi
      rois_selected[ich].push_back( roi );
    } //loop over channels rois
  } // loop over channels

  AdcRoiMap roimap;
  Index count_rois2 = 0;
  for( Index idx = 0;idx<nch;++idx ){
    if( rois_selected[idx].empty() ) continue;
    roimap.insert(std::pair( channels[idx], rois_selected[idx] ) );
    count_rois2 += rois_selected[idx].size();
  }
  
  if( m_LogLevel >= 3 ){
    cout<<myname<<"out of "<<count_rois1<<" ROIs kept "<<count_rois2<<endl;
  }
  return roimap;
}

//
AdcFilterVector IsoRoiByGroup::buildFilterVector(Index nsam, AdcRoiVector rois ) const {
  //std::vector<bool> 
  AdcFilterVector sig(nsam,false);
  for( auto const &r : rois ){
    std::fill( sig.begin()+r.first, sig.begin()+r.second+1, true );
  }
 
  return sig;
}

DEFINE_ART_CLASS_TOOL(IsoRoiByGroup)
