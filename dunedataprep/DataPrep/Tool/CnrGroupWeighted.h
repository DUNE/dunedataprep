// CnrGRoupWeighted.h
//
// David Adams
// November 2021
//
// Remove correlated noise by subtracting the weighted mean or median signal from
// the group for each channel.
// Channel groups are obtained from the channel group tool channelGroups.
// For sample s_ci (c = channel, i = tick), the correct signal is
//   s'_ci = s_ci - w_c C_gi
// where w_c is the assigned channel weight (e.g. BG RMS) and C_gi (g = channel group)
// is the mean or median of s_ci/w_c of tick i for channels in the group.
// E.g. the calculation for the mean is
//   C_gi = (SUM_c-in-g s_ci/w_c) / N_c-in-g
// Channels with zero weight are excluded from the calculation and left uncorrectd.
// Samples identified as signal are excluded from calculation but are corrected.
//
// Adapted from PdspNoiseRemoval.
//
// Configuration:
//   LogLevel: Log frequency: 0=none, 1=initialization, 2=every event
//   Weight: Name of variable holding the weight (blank for uniform weighting).
//   Groups: List of group names.
//   Options: List of options (last overrides):
//     mean: Evaluate correction using mean of samples (default)
//     median: Evaluate correction using median of samples

#ifndef CnrGroupWeighted_H
#define CnrGroupWeighted_H

#include "art/Utilities/ToolMacros.h"
#include "fhiclcpp/ParameterSet.h"
#include "dune/DuneInterface/Tool/TpcDataTool.h"
#include <string>
#include <vector>
#include <map>
	
class CnrGroupWeighted : TpcDataTool {

public:

  // Ctor.
  CnrGroupWeighted(fhicl::ParameterSet const& ps);

  // Dtor.
  ~CnrGroupWeighted() override =default;

  // Noise removal.
  DataMap updateMap(AdcChannelDataMap& acds) const override;
  
private:

  using Name = std::string;
  using NameVector = std::vector<Name>;
  using Index = unsigned int;
  using IndexVector = std::vector<Index>;
  using ChannelGroups = std::map<Name, IndexVector>;
  using FloatVector = std::vector<float>;
  using FloatMap = std::map<Index, float>;
  	
  // Configuration data.
  int  m_LogLevel;
  Name m_Weight;
  NameVector m_Groups;
  NameVector m_Options;

  // Derived data.
  ChannelGroups m_chg;
  bool m_useMedian =false;
  bool m_dropSignal =true;
  bool m_requireGoodChannel =true;

  void getWeights(const IndexVector& channels, const AdcChannelDataMap& acds, FloatMap& wts) const;
  FloatVector getCorrection(const IndexVector& channels, const AdcChannelDataMap& acds,
                            const FloatMap& wts) const;

};

#endif
