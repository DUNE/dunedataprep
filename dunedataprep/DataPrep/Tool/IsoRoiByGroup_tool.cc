#include "IsoRoiByGroup.h"

#include "dunecore/ArtSupport/DuneToolManager.h"
#include "dunecore/DuneInterface/Data/IndexRange.h"
#include "dunecore/DuneInterface/Data/IndexRangeGroup.h"
#include "dunecore/DuneInterface/Tool/IndexRangeGroupTool.h"
#include <iostream>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;

//
//
IsoRoiByGroup::IsoRoiByGroup(fhicl::ParameterSet const& ps)
: m_LogLevel(ps.get<int>("LogLevel")),
  m_Groups(ps.get<NameVector>("Groups")),
  m_Options(ps.get<NameVector>("Options")) {
  const string myname = "IsoRoiByGroup::ctor: ";
  
}

//
//
DataMap IsoRoiByGroup::updateMap(AdcChannelDataMap& acds) const {
  const string myname = "IsoRoiByGroup::updateMap: ";
  DataMap ret;
  
  cout<<myname<<acds.size()<<endl;
  if ( acds.size() == 0 ) {
    std::cout << myname << "WARNING: No channels found." << std::endl;
    return ret.setStatus(1);
  }

  
  return ret;
}
