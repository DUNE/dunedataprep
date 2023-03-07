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
  using MapIndex = std::unordered_map<Index, Index>;
  using VectorWid = std::vector<geo::WireID>;
  
  DetectorChannelInfo(int loglevel = 0);
  ~DetectorChannelInfo();
  
 private:
  //
  int m_LogLevel;
  
};

}// dataprep::util

#endif
