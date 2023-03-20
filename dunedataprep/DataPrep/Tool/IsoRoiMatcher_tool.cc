#include "IsoRoiMatcher.h"

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
  m_MaxTDelta = ps.get<Index>("MaxTDelta");
  
  // detector channel info from geo service
  m_DetChInfo = std::make_unique<DetChInfo>(m_LogLevel);
  
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

  if ( acds.size() == 0 ) {
    cout << myname << "WARNING: No channels found." << endl;
    return ret.setStatus(1);
  }

  return ret;
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
