#include "DetectorChannelInfo.h"

// 
#include <iostream>
#include <string>

// larsoft
#include "larcore/Geometry/Geometry.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

using std::cout;
using std::endl;
using std::string;

//
dataprep::util::
DetectorChannelInfo::DetectorChannelInfo( int loglevel ) : m_LogLevel(loglevel) 
{
  
  //
  // get geometry
  art::ServiceHandle<geo::Geometry> geo;
  
  //
  Index wid_cnt = 0;
  double xyz[3];   
  double abc[3];                                                                 
  for (auto const& wid : geo->Iterate<geo::WireID>()) {
    geo->WireEndPoints(wid,xyz,abc);
    auto chan=geo->PlaneWireToChannel(wid);
    std::cout << "FLAG " <<wid_cnt<< " " << chan << " " << wid << " " << xyz[0] << " " << xyz[1] << " " << xyz[2] <<  " " << abc[0] << " " << abc[1] << " " << abc[2] << std::endl;
    wid_cnt ++;
  }

  cout<<"total wires "<<wid_cnt<<endl;
  
}

//
dataprep::util::
DetectorChannelInfo::~DetectorChannelInfo()
{;}
