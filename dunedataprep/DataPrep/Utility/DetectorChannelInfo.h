// DetectorChannelInfo.h
//  
// Build a light weight map of readout channels from
// the geometry service as a function raw::ChannelId
// 
// The infomration that is collected here
//   - signal type (e.g., kU, kV, kZ) for each readout channel
//   - physical endpoints of a wire for a given channel
// Possible uses:
//   - give a range of channels from induction plane(s)
//     crossed by a collection plane channel
//   - intersection point between induction and collection chans
//   
//
// To avoid juggling multiple indices (cryo, tpc, plane, wire) the 
// geo::WireID is hashed with a boost::hash_combine function
// The look up tables between wires and channels are then built
// using the hased values.
//
// The ReadoutPlane channel ranges are given by a pair of ints
// the range is [first_ch, last_ch), i.e., the last ch specified 
// is not part of the set
//
// vgalymov, March, 2023
// 

#ifndef __DETECTOR_CHANNEL_INFO_H__
#define __DETECTOR_CHANNEL_INFO_H__

#include <unordered_map>
#include <vector>
#include <utility>
#include <optional>
#include <tuple>

#include "larcorealg/Geometry/TPCGeo.h"
#include "larcoreobj/SimpleTypesAndConstants/geo_types.h"
#include "larcoreobj/SimpleTypesAndConstants/geo_vectors.h"


// ROOT libraries
#include "Math/GenVector/Cartesian2D.h"
#include "Math/GenVector/CoordinateSystemTags.h"
#include "Math/GenVector/PositionVector2D.h"



namespace dataprep::util {
  //
using Point2d_t = ROOT::Math::PositionVector2D<ROOT::Math::Cartesian2D<float>,  ROOT::Math::GlobalCoordinateSystemTag>;

using Index           = unsigned int;
using IndexRange      = std::pair<Index, Index>;
  
// structures to keep intercept points of channels
//   Each ROP ch can intercept channels in other ROPs in one 
//   or several (wrapped APA wires?) places.
// The intercept points are computed based on the wire geo info
// Therefore only one intercept should be possible between two wires

using ChIntercept     = std::pair<Index, Point2d_t>; 
using VecChIntercept  = std::vector< ChIntercept >;  
using MapROPIntercept = std::unordered_map<Index, VecChIntercept>;

// geometric info 
struct ChGeoInfo {
  Index  chan;
  Index  ropid;
  geo::WireID wid;
  Point2d_t endpnt1;
  Point2d_t endpnt2;
};

   
class DetectorChannelInfo
{
  
 public:
  using MapChanRop  = std::unordered_map<Index, Index>;
  using MapWireChan = std::unordered_map<size_t, Index>;
  using MapChanWire = std::unordered_map<Index, std::vector<size_t>>;
  using MapWireChGeoInfo = std::unordered_map<size_t, ChGeoInfo>;

  //
  DetectorChannelInfo(int loglevel = 0);
  ~DetectorChannelInfo();

  Index getNChans() const { return m_Chans; }
  size_t getNRops() const { return m_RopChRanges.size(); }
  std::vector<IndexRange> getROPChRanges( Index ropid ) const;
  Index getChROPID( Index ch ) const;
  
  // geo info for a given readout channel
  std::vector<ChGeoInfo> getChGeoInfo( Index ch ) const;
  
  // Find intercepts of a given channel with channels in another ROP
  //   Naturally the specified channel should occupy a different ROP
  //   The vector of pairs returned is be sorted on channels found to 
  //   be crossed in the other ROP and duplicates removed
  VecChIntercept  getChROPIntercept( Index ch, Index ropid_other ) const;

  
  // same as getChROPIntercept but repeat for a group of channels
  MapROPIntercept getROPInterceptMap( Index ropid, Index ropid_other ) const;
  MapROPIntercept getROPInterceptMap( IndexRange irange, Index ropid_other ) const;
  
 private:
  // find guessed drift direction from TPC volume
  short int getDriftDir( const geo::TPCGeo &tpc );
  // remove drift coordinate
  Point2d_t makeCoord2d( const geo::Point_t &pnt );

  std::optional<Point2d_t> Intersection( const ChGeoInfo &wid1,
					 const ChGeoInfo &wid2 ) const ;

  //
  int m_LogLevel;

  // drift coordinate
  short int  m_DriftAxis; // 0 - X, 1 - Y, 2 - Z
  
  // map of a wire to channel
  //  i.e., hashed WireID to ChannelID
  MapWireChan m_WireToChan;

  // map channel to wire
  // it is possible several "wires" are assigned to same channel
  MapChanWire m_ChanToWire;

  //
  MapWireChGeoInfo m_ChGeoInfo;

  //
  Index m_Chans;
  
  // readout planes
  Index m_MaxRop;
  std::vector<std::vector<IndexRange>> m_RopChRanges;
  MapChanRop  m_ChanToRop;

};

}// dataprep::util

#endif
