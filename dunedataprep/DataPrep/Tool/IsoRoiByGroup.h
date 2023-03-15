// IsoRoiByGroup.h
//
// Vyacheslav Galymov
// March, 2023
//
// Select only sufficiently isolated ROIs in a given group of channels
// Channel groups are obtained from the channel group tool channelGroups.
//
// The isolated deposits are selected based on ROI isolation based on
// NchEz (ch exclusion zone) and NtickEz (tick exclusion zone) options
// For a given channel ch the exclusion zone is defined within +/- NchEz
// window. Within this window an ROI is included as isolated if it is 
// separated by more than NtickEz from another ROIs. 
// This makes an underlying assumptions that the channels in given range 
// a continuous. However, their geographical position with respect to each 
// other is not respected in this simple treatement. Example:
//   - a channel N+1 might be physically removed from channel N by a 
//     substantial distance but its ROIs will be masked. 
//   - a channel M might be quite far from N in terms nch_ez window,
//     but quite close physically (example collection strips in VD CRPs).
//     In this case ROIs (due to end of the tracks) might be flagged as 
//     isolated deposits
//
// Configuration:
//   LogLevel: Log frequency: 0=none, 1=initialization, 2=every event
//   Groups: List of group names.
//   NChanEz : Number of channels to define an exclusion zone -> m_NchEz
//   NTickEz : Number of ticks to define an exclusion zoe -> m_NtickEz
//    

#ifndef IsoRoiByGroup_H
#define IsoRoiByGroup_H

#include "art/Utilities/ToolMacros.h"
#include "fhiclcpp/ParameterSet.h"
#include "dunecore/DuneInterface/Tool/TpcDataTool.h"
#include <string>
#include <vector>
#include <map>
	
class IsoRoiByGroup : TpcDataTool {

public:

  // Ctor
  IsoRoiByGroup(fhicl::ParameterSet const& ps);

  // Dtor
  ~IsoRoiByGroup() override =default;

  // filter isolated ROIs
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
  Index m_NchEz;
  Index m_NtickEz;
  
  //
  ChannelGroups m_chg;

};


#endif
