// CnrGroupWeighted_tool.cc

#include "CnrGroupWeighted.h"
#include "dune/ArtSupport/DuneToolManager.h"
#include "dune/DuneInterface/Data/IndexRange.h"
#include "dune/DuneInterface/Data/IndexRangeGroup.h"
#include "dune/DuneInterface/Tool/IndexRangeGroupTool.h"
#include <iostream>
#include <iomanip>

using std::string;
using std::cout;
using std::endl;
using std::setw;

//**********************************************************************
// Class methods.
//**********************************************************************

CnrGroupWeighted::CnrGroupWeighted(fhicl::ParameterSet const& ps)
: m_LogLevel(ps.get<int>("LogLevel")),
  m_Weight(ps.get<Name>("Weight")),
  m_Groups(ps.get<NameVector>("Groups")),
  m_Options(ps.get<NameVector>("Options")) {
  const string myname = "CnrGroupWeighted::ctor: ";
  // Decode the options.
  for ( Name sopt : m_Options ) {
    if ( sopt == "mean" ) m_useMedian = false;
    else if ( sopt == "median" ) m_useMedian = true;
    else cout << myname << "WARNING: Ignoring invalid option: " << sopt << endl;
  }
  // Build the channel map.
  string crtName = "channelGroups";
  DuneToolManager* ptm = DuneToolManager::instance();
  const IndexRangeGroupTool* pcrt = ptm == nullptr ? nullptr : ptm->getShared<IndexRangeGroupTool>(crtName);
  for ( Name sgrp : m_Groups ) {
    IndexRangeGroup grp;
    if ( pcrt != nullptr ) grp = pcrt->get(sgrp);
    if ( ! grp.isValid() ) {
      grp = IndexRangeGroup(sgrp);
    }
    if ( ! grp.isValid() ) {
      cout << myname << "WARNING: Unable to find range group " << sgrp << endl;
    } else {
      grp.getIndices(m_chg[grp.name]);
    }
  }
       
  // Log the configuration.
  if ( m_LogLevel >= 1 ) {
    cout << myname << "  LogLevel: " << m_LogLevel << endl;
    cout << myname << "    Weight: " << m_Weight << endl;
    cout << myname << "    Groups: [";
    int count = 0;
    for ( Name nam : m_Groups ) {
      if ( count && count%10 == 0 ) cout << "\n             ";
      if ( count++ ) cout << ", ";
      cout << nam;
    }
    cout << "]" << endl;
    cout << myname << "   Options: [";
    count = 0;
    for ( Name nam : m_Options ) {
      if ( count++ ) cout << ", ";
      cout << nam;
    }
    cout << "]" << endl;
    cout << myname << "Using " << (m_useMedian ? "median" : "mean") << " correction." << endl;
    cout << myname << "Using " << (m_dropSignal ? "all" : "non-signal") << " samples." << endl;
    cout << myname << (m_requireGoodChannel ? "R" : "Not r") << "equiring good channel status." << endl;
    cout << myname << "    Group   #chan" << endl;
    for ( const auto& ient : m_chg ) {
      cout << myname << setw(10) << ient.first << setw(8) << ient.second.size() << endl;
    }
  }
}

//**********************************************************************

DataMap CnrGroupWeighted::updateMap(AdcChannelDataMap& acds) const {
  const string myname = "CnrGroupWeighted::updateMap: ";
  DataMap ret;
  if ( acds.size() == 0 ) {
    std::cout << myname << "WARNING: No channels found." << std::endl;
    return ret.setStatus(1);
  }
  // Loop over groups.
  for ( const auto& entry : m_chg ) {   
    const IndexVector& channels = entry.second;
    FloatMap wts;
    getWeights(channels, acds, wts);
    std::vector<float> correction = getCorrection(channels, acds, wts);
    for ( Index ich : channels) {
      auto iacd = acds.find(ich);
      if ( iacd == acds.end() ) continue;
      AdcChannelData& acd = iacd->second;
      if ( acd.samples.size() == 0 ) continue;
      if ( acd.samples.size() > correction.size() ) correction.resize(acd.samples.size(), 0.);
      for ( size_t isam=0; isam<acd.samples.size(); ++isam) {
        acd.samples[isam] -= wts[ich]*correction[isam];  
      }
    }
  }
  return ret;
}

//**********************************************************************

void CnrGroupWeighted::
getWeights(const IndexVector& channels, const AdcChannelDataMap& acds,
           FloatMap& wts) const {
  const string myname = "CnrGroupWeighted::getWeights";
  for ( Index ich : channels ) {
    if ( m_Weight.size() == 0 ) {
      wts[ich] = 1.0;
    } else {
      auto iacd = acds.find(ich);
      if ( iacd == acds.end() ) continue;
      const AdcChannelData& acd = iacd->second;
      if ( acd.hasAttribute(m_Weight) ) {
        wts[ich] = acd.getAttribute(m_Weight);
      } else {
        if ( m_LogLevel >= 1 ) {
          cout << myname << " Channel " << ich << " doe not have attribute "
               << m_Weight << endl;
        }
        wts[ich] = 0.0;
      }
    }
  }
}

//**********************************************************************

CnrGroupWeighted::FloatVector CnrGroupWeighted::
getCorrection(const IndexVector& channels, const AdcChannelDataMap& acds,
              const FloatMap& wts) const {
  const string myname = "CnrGroupWeighted::getCorrection: ";
  Index nsam = 0;
  std::vector<FloatVector> wsamples;
  for ( Index ich : channels ) {
    if ( wts.count(ich) == 0 ) continue;
    float wt = wts.find(ich)->second;
    auto iacd = acds.find(ich);
    if ( iacd == acds.end() ) continue;
    const AdcChannelData& acd = iacd->second;
    if ( m_requireGoodChannel && acd.channelStatus() ) continue;
    if ( acd.samples.size() > nsam ) {
      nsam = acd.samples.size();
      wsamples.resize(nsam);
    }
    for ( size_t isam=0; isam<acd.samples.size(); ++isam ) {
      if ( m_dropSignal && acd.signal.size()>isam && acd.signal[isam] ) continue;
      if ( wt == 0 ) continue;
      wsamples[isam].push_back(acd.samples[isam]/wt);
    }
  }
  std::vector<float> correction(nsam, 0.0);
  Index nsamCor = 0;
  for ( Index isam=0; isam<nsam; ++isam ) {
    size_t nval = wsamples[isam].size();
    if ( nval < 2 ) continue;
    if ( m_useMedian ) {
      std::sort(wsamples[isam].begin(), wsamples[isam].end());
      if ( nval%2 == 0 ) correction[isam] = 0.5 * (wsamples[isam][nval/2-1] + wsamples[isam][nval/2]);
      else correction[isam] = wsamples[isam][nval/2];
    } else {
      float sum = 0.0;
      for ( float val : wsamples[isam] ) sum += val;
      correction[isam] = sum/float(wsamples[isam].size());
    }
    ++nsamCor;
  }
  if ( m_LogLevel >= 2 ) cout << myname << "Correcting " << nsamCor << "/" << nsam << " samples." << endl;
  return correction;
}

//**********************************************************************

DEFINE_ART_CLASS_TOOL(CnrGroupWeighted)
