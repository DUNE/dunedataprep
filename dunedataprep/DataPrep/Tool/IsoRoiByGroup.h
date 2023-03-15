// IsoRoiByGroup.h
//
// Vyacheslav Galymov
// March, 2023
//
// Select only sufficiently isolated ROIs in a given group channels
// Channel groups are obtained from the channel group tool channelGroups.
//
//
// Configuration:
//   LogLevel: Log frequency: 0=none, 1=initialization, 2=every event
//   Groups: List of group names.
//   Options: List of options (last overrides):
//    
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
  NameVector m_Options;

};


#endif
