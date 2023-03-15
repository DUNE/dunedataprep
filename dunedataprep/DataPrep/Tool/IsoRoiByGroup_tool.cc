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
using std::setw;

//
// Ctor
IsoRoiByGroup::IsoRoiByGroup(fhicl::ParameterSet const& ps)
: m_LogLevel(ps.get<int>("LogLevel")),
  m_Groups(ps.get<NameVector>("Groups")),
  m_NchEz(ps.get<Index>("NChanEz")),
  m_NtickEz(ps.get<Index>("NTickEz")) {
  
  //
  const string myname = "IsoRoiByGroup::ctor: ";

  // Build the channel map.
  string crtName = "channelGroups";
  DuneToolManager* ptm = DuneToolManager::instance();
  const IndexRangeGroupTool* pcrt = ptm == nullptr ? nullptr : ptm->getShared<IndexRangeGroupTool>(crtName);
  int nerr = 0;
  for ( Name sgrp : m_Groups ) {
    IndexRangeGroup grp;
    if ( pcrt != nullptr ) grp = pcrt->get(sgrp);
    if ( ! grp.isValid() ) {
      grp = IndexRangeGroup(sgrp);
    }
    if ( ! grp.isValid() || grp.name.size() == 0 ) {
      cout << myname << "WARNING: Unable to find range group " << sgrp << endl;
      ++nerr;
    } else {
      grp.getIndices(m_chg[grp.name]);
    }
  }
  if ( nerr ) {
    if ( pcrt == nullptr ) {
      cout << myname << "Channel groups tool " << crtName << " was not found." << endl;
    } else {
      cout << myname << "Channel groups tool " << crtName << " listing:" << endl;
      pcrt->get("list");
    }
  }

  // Log the configuration.
  if ( m_LogLevel >= 1 ) {
    cout << myname << "  LogLevel: " << m_LogLevel << endl;
    cout << myname << "    Groups: [";
    int count = 0;
    for ( Name nam : m_Groups ) {
      if ( count && count%10 == 0 ) cout << "\n" + myname + "             ";
      if ( count++ ) cout << ", ";
      cout << nam;
    }
    cout << "]" << endl;
    
    if ( m_chg.size() ) {
      cout << myname << "     Group   #chan" << endl;
      for ( const auto& ient : m_chg ) {
        cout << myname << setw(10) << ient.first << setw(8) << ient.second.size() << endl;
      }
    } else {
      cout << myname << "No channel groups found." << endl;
    }
    cout<<myname<<"Channel exclusion zone : "<<m_NchEz<<endl;
    cout<<myname<<"Tick exclusion zone    : "<<m_NtickEz<<endl;
  }
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


DEFINE_ART_CLASS_TOOL(IsoRoiByGroup)
