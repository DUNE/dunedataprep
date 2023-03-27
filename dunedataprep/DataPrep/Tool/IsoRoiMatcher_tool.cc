#include "IsoRoiMatcher.h"

#include "canvas/Utilities/Exception.h"
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

namespace {
  template<typename T>
  void unpackStrOpts( const string &stropt, std::vector<T> &opts ) {
    
    string str1 = stropt;
    string str2 = "";
    auto ipos = stropt.find(":");
    if( ipos != string::npos ){
      str1 = stropt.substr(0, ipos);
      str2 = stropt.substr(ipos + 1);
    }

    std::stringstream ss(str1);
    T tmp;
    if( (ss >> tmp).fail() ){
      cout<<"could not parse the option\n";
    }
    else {
      opts.push_back( tmp );
    }
    if( !str2.empty() ) 
      unpackStrOpts<T>( str2, opts );
  
    return;
  }
}


//
// Ctor
IsoRoiMatcher::IsoRoiMatcher(fhicl::ParameterSet const& ps)
: m_LogLevel(ps.get<int>("LogLevel"))
{
  const string myname = "IsoRoiMatcher::ctor: ";

  NameVector gsets = ps.get<NameVector>("GroupSets");
  m_MaxTDelta = ps.get<int>("MaxTDelta");
  m_MaxDist   = ps.get<float>("MaxDist");
  m_AlignMode = ps.get<string>("AlignMode");
  m_NRoiPreSamples = ps.get<Index>("NRoiPreSamples");
  m_NRoiTotSamples = ps.get<Index>("NRoiTotSamples");

  // detector channel info from geo service
  m_DetChInfo = std::make_unique<DetChInfo>(m_LogLevel);
  if( m_DetChInfo->getNRops() != 3 ){
    throw art::Exception(art::errors::Configuration, "Geometry with number of readout planes other 3 is currently not supported by this tool");
  }
  
  buildChGroupSets( gsets );
  buildInterceptsMap( );
  
  // Log the configuration.
  if ( m_LogLevel >= 1 ) {
    cout << myname << "  LogLevel: " << m_LogLevel << endl;
    cout << myname << "    Group sets: [";
    int count = 0;
    for ( Name nam : gsets ) {
      if ( count && count%10 == 0 ) cout << "\n" + myname + "             ";
      if ( count++ ) cout << ", ";
      cout << nam;
    }
    cout << "]" << endl;
    
    if ( m_GroupSets.size() ) {
      for( auto const gset : m_GroupSets ){
	cout << myname << "     Group   #chan" << endl;
	for ( const auto& ient : gset ) {
	  cout << myname << setw(10) << ient.name << setw(3) << ient.ropid
	       << setw(8) << ient.channels.size() << endl;
	}
      } 
    }
    else {
      cout << myname << "No channel groups found." << endl;
    }
    cout<<myname<<"  Tick search window for matching : "<<m_MaxTDelta<<endl;
    cout<<myname<<"  Distance to accept intercepts   : "<<m_MaxDist<<endl;
    cout<<myname<<"  Tick alignment mode             : "<<m_AlignMode<<endl;
    cout<<myname<<"  Number of ROI presamples        : "<<m_NRoiPreSamples<<endl;
    cout<<myname<<"  Number of total ROI samples     : "<<m_NRoiTotSamples<<endl;
  }
  
  // loop over intercept maps
  //int debug = 0;
  for( auto const gset : m_GroupSets ){
    auto const &col   = gset.back();
    auto const &chans = col.channels;
    for( auto const &ch: chans ){ // loop over collection channels
      for( size_t idx=0;idx<m_ChIntercepts.size();++idx ){
	//this ROP intercepts for a given collection channel
	auto it = m_ChIntercepts[idx].find( ch );
	if( it == m_ChIntercepts[idx].end() ){
	  cout<<myname<<"WARNING no intercept of "<<ch<<" with ROPID "<<idx<<endl;
	  continue;
	}
	//if( debug < 2 ){
	//auto const &pnts = it->second;
	//cout<<ch<<" "<<idx<<" "<<pnts<<endl;
	//debug++;
	//}
      } // loop over ROPs
    } // loop over collection channels in set
  }//loop over sets
  
  //
}


//
DataMap IsoRoiMatcher::updateMap(AdcChannelDataMap& acds) const {
  const string myname = "IsoRoiMatcher::updateMap: ";
  DataMap ret;
  
  //m_MatchedIsoRois.clear();
  if ( acds.size() == 0 ) {
    cout << myname << "WARNING: No channels found." << endl;
    return ret.setStatus(1);
  }

  size_t nrops = m_DetChInfo->getNRops();
  if( nrops < 2 ){ 
    cout<<myname<<"ERROR: too few ROPs.\n";
    return ret.setStatus(1);
  }
  
  // number of "other" planes
  size_t nsrops = m_ChIntercepts.size();
  if( nsrops != 2 ){ //should not happen at this stage ...
    cout<<myname<<"ERROR: number of induction views other than 2 is not supported\n";
    return ret.setStatus(1);
  }

  //
  //ChRoiVector2d matched_iso_rois;
  ChRoiVector2d m_MatchedIsoRois;
  for( auto const gset : m_GroupSets ){
    if( gset.size() != nsrops + 1 ){
      cout<<myname<<"ERROR : bad number of channel groups : "<<gset.size()<<endl;
      continue;
    }
    try {
      auto const &col   = gset.back();
      auto rois_col     = buildRoisFrame( col.channels, acds );
      ChRoiVector2d rois_inds(nsrops);
      for(Index idx = 0; idx < nsrops; ++idx ){
	rois_inds[idx] = buildRoisFrame( gset[idx].channels, acds );
      }
      
      // match collection to induction views
      for( auto const &roi_col : rois_col ){
	ChRoiVector2d rois_matched(nsrops);
	int nomatch = 0;
	cout<<roi_col.chan<<" "<<roi_col.rid<<" "
	    <<roi_col.tstart<<" "<<roi_col.tend<<" "<<roi_col.inuse<<endl;
	for(Index idx = 0; idx < nsrops; ++idx ){
	  rois_matched[idx] = findRoiMatch( roi_col, rois_inds[idx], 
					    m_ChIntercepts[idx] );
	  if( rois_matched[idx].empty() ) nomatch++;
	  if( !rois_matched[idx].empty() ){
	    //cout<<roi_col.chan<<" "<<roi_col.rid<<" "
	    //<<roi_col.tstart<<" "<<roi_col.tend<<" "<<roi_col.inuse<<endl;
	    cout<<"  -> Match "<<idx<<" "<<rois_matched[idx].size();
	    for( const auto &tmproi : rois_matched[idx] ){
	      cout<<" "<<tmproi.chan<<" "<<tmproi.rid<<" "<<tmproi.tstart<<" "<<tmproi.tend;
	    }
	    cout<<endl;
	  }
	}
	if( nomatch ) continue;

	// match found intercepts
	ChRoiVector aMatch = findRoiVecMatch( rois_matched.front(), rois_matched.back() );
	if( aMatch.empty() ) continue;
	// flag these ROIs as used
	for( Index idx=0;idx<aMatch.size();++idx ){
	  Index idx_roi = aMatch[idx].rid;
	  rois_inds[idx][idx_roi].inuse++;
	}
	
	// add collection ROI 
	ChRoi aCol = roi_col;
	aCol.ipnts = aMatch.back().ipnts;
	aMatch.push_back( aCol );
	// set the roi index for the entire group
	//for( auto &aRoi: aMatch ){ aRoi.rid = m_MatchedIsoRois.size(); }
	bool rval = doCenterAndCrop( aMatch, acds );
	if( not rval ) continue;
	// add it ...
	m_MatchedIsoRois.push_back( aMatch );
      }// collection channels in a given group
     
    } catch (...) { // try block exception
      cout<<myname<<"Exception in ROI matching block"<<endl;
    }
  }//loop over groups

  // reset all rois in specified channels
  /*
  for( auto &[ch, acd] : acds ){
    if ( acd.samples.size() == 0 ) continue;
    Index nsa = acd.samples.size();
    acd.signal.clear();
    acd.signal.resize(nsa, false);
  }
  */    
  
  for( auto const &gset : m_GroupSets ){
    for ( auto const &ient : gset ) {
      for ( Index ch : ient.channels ){
	auto iacd = acds.find(ch);
	if ( iacd == acds.end() ) continue;
	AdcChannelData& acd = iacd->second;
	if ( acd.samples.size() == 0 ) continue;
	
	Index nsa = acd.samples.size();
	acd.signal.clear();
	acd.signal.resize(nsa, false);
	acd.roisFromSignal();
      }
    }
  }
  
  // copy matched ROIs
  for(auto const &amatch: m_MatchedIsoRois ){
    for( auto const &aroi: amatch ){
      Index ch = aroi.chan;
      Index ts = aroi.tstart;
      Index te = aroi.tend;
      cout<<" "<<aroi.rid<<" "<<aroi.chan<<" "<<aroi.tstart;
      auto iacd = acds.find(ch);
      if ( iacd == acds.end() ) continue;
      AdcChannelData& acd = iacd->second;
      if ( acd.samples.size() == 0 ) continue;
	
      Index nsa = acd.samples.size();
      AdcFilterVector sig(nsa,false);
      std::fill( sig.begin()+ts, sig.begin()+te, true );
      acd.signal = sig;
      acd.roisFromSignal();
    }
    cout<<endl;
  }
  if( m_LogLevel >= 2 ){
    cout << myname << "     Number of grouped ROIs : " << m_MatchedIsoRois.size()<< endl;
  }

  
  ret.setInt("nroi_matched", m_MatchedIsoRois.size() );
  return ret;
}


//
IsoRoiMatcher::ChRoiVector 
IsoRoiMatcher::buildRoisFrame(const IndexVector& channels, const AdcChannelDataMap& acds) const {
  ChRoiVector chrois;
  for( auto const &ch : channels ){
    auto iacd = acds.find( ch );
    if( iacd == acds.end() ) {
      continue;
    }
    auto const &acd = iacd->second;
    for( auto const &roi: acd.rois ){
      Index tstart = roi.first;
      Index tend   = roi.second;
      auto const it_start = acd.samples.begin() + tstart;
      auto const it_end   = acd.samples.begin() + tend;
      // find max value in ROI
      auto it_max = std::max_element( it_start, it_end );
      Index tmax  = std::distance(std::begin(acd.samples), it_max);
      // find min value in the range max to end of ROI
      auto it_min = std::min_element( it_max, it_end );
      Index tmin  = std::distance(std::begin(acd.samples), it_min);

      //
      ChRoi chroi;
      chroi.chan   = ch;
      chroi.rid    = chrois.size();
      chroi.tstart = tstart;
      chroi.tend   = tend;
      chroi.tmax   = tmax;
      chroi.tmin   = tmin;
      //chroi.psum   = std::accumulate( it_start, it_end, 0.0 ); 
      //chroi.pheight = *it_max;
      chroi.inuse  = 0;
      chrois.push_back( chroi );
    } // channel rois
  }//channels

  return chrois;
}

IsoRoiMatcher::ChRoiVector 
IsoRoiMatcher::findRoiMatch( const ChRoi &col_roi, 
			     const ChRoiVector &ind_rois, 
			     const ChInterceptsMap &intercepts ) const {
  // simply loop over the hit channels in other rois 
  // not very efficient, but clear ...

  const string myname = "IsoRoiMatcher::findRoiMatch: ";
  ChRoiVector matched_rois;
  
  auto it = intercepts.find( col_roi.chan );
  if( it == intercepts.end() ){
    cout<<myname<<"WARNING: could not find intercepts for col channel "<<col_roi.chan<<endl;
    return matched_rois;
  }
  
  int absMaxTDelta = std::abs(m_MaxTDelta);

  // intercepts with induction channel
  auto const &ind_ints = it->second;
  // loop over the induction ROIs
  for( auto const &ind_roi : ind_rois ){
    // skip ROIs already assigned
    if( ind_roi.inuse ) continue;

    // check that this channel intercept is valid
    auto pnts = ind_ints.get( ind_roi.chan );
    if( pnts.empty() ) continue; // no intercepts with this channel
    
    // required some overlap between rois
    bool no_overlap = col_roi.tend < ind_roi.tstart || col_roi.tstart > ind_roi.tend;
    if( no_overlap ) continue;
    
    // check if pulse height is within MaxTDelta
    int tdiff = (int)ind_roi.tmax - (int)col_roi.tmax;
    if( std::abs(tdiff) > absMaxTDelta ) continue;
    // if MaxTDelta is negative require induction pulse to be before collection
    if( m_MaxTDelta < 0 && tdiff > 0 ) continue;
    
    //
    ChRoi matched_roi = ind_roi;
    matched_roi.ipnts = pnts;
    matched_rois.push_back( matched_roi );
  }
  
  return matched_rois;
}

//
IsoRoiMatcher::ChRoiVector 
IsoRoiMatcher::findRoiVecMatch( const ChRoiVector &rois1, const ChRoiVector &rois2 ) const {
  const string myname = "IsoRoiMatcher::findRoiVecMatch: ";

  // loop over the points of each ROI and find the pair with closest distance
  Index badidx = std::numeric_limits<Index>::max();
  Index iroi1  = badidx;
  Index ipnt1  = badidx;
  Index iroi2  = badidx;
  Index ipnt2  = badidx;
  float dmin   = std::numeric_limits<float>::max();

  for( Index idx1 = 0; idx1<rois1.size(); ++idx1 ){
    auto const &pnts1 = rois1[idx1].ipnts;
    for( Index idx_pnt1 = 0;idx_pnt1 < pnts1.size(); ++idx_pnt1){
      auto const &pnt1 = pnts1[idx_pnt1];
      //
      for( Index idx2 = 0; idx2<rois2.size(); ++idx2 ){
	auto const pnts2 = rois2[idx2].ipnts;
	for( Index idx_pnt2 = 0;idx_pnt2 < pnts2.size(); ++idx_pnt2){
	  auto const &pnt2 = pnts2[idx_pnt2];
	  auto delta = pnt1 - pnt2;
	  if( std::abs(delta.Y()) > 1.0E-3 ){
	    cout<<myname<<"WARNING channel intecepts are not ligned up on the same collection channel : "<<delta.Y()<<endl;
	    continue;
	  }
	  float d = std::abs(delta.X());
	  if( d < dmin ){
	    iroi1 = idx1;
	    ipnt1 = idx_pnt1;
	    iroi2 = idx2;
	    ipnt2 = idx_pnt2;
	    dmin  = d;
	  }
	} // loop points in 2nd roi set
      } // loop rois in 2nd set
    } // loop points in 1st roi set
  } // loop rois in 1st set
  
  ChRoiVector matched_rois;
  if( dmin > m_MaxDist ){ // no match was found
    return matched_rois;
  }
  
  if( iroi1 == badidx || ipnt1 == badidx ||
      iroi2 == badidx || ipnt2 == badidx  ) {
    return matched_rois;
  }
  
  // return two rois that were matched
  // with an intercept point being the average of the two
  matched_rois.resize(2);
  matched_rois[0] = rois1[iroi1];
  matched_rois[1] = rois2[iroi2];
  auto const &pnt1 = matched_rois[0].ipnts[ipnt1];
  auto const &pnt2 = matched_rois[1].ipnts[ipnt2];
  Point2d_t avg;
  avg.SetX( (pnt1.X() + pnt2.X())/2 );
  avg.SetY( (pnt1.Y() + pnt2.Y())/2 );
  matched_rois[0].ipnts.clear();
  matched_rois[0].ipnts.push_back( avg );
  matched_rois[1].ipnts = matched_rois[0].ipnts;
  
  return matched_rois;
}

//
bool IsoRoiMatcher::doCenterAndCrop( ChRoiVector &amatch, 
				     const AdcChannelDataMap& acds ) const {

  if( m_AlignMode == "peak" ){
    Index t0 = amatch.front().tmax;
    Index ts = (t0<m_NRoiPreSamples)?0:(t0-m_NRoiPreSamples);
    Index te = ts + m_NRoiTotSamples;
    for( auto &roi : amatch ){
      roi.tstart = ts;
      roi.tend   = te;
    }
  } else if (m_AlignMode == "zerocrossing"){
    Index tmax = amatch.front().tmax;
    Index tmin = amatch.front().tmin;
    Index ch   = amatch.front().chan;
    auto iacd = acds.find( ch );
    if( iacd == acds.end() ) {
      return false;
    }
    auto const &acd     = iacd->second;
    auto const it_start = acd.samples.begin() + tmax;
    auto const it_end   = acd.samples.begin() + tmin + 1;
    
    auto it_low = std::lower_bound( it_start, it_end, 0.0 );
    Index t0    = std::distance(std::begin(acd.samples), it_low);
    if( t0 == tmax || t0 == tmin ) return false;
    Index ts = (t0<m_NRoiPreSamples)?0:(t0-m_NRoiPreSamples);
    Index te = ts + m_NRoiTotSamples;
    for( auto &roi : amatch ){
      roi.tstart = ts;
      roi.tend   = te;
    }
  }
  
  return true;
}


//
void IsoRoiMatcher::buildChGroupSets( const NameVector &sets ){
  const string myname = "IsoRoiMatcher::buildChGroupSets: ";
  
  // get ch range tool
  string crtName = "channelGroups";
  DuneToolManager* ptm = DuneToolManager::instance();
  const IndexRangeGroupTool* pcrt = ptm == nullptr ? nullptr : ptm->getShared<IndexRangeGroupTool>(crtName);

  size_t nrops = m_DetChInfo->getNRops();
  for( auto const &s : sets ){
    NameVector set_grps;
    unpackStrOpts(s, set_grps);
    if( set_grps.size() != nrops ){
      cout<<myname<<"WARNING: '"<<s<<"' group does not contain enogh ROPs "
	  <<nrops<<". Skipping ..."<<endl;
      continue;
    }
    GroupSet aset(set_grps.size());
    int nerr = 0;
    for(Index idx=0;idx<aset.size();idx++){
      Name sgrp       = set_grps[idx];
      aset[idx].name  = sgrp;
      aset[idx].ropid = idx; // this assumptions should be respected in the set order!
      
      //
      IndexRangeGroup grp;
      if( pcrt != nullptr ) grp = pcrt->get(sgrp);
      if ( ! grp.isValid() ) grp = IndexRangeGroup(sgrp);
      if ( ! grp.isValid() || grp.name.size() == 0 ) {
	cout << myname << "WARNING: Unable to find range group " << sgrp << endl;
	++nerr;
      } else {
	grp.getIndices( aset[idx].channels );
      }
    }
    if ( nerr ) {
      if ( pcrt == nullptr ) {
	cout << myname << "Channel groups tool " << crtName << " was not found." << endl;
      } else {
	cout << myname << "Channel groups tool " << crtName << " listing:" << endl;
	pcrt->get("list");
      }
    } else {
      m_GroupSets.push_back(aset);
    }
  }// loop over all sets
  
  
  return;
}


// build a map of various channel intercepts
IsoRoiMatcher::ChInterceptsMap
IsoRoiMatcher::buildRopIntercepts( IndexRange r, ChGroup g ){
  const string myname = "IsoRoiMatcher::buildRopIntercepts: ";
  ChInterceptsMap amap;
  auto const ints = m_DetChInfo->getROPInterceptMap( r, g.ropid );
  if( ints.empty() ){
    cout<<myname<<"WARNING could not find any ROP inteercepts for "
	<<r.first<<":"<<r.second<<" in ROP "<<g.ropid<<endl;
    return amap;
  }
  
  Index ifirst = g.channels[0];
  Index ilast  = g.channels.back();
  
  for( auto const &[key, values]: ints ){
    ChIntercepts ch_ints;
    for( const auto &pnt : values ){
      if( pnt.first < ifirst || pnt.first > ilast ){
	cout<<myname<<"WARNING: "<<pnt.first<<" ch is outside of group ch range"<<endl;
	continue;
      }
      ch_ints.add(pnt.first, pnt.second);
    }
    amap.insert(std::make_pair(key, ch_ints));
  }
  
  return amap;
}

//
void IsoRoiMatcher::buildInterceptsMap(){
  // the goal here is to build a map of collection channel intercepts with
  // other views 
  const string myname = "IsoRoiMatcher::buildInterceptsMap: ";
  size_t nrops = m_DetChInfo->getNRops();
  if( nrops < 2 ){ 
    cout<<myname<<"ERROR: too few ROPs.\n";
    return;
  }
  
  // number of "other" planes
  size_t nsrops = nrops - 1;

  m_ChIntercepts.resize(nsrops);
  for( auto const gset : m_GroupSets ){
    auto const &col = gset.back();
    IndexRange idxrange = std::make_pair( col.channels[0], col.channels.back()+1 );
    for( size_t idx = 0;idx < nsrops; ++idx ){
      auto amap = buildRopIntercepts( idxrange, gset[idx] );
      m_ChIntercepts[idx].insert(amap.begin(), amap.end());
    } // loop over ROPs apart from collection
  } // loop over sets

  // 
}


DEFINE_ART_CLASS_TOOL(IsoRoiMatcher)
