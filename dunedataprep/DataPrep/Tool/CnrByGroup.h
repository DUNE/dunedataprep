// CnrByGroup.h
//
// David Adams
// November 2021
//
// Remove correlated noise by subtracting the mean or median signal from the group for each channel.
// Channel groups are obtained from the channel group tool channelGroups.
//
// Adapted from PdspNoiseRemoval.
//
// Configuration:
//   LogLevel: Log frequency: 0=none, 1=initialization, 2=every event
//   Groups: List of group names.
//   Options: List of options (last overrides):
//     mean: Evaluate correction using mean of samples (default)
//     median: Evaluate correction using median of samples

#ifndef CnrByGroup_H
#define CnrByGroup_H

#include "art/Utilities/ToolMacros.h"
#include "fhiclcpp/ParameterSet.h"
#include "dune/DuneInterface/Tool/TpcDataTool.h"
#include <string>
#include <vector>
#include <map>
	
class CnrByGroup : TpcDataTool {

public:

  // Ctor.
  CnrByGroup(fhicl::ParameterSet const& ps);

  // Dtor.
  ~CnrByGroup() override =default;

  // Noise removal.
  DataMap updateMap(AdcChannelDataMap& acds) const override;
  
private:

  using Name = std::string;
  using NameVector = std::vector<Name>;
  using Index = unsigned int;
  using IndexVector = std::vector<Index>;
  using ChannelGroups = std::map<Name, IndexVector>;
  using FloatVector = std::vector<float>;
  	
  // Configuration data.
  int  m_LogLevel;
  NameVector m_Groups;
  NameVector m_Options;

  // Derived data.
  ChannelGroups m_chg;
  bool m_useMedian =false;
  bool m_dropSignal =true;
  bool m_requireGoodChannel =true;

  FloatVector getCorrection(const IndexVector& channels, const AdcChannelDataMap& acds) const;

};

#endif
