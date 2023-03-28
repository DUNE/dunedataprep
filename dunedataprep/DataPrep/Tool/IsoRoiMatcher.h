// IsoRoiMatcher.h
//
// Vyacheslav Galymov
// March, 2023
//
//
// Match (isolated) ROIs found in different planes. The matched ROIs are saved
// for each channel while others are removed. 
//
// The groups of channels associated to readout planes of a tpcset
// should be specified via GroupSets argument. The format is <ind1>:<ind2>:<col>.
// The first sub-string <ind1> is interpeted as the group name for induction 1
// The second sub-string <ind2> is interpeted as the group name for induction 2
// The last sub-string <col> is interpeted as the group name for collection.
// It is also assumed that <ind1> is associated to ROP 0 in the channel map,
// the <ind2> to ROP 1, while the collection is ROP 2.
// The found ROIs in collection group are matched to ind1 and ind2 
// Then the results of two matches are compared to find "best" possible 
// combination of the three planes.
// To match the ROIs a tick cooridante of the pick in induction is required to be 
//  1) before the tick of the peak in collection
//  2) within time (tick) window specifed by MaxTDelta option. A negative value
//     will in addition require that pulses in the induction planes come before
//     the ones in collection.
//  3) The ROIs matched for col and ind1 and col and ind2 are then compare to
//     determine the intercept point on which all views agree. The MaxDist parameter
//     sets an acceptable tollerance (normally its value should be ~ind_pitch/2)
//
// Configuration:
//   LogLevel:  Log frequency: 0=none, 1=initialization, 2=every event
//   GroupSets: List of group plane sets in format <ind1>:<ind2>:<col>
//              Eg., cruCu:cruCv:cruCz for coldbox
//   MaxTDelta: Max number of ticks in peak separation -> m_MaxTDelta
//              A negative value specified here would in addition require
//              that an pulse in induction is before collection
//   MaxDist  : max distance tolerance for matching the intersect between
//              two iduction views in cm
//   AlignMode : tick alignment mode :
//                      "peak" - align on peak in the first plane
//                      "zerocrossing" - align on the tick of zero crossing
//                                       relevant for induction view
//   NRoiPreSamples : number of ticks to save before tick0 (see AlignMode)
//   NRoiTotSamples : number of total ticks in ROI windows (includes NRoiPreSample ticks)
//   OutputFile     : output file to optionally write out grouped ROIs to TTree
//
//

#ifndef IsoRoiMatcher_H
#define IsoRoiMatcher_H

#include "art/Utilities/ToolMacros.h"
#include "fhiclcpp/ParameterSet.h"
#include "dunecore/DuneInterface/Tool/TpcDataTool.h"
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "dunedataprep/DataPrep/Utility/DetectorChannelInfo.h"

//
class IsoRoiMatcher : TpcDataTool {
  
 public:
  
  // Ctor
  IsoRoiMatcher(fhicl::ParameterSet const& ps);

  // Dtor
  ~IsoRoiMatcher() override =default;

  // match isolated ROIs
  DataMap updateMap(AdcChannelDataMap& acds) const override;
  //DataMap viewMap(const AdcChannelDataMap& acds) const override;

 private:
  
  using Name         = std::string;
  using NameVector   = std::vector<Name>;
  using Index        = unsigned int;
  using IndexVector  = std::vector<Index>;
  using FloatVector  = std::vector<float>;
  using DetChInfo    = dataprep::util::DetectorChannelInfo;
  using DetChInfoPtr = std::unique_ptr<DetChInfo>;

  //
  using Point2d_t    = dataprep::util::Point2d_t;
  using IndexRange   = dataprep::util::IndexRange;

  struct ChGroup {
    Name name;
    Index ropid;
    IndexVector channels;
  };

  // structures to hold various levels of channel intercept information
  // in general a given readout channel could have multiple intercepts with
  // another readout channel from a different ROP

  // point intercepts
  struct ChIntercepts {
    
    //
    void add( Index ch, Point2d_t pnt){
      auto found = pmap.find(ch);
      if( found == pmap.end() ){ 
	std::vector<Point2d_t> v;
	pmap.insert( std::make_pair(ch, v) );
      }
      pmap[ch].push_back( pnt );
    }
    
    //
    std::vector<Point2d_t> get( Index ch ) const {
      std::vector<Point2d_t> v;
      auto found = pmap.find(ch);
      if( found == pmap.end() ){ return v; }
      return found->second;
    }
    
    friend std::ostream& operator<< (std::ostream &os, 
				     const ChIntercepts &pnts){
      for(auto const &[k, v]: pnts.pmap){
	for( auto const &p : v ){
	  os<<k<<" ["<<p.X()<<", "<<p.Y()<<"] ";
	}
      }
      return os;
    }
    
  private:
    std::unordered_map<Index, std::vector<Point2d_t>> pmap;
  };
  

  using ChInterceptsMap    = std::unordered_map<Index, ChIntercepts>;
  using ChInterceptsMapVec = std::vector<ChInterceptsMap>;

  //
  using GroupSet       = std::vector<ChGroup>;
  using GroupSetVector = std::vector<GroupSet>;
  
  // structure for a given ROI info
  struct ChRoi {
    Index chan;
    Index rid;
    Index tstart;
    Index tend;
    Index tmin;
    Index tmax;
    Index inuse;
    float delta;
    //float psum;
    //float pheight;
    std::vector<Point2d_t> ipnts; //intersection points

    friend std::ostream& operator<< (std::ostream &os, 
				     const ChRoi &roi){
      os<<roi.chan<<" "<<roi.rid<<" "
	<<roi.tstart<<" - "<<roi.tend<<" "
	<<roi.tmax<<" "<<roi.tmin<<" "
	<<roi.ipnts.size();
      return os;
    }

  };
  using ChRoiVector   = std::vector<ChRoi>;
  using ChRoiVector2d = std::vector<ChRoiVector>;

  //
  struct TreeData {
    Index event   =0;
    Index run     =0;
    Index channel =0;
    Index ropid   =0;
    Index grpid   =0;   //ID of grouped iso ROIs
    float coord1  =0.0; //CRP coordinate 1
    float coord2  =0.0; //CRP coordinate 2
    float cdelta  =0.0; //difference in coords from u/v planes
    Index isam =0;
    float qroi =0.0;
    float hmin =0.0;
    float hmax =0.0;
    Index nsa =0;
    FloatVector data;
  };

  //
  int   m_LogLevel;
  int   m_MaxTDelta;
  float m_MaxDist;
  std::string m_AlignMode;
  Index m_NRoiPreSamples;
  Index m_NRoiTotSamples;
  Name  m_OutFile;

  
  //
  GroupSetVector m_GroupSets;
  DetChInfoPtr   m_DetChInfo;

  //
  // intercepts of collection channels with ch in other planes
  ChInterceptsMapVec m_ChIntercepts;

  // matched ROIs, mutable since we clear it 
  // in the updateMap function
  //mutable ChRoiVector2d m_MatchedIsoRois;
  
  //
  Name treeName() const { return "isorois"; }
    
  //get
  void buildChGroupSets(const NameVector &sets);
  
  // built all possible intercept maps with
  void buildInterceptsMap();
  ChInterceptsMap buildRopIntercepts( IndexRange r, ChGroup g );

  //
  ChRoiVector buildRoisFrame(const IndexVector& channels, const AdcChannelDataMap& acds) const;
  ChRoiVector findRoiMatch( const ChRoi &col_roi, const ChRoiVector &ind_rois, 
			    const ChInterceptsMap &intercepts ) const;
  // find ROIs that match based on available geo info from intercept points
  // if successful returns vector of ROIs with size 2 where the first element is
  // taken from rois1 and the second from rois2
  ChRoiVector findRoiVecMatch( const ChRoiVector &rois1, const ChRoiVector &rois2 ) const;

  bool doCenterAndCrop( ChRoiVector &amatch, const AdcChannelDataMap& acds ) const ; 
  
  void prepOutfile() const;
  void writeTree( const ChRoiVector2d &matched_rois, const AdcChannelDataMap& acds) const;
};



#endif
