//
//  AdcSumSignalFinder.h
// 
//
//  This tool searches for signal regions by looking at sum of samples.
//  Given that the induction views have bipolar signals, the aglorithm
//  uses (or should use depending on fcl configs) abs(sample) values 
//  for the induction channels. Since the tool does not now which channel
//  is induction or collection options to specify groups of channels
//  and the appropriate parameters for each groups could be set via fcl
//  One should take care that the tool always uses abs(sample)
//  as default configuration, otherwise ROIs found for induction channels
//  would not be complete.
//
//  The tool configuration could take a list of channel groups and 
//  a list of corresponding thresholds for each group as well as
//  an option to use abs(sample) or sample in calculating the sums.
//  The threshold is specified in terms of n units of RMS. The algorithm
//  computes mean and RMS for a vector sample sums. To avoid biasing
//  the RMS the outliers are filtered using simple interquartile trimmer
//  algorithm. The threshold is then computed as:
//     threshold = N x RMS + Mean,
//    where N is the fcl parameter specifiying the threshold
//    and Mean and RMS are computed from the IQR trimmed vector of sample sums 
//
// Configuration:
//   LogLevel:     Log frequency: 0=none, 1=initialization, 2=every event
//   Groups:       If empty use default ROI threshold and abs(sample).
//                 Otherwise attempt to get channels for the corresponding groups
//   GroupMethod:  List of strings "sumabs" or "sum"
//   GroupThresh:  List of thresholds for each group as N units of RMS 
//   DefaultThresh: Default threshold for all unpecfied channels in group arg 
//   DefaultMethod: Default method "sumabs" or "sum" for for all unpecfied 
//                  channels in the group argument
//   SamplesToSum : Number of samples to sum
//   SampleSumStep: Step (lag) for moving sum search win
//   

#include "art/Utilities/ToolMacros.h"
#include "fhiclcpp/ParameterSet.h"
#include "dunecore/DuneInterface/Tool/TpcDataTool.h"
#include <utility>
#include <string>
#include <unordered_map>

class AdcSumSignalFinder: TpcDataTool {

public:
  
  // Ctor
  AdcSumSignalFinder(fhicl::ParameterSet const& ps);

  // Dtor
  ~AdcSumSignalFinder() override =default;

  // find ROIs on a given channel
  DataMap update(AdcChannelData& acd) const override;
  
 private:
  
  enum Method { SUMABS, SUM };
  
  struct RoiResult {
    float thresh;
    AdcFilterVector rois;
  };

  using Name        = std::string;
  using NameVector  = std::vector<Name>;
  using Index       = unsigned int;
  using IndexVector = std::vector<Index>;
  using FloatVector = std::vector<float>;
  using AlgoConfig  = std::pair< Method, float >;
  using ChAlgoConfig = std::unordered_map<Index, AlgoConfig>;
  
  int        m_LogLevel;
  AlgoConfig m_DefConfig;
  Index      m_SamplesToSum;
  Index      m_SampleSumStep;
  
  ChAlgoConfig m_ChConfigs;

  //
  AlgoConfig getChConfig( Index ch ) const ;
  
  RoiResult findChRois( Index ch, const AdcSignalVector &vec ) const;
};
