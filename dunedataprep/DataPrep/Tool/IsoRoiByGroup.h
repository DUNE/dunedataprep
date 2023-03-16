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
//   a) a channel N+1 might be physically removed from channel N by a 
//     substantial distance but its ROIs will be masked. 
//   b) a channel M might be quite far from N in terms nch_ez window,
//     but quite close physically (example collection strips in VD CRPs).
//     In this case ROIs (due to end of the tracks) might be flagged as 
//     isolated deposits
// The case a) decreases the efficiency of the algorithm, while the 
// the case b) can possibley increase it. On the other than the 
// contamination from cosmic tracks should be very small (i.e.,
// this requires a single hit on the "right" channel). However, brem
// photons could be a contribution. 
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
#include <unordered_map>

	
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
  using AdcRoiMap = std::unordered_map<Index, AdcRoiVector>;
	
  // Configuration data.
  int  m_LogLevel;
  NameVector m_Groups;
  Index m_NchEz;
  Index m_NtickEz;
  
  //
  ChannelGroups m_chg;

  // methods
  AdcRoiMap buildIsodepRois(const IndexVector& channels, const AdcChannelDataMap& acds) const;
  AdcFilterVector buildFilterVector(Index nsam, AdcRoiVector rois) const;
};


#endif
