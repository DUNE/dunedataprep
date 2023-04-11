#include "AdcSumSignalFinder.h"

#include "dunecore/ArtSupport/DuneToolManager.h"
#include "dunecore/DuneInterface/Data/IndexRange.h"
#include "dunecore/DuneInterface/Data/IndexRangeGroup.h"
#include "dunecore/DuneInterface/Tool/IndexRangeGroupTool.h"
#include "dunedataprep/DataPrep/Utility/MathUtils.h"

#include <iostream>
#include <iomanip>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::setw;

//
// ctor
AdcSumSignalFinder::AdcSumSignalFinder(fhicl::ParameterSet const& ps): 
  m_LogLevel(ps.get<int>("LogLevel")) {

  //
  const string myname = "AdcSumSignalFinder::ctor: ";
  
  NameVector gnames   = ps.get<NameVector>("Groups");
  NameVector gmeths   = ps.get<NameVector>("GroupMethod");
  FloatVector gthresh = ps.get<FloatVector>("GroupThresh");
  Name DefMethod     = ps.get<Name>("DefaultMethod");
  float DefThresh    = ps.get<float>("DefaultThresh");
  m_SamplesToSum     = ps.get<Index>("SamplesToSum");
  m_SampleSumStep    = ps.get<Index>("SampleSumStep");

  if( DefThresh < 0 ){
    cout<<myname<<"ERROR in configuration threshold cannot be negative "<<endl;
    DefThresh = std::abs(DefThresh);
  }

  if( !gnames.empty() ){
    size_t gsz = gnames.size();
    if( gmeths.size() < gsz ){
      gmeths.resize( gsz, DefMethod );
    }
    if( gthresh.size() < gsz ){
      gthresh.resize( gsz, DefThresh );
    }
  }
  
  auto str_to_method = []( string val ){
     if( val == "sumabs" ) return SUMABS;
     else if( val == "sum" ) return SUM;
     return SUMABS;
  };

  m_DefConfig.first  = str_to_method( DefMethod );
  m_DefConfig.second = DefThresh;

  if( m_LogLevel >= 1){
    cout << myname << "  LogLevel: " << m_LogLevel << endl;
    cout << myname << "  Default sum mode   : "<<m_DefConfig.first<<endl;
    cout << myname << "  Default threshold  : "<<m_DefConfig.second<<endl;
    cout << myname << "  Number of samples to sum   : "<<m_SamplesToSum<<endl;
    cout << myname << "  NUmber of samples per step : "<<m_SampleSumStep<<endl;
  }

  //
  // Build the channel map from options.
  string crtName = "channelGroups";
  DuneToolManager* ptm = DuneToolManager::instance();
  const IndexRangeGroupTool* pcrt = ptm == nullptr ? nullptr : ptm->getShared<IndexRangeGroupTool>(crtName);
  int nerr = 0;
  for( Index igrp=0;igrp<gnames.size();++igrp){
    Name sgrp = gnames[igrp];
    IndexRangeGroup grp;
    if ( pcrt != nullptr ) grp = pcrt->get(sgrp);
    if ( ! grp.isValid() ) {
      grp = IndexRangeGroup(sgrp);
    }
    if ( ! grp.isValid() || grp.name.size() == 0 ) {
      cout << myname << "WARNING: Unable to find range group " << sgrp << endl;
      ++nerr;
    } else {
      IndexVector chans;
      grp.getIndices(chans);
      AlgoConfig ch_conf;
      ch_conf.first  = str_to_method( gmeths[igrp] );
      ch_conf.second = gthresh[ igrp ];
      if( ch_conf.second < 0 ){ ch_conf.second = std::abs(ch_conf.second); }
      if( m_LogLevel >= 1 ){
	cout << myname << "group "<< sgrp << " with "<<chans.size()
	     <<" chans uses "<< gmeths[igrp] << " algo "<< ch_conf.first 
	     <<" with threshold "<<ch_conf.second << endl;
      }
      for( Index ch: chans ){ m_ChConfigs.insert(std::make_pair(ch, ch_conf)); }
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

}

//
//
DataMap AdcSumSignalFinder::update(AdcChannelData &acd) const
{
  const string myname = "AdcSumSignalFinder::update: ";
  DataMap ret;
  if ( m_LogLevel >= 2 ) {
    cout << myname << "Finding ROIs for channel " << acd.channel() << endl;
  }
  auto nsam = acd.samples.size();
  if ( nsam == 0 ) {
    if( m_LogLevel >= 2 ){
      cout << myname << "ERROR: No samples found in channel " << acd.channel() << endl;
    }
    acd.signal.clear();
    acd.rois.clear();
    return ret.setStatus(1);
  }
  
  auto res = findChRois( acd.channel(), acd.samples );
  acd.signal = res.rois;
  acd.roisFromSignal();
  
  if ( m_LogLevel >= 3 ) {
    cout << myname << "  ROIs count (size = " << acd.rois.size() << "):" << endl;
    for ( const AdcRoi& roi : acd.rois ) {
      cout << myname << setw(8) << roi.first << " " << setw(8) << roi.second << endl;
    }
  } else if ( m_LogLevel >= 2 ) {
    cout << myname << "  ROIs count : " << acd.rois.size() << endl;
  }

  ret.setFloat("nsfPSumThreshold", res.thresh);  
  ret.setInt("nsfPSumRoiCount", acd.rois.size());

  acd.metadata["nsfPSumThreshold"] = res.thresh;
  acd.metadata["nsfPSumRoiCount"]  = acd.rois.size();

  return ret;
}

//
//
AdcSumSignalFinder::RoiResult 
AdcSumSignalFinder::findChRois( Index ch, const AdcSignalVector &vec ) const {
  const string myname = "AdcSumSignalFinder::findChRois: ";
  Index nsum = m_SamplesToSum;
  Index step = m_SampleSumStep;
  RoiResult res;
  res.thresh = -1;
  res.rois   = AdcFilterVector(vec.size(), false);

  if( vec.size() <= nsum ){
    cout<<myname<<"ERROR: the number of samples for "<<ch
	<<" is too small for this algorithm"<<endl;
    return res;
  }
  
  // make a copy for the internal manipulations
  AdcSignalVector samples( vec );
  
  // get configs
  AlgoConfig conf = getChConfig( ch );
  
  // convert to abs(sample) if selected
  if( conf.first == SUMABS ){
    std::transform(samples.cbegin(), samples.cend(), samples.begin(),
		   [](auto d){ return std::abs(d); });
  }
  // subtract median value
  float med = dataprep::util::find_median( samples );
  std::transform(samples.cbegin(), samples.cend(), samples.begin(),
		 [med](auto d){ return (d - med); });

    
  // find mean and rms
  float mean  = 0;
  float sigma = 0;
  
  {
    auto tsdata = dataprep::util::moving_sum(samples, nsum);
    auto stats  = dataprep::util::find_mean_and_rms_iqrfiltered(tsdata);
    mean = stats.first;
    sigma = stats.second;
  }
  
  float thresh = conf.second * sigma + mean;
  if( thresh < 0 ){ // should be positive
    thresh = conf.second * sigma;
  }
  // save threshold
  res.thresh = thresh;

  if( m_LogLevel >= 3 ){
      cout<<myname<<"mean = "<<mean<<endl;
      cout<<myname<<"rms  = "<<sigma<<endl;
      cout<<myname<<"threshold = "<<thresh<<endl;
    }
  

  //
  auto stepsum = dataprep::util::moving_sum( samples, step );
  Index nsteps = nsum / step;
  vector<float> sums;
  auto it  = stepsum.cbegin();
  auto end = stepsum.cend();
  while(it < end ){ // convolution
    auto nit = it + nsteps;
    if( nit > end ) nit = end;
    float s = std::reduce(it, nit);
    sums.push_back(s);
    it++;
  }

  // find indices with sums over threshold
  for(Index i=0;i<sums.size();i++){
    float sum = sums[i];
    if( sum < thresh ) continue;
    Index idx1 = i * step;
    Index idx2 = idx1 + nsum;
    std::fill( res.rois.begin()+idx1, res.rois.begin()+idx2, true);
  }
  
  return res;
}


//
AdcSumSignalFinder::AlgoConfig
AdcSumSignalFinder::getChConfig( Index ch ) const {
  
  if( m_ChConfigs.empty() ){
    return m_DefConfig;
  }

  auto found = m_ChConfigs.find( ch );
  if( found != m_ChConfigs.end() ){
    return found->second;
  }
  
  return m_DefConfig;
}


DEFINE_ART_CLASS_TOOL(AdcSumSignalFinder)
