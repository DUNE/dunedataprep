#include "DetectorChannelInfo.h"

// 
#include <iostream>
#include <string>
//#include <unordered_set>

//
#include <boost/functional/hash.hpp>

// larsoft
#include "larcore/Geometry/Geometry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

using std::cout;
using std::endl;
using std::string;

namespace {
  //
  size_t wid_hash( const geo::WireID &wid ){
    size_t seed = 0;
    boost::hash_combine(seed, wid.Cryostat);
    boost::hash_combine(seed, wid.TPC);
    boost::hash_combine(seed, wid.Plane);
    boost::hash_combine(seed, wid.Wire);
    return seed;
  }
}

//
dataprep::util::
DetectorChannelInfo::DetectorChannelInfo( int loglevel ) : m_LogLevel(loglevel) 
{
  const string myname = "DetectorChannelInfo::ctor: ";
  
  //
  // get geometry
  art::ServiceHandle<geo::Geometry> geo;
  
  //
  Index wid_cnt = 0;
  
  //double xyz[3];   
  //double abc[3];                                                                 
  for (auto const& wid : geo->Iterate<geo::WireID>()) {
    //geo->WireEndPoints(wid,xyz,abc);
    Index  chan = geo->PlaneWireToChannel(wid);
    size_t hash = wid_hash( wid );
    
    // wire to channel
    {
      bool ok   = m_WireToChan.insert( std::make_pair(hash, chan) ).second;
      if( !ok && m_LogLevel > 0 ){
	cout<<myname<<" WARNING multiple identical hash values for geo::WireID";
      }
    }
    // channel to wire
    {
      if( m_ChanToWire.find(chan) == m_ChanToWire.end() ){
	std::vector<size_t> v{hash};
	m_ChanToWire.insert( std::make_pair(chan, v) );
      } else {
	m_ChanToWire[chan].push_back( hash );
      }      
    }
    

    //std::cout << "FLAG " <<wid_cnt<< " " << chan << " " << wid << " " << xyz[0] << " " << xyz[1] << " " << xyz[2] <<  " " << abc[0] << " " << abc[1] << " " << abc[2] << std::endl;
    wid_cnt ++;
  }

  if( m_LogLevel > 1 ){
    cout<<myname<<"Total wires counted : "<<wid_cnt<<endl;
    cout<<myname<<"Total hash values   : "<<m_WireToChan.size()<<endl;
    cout<<myname<<"Total channels      : "<<m_ChanToWire.size()<<endl;
  }
  
}

//
dataprep::util::
DetectorChannelInfo::~DetectorChannelInfo()
{;}
