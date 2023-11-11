#include "DetectorChannelInfo.h"

// 
#include <iostream>
#include <string>

//
#include <boost/functional/hash.hpp>

// larsoft
#include "larcore/Geometry/WireReadout.h"
#include "larcore/Geometry/Geometry.h"
#include "canvas/Utilities/Exception.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

using std::cout;
using std::endl;
using std::string;

using dataprep::util::Point2d_t;
using dataprep::util::Index;
using dataprep::util::IndexRange;
using dataprep::util::ChIntercept;
using dataprep::util::VecChIntercept;
using dataprep::util::MapROPIntercept;
using dataprep::util::ChGeoInfo;

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
// collect info from geo service
dataprep::util::
DetectorChannelInfo::DetectorChannelInfo( int loglevel ) : m_LogLevel(loglevel) 
{
  const string myname = "DetectorChannelInfo::ctor: ";
  
  //
  geo::WireReadoutGeom const& wireReadout = art::ServiceHandle<geo::WireReadout>()->Get();

  
  // get drift axis for this geometry
  m_DriftAxis = art::ServiceHandle<geo::Geometry>()->TPC().DriftAxisWithSign().coordinate;
  if( m_LogLevel > 1 ){
    cout<<myname<<"Drift coordinate is "<<m_DriftAxis<<endl;
  }


  //
  m_Chans   = wireReadout.Nchannels();
  m_MaxRop  = wireReadout.MaxROPs(); 
  if( m_MaxRop > 3 ){ 
    cout<<myname<<"ERROR number of readout planes > 3 is not supported\n";
    throw art::Exception(art::errors::Configuration, "InvalidNumberOfROPs");
  }
  if(m_LogLevel > 1 ){
    cout<<myname<<"Number of channels in the geometry       : "<<m_Chans<<endl;
    cout<<myname<<"Number of readout planes in the geometry : "<<m_MaxRop<<endl;
  }
   
  
  //
  m_RopChRanges.resize( m_MaxRop );
  for( auto const& rop : wireReadout.Iterate<readout::ROPID>() ){
    Index ropid = rop.ROP;
    Index fch   = wireReadout.FirstChannelInROP( rop );
    Index nch   = wireReadout.Nchannels( rop );
    Index lch   = fch + nch;
    for( Index i = fch;i<lch; ++i ){
      m_ChanToRop.insert( std::make_pair( i, ropid ) );
    }
    m_RopChRanges[ropid].push_back(std::make_pair(fch, lch) );
  }

  //
  Index wid_cnt = 0;
  
  for (auto const& wid : wireReadout.Iterate<geo::WireID>()) {
    Index  chan = wireReadout.PlaneWireToChannel(wid);
    size_t hash = wid_hash( wid );
    auto   rop  = wireReadout.ChannelToROP( chan );
    
    // wire to channel
    {
      bool ok   = m_WireToChan.insert( std::make_pair(hash, chan) ).second;
      if( !ok && m_LogLevel > 0 ){
	cout<<myname<<"WARNING multiple identical hash values for geo::WireID\n";
      }

      // geo info for this wire
      ChGeoInfo ch_geo_info;
      ch_geo_info.chan  = chan;
      ch_geo_info.ropid = rop.ROP;
      ch_geo_info.wid   = wid;
      auto ends = wireReadout.WireEndPoints(wid);
      ch_geo_info.endpnt1 = makeCoord2d( ends.first );
      ch_geo_info.endpnt2 = makeCoord2d( ends.second );
      m_ChGeoInfo.insert( std::make_pair( hash, ch_geo_info ) );
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

//
// reduce 3D to 2D by removing the drift coordinate
Point2d_t dataprep::util::
DetectorChannelInfo::makeCoord2d( const geo::Point_t &pnt ){
  Point2d_t p;
  if( m_DriftAxis == geo::Coordinate::Y ){
    p.SetXY( pnt.X(), pnt.Z() );
  } else { //default to X drift
    p.SetXY( pnt.Y(), pnt.Z() );
  }
  
  return p;
}


//
// find if intersection exists between two wires
std::optional<Point2d_t> dataprep::util::
DetectorChannelInfo::Intersection( const ChGeoInfo &wid1,
				   const ChGeoInfo &wid2 ) const {
  
  // some basic logic to calculate intersection point:
  //  1) not the same readout channel
  //  2) not in different TPCs
  //  3) not in the same plane
  //
  if( wid1.chan == wid2.chan ){
    // same channel
    return std::nullopt;
  }
   
  //
  if( wid1.wid.TPC != wid2.wid.TPC ){
    // not in the same TPC
    return std::nullopt;
  }
  
  //
  if( wid1.wid.Plane == wid2.wid.Plane ){
    // same plane
    return std::nullopt;
  }
  
  // now solve equations for two interesecting line segments
  //  L1 = {p + t r | t in [0, 1]}
  //  L2 = {q + u s | u in [0, 1]}
  // by finding if t & u are both >= 0 and <= 1
  
  float px = wid1.endpnt1.X();
  float py = wid1.endpnt1.Y();
  float rx = wid1.endpnt2.X() - px;
  float ry = wid1.endpnt2.Y() - py;

  float qx = wid2.endpnt1.X();
  float qy = wid2.endpnt1.Y();
  float sx = wid2.endpnt2.X() - qx;
  float sy = wid2.endpnt2.Y() - qy;
  
  // determinant of linear equiation matrix
  
  float det = rx*sy - ry*sx;
  
  if( std::abs( det ) < 1.0E-4 ){
    //lines are parallel / should not happen at this stage
    return std::nullopt;
  }
  
  //
  float dx = qx - px;
  float dy = qy - py;
  float d1 = dx*sy - dy*sx;
  float d2 = dx*ry - dy*rx;
  float t  = d1/det;
  float u  = d2/det;
  
  if( (t>=0 && t<=1) && (u>=0 && u<=1) ){
    float x = px + t*rx;
    float y = py + t*ry;
    return Point2d_t( x, y );
  }

  return std::nullopt;
}

//
//
Index dataprep::util::
DetectorChannelInfo::getChROPID( Index ch ) const {
  auto found = m_ChanToRop.find( ch );
  if( found != m_ChanToRop.end() ){
    return found->second;
  }
  
  return (m_MaxRop);
}

//
//
std::vector<IndexRange> dataprep::util::
DetectorChannelInfo::getROPChRanges( Index ropid ) const 
{
  const string myname = "DetectorChannelInfo::getROPChRanges: ";
  std::vector<IndexRange> r;
  if( ropid >= m_RopChRanges.size() ){
    //
    cout<<myname<<"ERROR could not find ropid "<<ropid<<endl;
    throw art::Exception(art::errors::InvalidNumber, "InvalidROPId");
  } else {
    r = m_RopChRanges[ropid];
  }
  
  return r;
}

//
//
std::vector<ChGeoInfo> dataprep::util::
DetectorChannelInfo::getChGeoInfo( Index ch ) const {
  const string myname = "DetectorChannelInfo::getChROPIntercept: ";

  std::vector<ChGeoInfo> chgeo;
  if( ch >= m_Chans ){
    cout<<myname<<"ERROR ch index "<<ch<<" is too large"<<endl;
    return chgeo;
  }
  
  auto found = m_ChanToWire.find(ch);
  if(  found == m_ChanToWire.end() ){
    cout<<myname<<"ERROR: the channel "<<ch<<" could not be found in the channel map\n";
    return chgeo;
  }
  
  //
  auto hash_vec = found->second;
  for(auto const &hash : hash_vec ){
    auto find_wire = m_ChGeoInfo.find( hash );
    if( find_wire == m_ChGeoInfo.end() ){
      cout<<myname<<"ERROR: bad wire hash "<<hash<<" for ch "<<ch<<endl;
      continue;
    }
    chgeo.push_back( find_wire->second );
  }

  return chgeo;
}


//
//
VecChIntercept dataprep::util::
DetectorChannelInfo::getChROPIntercept( Index ch, Index ropid_other ) const {
  const string myname = "DetectorChannelInfo::getChROPIntercept: ";

  VecChIntercept intercepts; 
  auto this_ch_geo_info = getChGeoInfo( ch );
  if( this_ch_geo_info.empty() ){
    if(m_LogLevel > 0 ){
      cout<<myname<<"ERROR: could not find in wire map "<<ch<<endl;
    }
    return intercepts;
  }
  if( this_ch_geo_info[0].ropid == ropid_other ){
    cout<<myname<<"ERROR ch "<<ch<<" belongs to the same ROP as "<<ropid_other<<endl;
    return intercepts;
  }
  
  auto ropRanges = getROPChRanges( ropid_other );
  
  for( auto const &rop_range: ropRanges ){
    for(Index ch_other=rop_range.first; ch_other<rop_range.second; ++ch_other ){
      auto other_ch_geo_info = getChGeoInfo( ch_other );
      for(auto const &o_ch_geo : other_ch_geo_info){
	for( auto const &ch_geo : this_ch_geo_info ){
	  auto pnt = Intersection( ch_geo, o_ch_geo );
	  if( !pnt ) continue;
	  intercepts.push_back( std::make_pair(ch_other, pnt.value()) );
	} // this ch geo
      } // other ch geo
    } // rop range
  } // all rop ranges
  
  // sort on channel number
  std::sort( intercepts.begin(), intercepts.end(), [](auto const &l, auto const &r){
      return (l.first < r.first);} );
  
  // remove identical intercepts if any
  float tol = 1.0E-4;
  auto it = intercepts.begin() + 1;
  while( it != intercepts.end() ){
    auto v1 = *it;
    auto v0 = *(std::prev(it, 1));
    if( v1.first == v0.first ){
      bool isame = std::abs( v1.second.X() - v0.second.X() ) < tol;
      isame = isame && (std::abs( v1.second.Y() - v0.second.Y() ) < tol);
      if( isame ){
	if( m_LogLevel > 2 ){
	  cout<<myname<<"erase point for "<<ch<<" in ROP "<<ropid_other<<endl;
	}
	it = intercepts.erase(it);
	continue;
      }
    }
    it++;
  }
  
  //
  return intercepts;
}


//
//
MapROPIntercept dataprep::util::
DetectorChannelInfo::getROPInterceptMap( Index ropid, Index ropid_other ) const {
  
  MapROPIntercept aMap;
  
  auto ropRanges = getROPChRanges( ropid );
  for( const auto &chRange : ropRanges ){
    auto r = getROPInterceptMap( chRange, ropid_other );
    aMap.insert(r.begin(), r.end());
  }
  
  return aMap;
}

//
//
MapROPIntercept dataprep::util::
DetectorChannelInfo::getROPInterceptMap( IndexRange irange, Index ropid_other ) const {
  //
  MapROPIntercept aMap;
  
  const string myname = "DetectorChannelInfo::getROPInterceptMap: ";
  Index fch = irange.first;
  Index lch = irange.second;
  if( fch > lch ){
    cout<<myname<<"WARNING: the channel range appears to be invalid\n";
    std::swap( fch, lch );
  }
  
  for(Index ch = fch; ch < lch; ++ch){
    auto intercepts = getChROPIntercept( ch, ropid_other );
    if( intercepts.empty() ) continue;
    aMap.insert( std::make_pair( ch, intercepts ) );
  }
  
  return aMap;
}
