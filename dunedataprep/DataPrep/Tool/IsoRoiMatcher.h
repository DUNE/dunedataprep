// IsoRoiMatcher.h
//
// Vyacheslav Galymov
// March, 2023
//
//
// Match (isolated) ROIs found in different planes and dump matched
// results to a ROOT file. 
// The groups of channels associated to readout planes of a tpcset
// should be specified via Sets argument. The format is <ind1>:<ind2>:<col>.
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
//  2) within time (tick) window specifed by MaxTDelta option
//
// Configuration:
//   LogLevel:  Log frequency: 0=none, 1=initialization, 2=every event
//   GroupSets: List of group plane sets in format <ind1>:<ind2>:<col>
//              Eg., cruCu:cruCv:cruCz for coldbox
//   MaxTDelta: Max number of ticks in peak separation -> m_MaxTDelta
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

  // filter isolated ROIs
  DataMap updateMap(AdcChannelDataMap& acds) const override;
  
 private:
  
  using Name         = std::string;
  using NameVector   = std::vector<Name>;
  using Index        = unsigned int;
  using IndexVector  = std::vector<Index>;
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
  //using ChInterceptsVector = std::vector<ChIntercepts>;
  using ChInterceptsMapVec  = std::vector<ChInterceptsMap>;

  //
  using GroupSet       = std::vector<ChGroup>;
  using GroupSetVector = std::vector<GroupSet>;
  
  int   m_LogLevel;
  Index m_MaxTDelta;
  GroupSetVector m_GroupSets;

  DetChInfoPtr m_DetChInfo;

  //
  // intercepts of collection channels with ch in other planes
  ChInterceptsMapVec m_ChIntercepts;
  
  //get
  void buildChGroupSets(const NameVector &sets);
  
  // built all possible intercept maps with
  void buildInterceptsMap();
  ChInterceptsMap buildRopIntercepts( IndexRange r, ChGroup g );
   
};



#endif
