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
// vgalymov, March, 2023
// 

#ifndef __DETECTOR_CHANNEL_INFO_H__
#define __DETECTOR_CHANNEL_INFO_H__

#include <unordered_map>
#include <vector>

#include "larcoreobj/SimpleTypesAndConstants/geo_types.h"

namespace dataprep::util {

class DetectorChannelInfo
{
  
 public:
  using Index = unsigned int;
  using MapWireChan = std::unordered_map<size_t, Index>;
  using MapChanWire = std::unordered_map<Index, std::vector<size_t>>;

  //using MapHashGeo   = std::unordered_map<size_t, Index>;
  //using VectorWid = std::vector<geo::WireID>;
  
  DetectorChannelInfo(int loglevel = 0);
  ~DetectorChannelInfo();
  
 private:
  //
  int m_LogLevel;
  
  // map of a wire to channel
  //  i.e., hashed WireID to ChannelID
  MapWireChan m_WireToChan;

  // map channel to wire
  // it is possible several "wires" are assigned to same channel
  MapChanWire m_ChanToWire;

};

}// dataprep::util

#endif
