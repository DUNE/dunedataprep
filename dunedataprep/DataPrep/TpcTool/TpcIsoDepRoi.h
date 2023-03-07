#ifndef __TPCISODEPROI_H__
#define __TPCISODEPROI_H__

#include "art/Utilities/ToolMacros.h"
#include "fhiclcpp/ParameterSet.h"
#include "dunecore/DuneInterface/Tool/TpcDataTool.h"

#include "dunedataprep/DataPrep/Utility/DetectorChannelInfo.h"

class TpcIsoDepRoi : TpcDataTool {

 public:
  
  using Index = unsigned int;
  TpcIsoDepRoi(fhicl::ParameterSet const& ps);
  ~TpcIsoDepRoi() override =default;
  // 
  DataMap updateTpcData(TpcData&) const override;
  
 private:
  using DetectorChannelInfoPtr = std::unique_ptr<dataprep::util::DetectorChannelInfo>;
  
  int m_LogLevel;
  DetectorChannelInfoPtr m_DetChanInfo;
};

#endif
