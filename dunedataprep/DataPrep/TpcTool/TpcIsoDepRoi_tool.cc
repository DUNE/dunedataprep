#include "TpcIsoDepRoi.h"

#include <iostream>

using std::cout;
using std::endl;


//
TpcIsoDepRoi::TpcIsoDepRoi(fhicl::ParameterSet const& ps)
  : m_LogLevel(ps.get<int>("LogLevel"))
{
  
  m_DetChanInfo = std::make_unique<dataprep::util::DetectorChannelInfo>( m_LogLevel );
  
  
}
  
//
DataMap TpcIsoDepRoi::updateTpcData(TpcData& tpd) const {
  DataMap ret;
  
  return ret;
}



//**********************************************************************

DEFINE_ART_CLASS_TOOL(TpcIsoDepRoi)
