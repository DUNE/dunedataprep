// test_CnrGroupWeighted.cxx
//
// David Adams
// April 2019
//
// Test CnrGroupWeighted.

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "dune/DuneInterface/Tool/TpcDataTool.h"
#include "dune/DuneCommon/Utility/SampleTailer.h"
#include "dune/ArtSupport/DuneToolManager.h"
#include "TRandom.h"

#undef NDEBUG
#include <cassert>

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::istringstream;
using std::setw;
using std::fixed;
using std::setprecision;
using fhicl::ParameterSet;

using Index = unsigned int;
using IndexVector = std::vector<Index>;
using FloatVector = AdcSignalVector;

//**********************************************************************

void showSamples(const AdcChannelDataMap& acds, string pre) {
  for ( const auto& iacd : acds ) {
    cout << pre << setw(2) << iacd.first << ":";
    for ( float sam : iacd.second.samples ) {
      cout << setw(9) << fixed << setprecision(2) << sam;
    }
    cout << endl;
  }
}

//**********************************************************************

int test_CnrGroupWeighted(bool useExistingFcl) {
  const string myname = "test_CnrGroupWeighted: ";
#ifdef NDEBUG
  cout << myname << "NDEBUG must be off." << endl;
  abort();
#endif
  string line = "-----------------------------";

  cout << myname << line << endl;
  string fclfile = "test_CnrGroupWeighted.fcl";
  if ( ! useExistingFcl ) {
    ofstream fout(fclfile.c_str());
    fout << "tools: {" << endl;
    fout << "  mytool: {" << endl;
    fout << "     tool_type: CnrGroupWeighted" << endl;
    fout << "      LogLevel: 2" << endl;
    fout << "        Groups: [\"grpa:0:5\", \"grpb:5:10\"]" << endl;
    fout << "       Options: []" << endl;
    fout << "  }" << endl;
    fout << "}" << endl;
    fout.close();
  } else {
    cout << myname << "Using existing top-level FCL." << endl;
  }

  cout << myname << line << endl;
  cout << myname << "Fetching tool manager." << endl;
  DuneToolManager* ptm = DuneToolManager::instance(fclfile);
  assert ( ptm != nullptr );
  DuneToolManager& tm = *ptm;
  tm.print();
  assert( tm.toolNames().size() == 1 );

  cout << myname << line << endl;
  cout << myname << "Fetching tool." << endl;
  auto ptoo = tm.getPrivate<TpcDataTool>("mytool");
  assert( ptoo != nullptr );

  cout << myname << line << endl;
  cout << myname << "Create channel data." << endl;
  AdcChannelDataMap acds;
  float noiseSigma = 0.5;
  for ( Index icha=0; icha<10; ++icha ) {
    float off = icha < 5 ? 10 : 20;
    for ( Index isam=0; isam<8; ++isam ) {
      acds[icha].samples.push_back(gRandom->Gaus(off, noiseSigma));
      acds[icha].setChannelInfo(icha, 0, icha, 0);
    }
  }
  showSamples(acds, myname);

  cout << myname << line << endl;
  cout << myname << "Call tool." << endl;
  DataMap ret = ptoo->updateMap(acds);
  showSamples(acds, myname);

  cout << myname << "Done." << endl;
  return 0;
}

//**********************************************************************

int main(int argc, char* argv[]) {
  bool useExistingFcl = false;
  if ( argc > 1 ) {
    string sarg(argv[1]);
    if ( sarg == "-h" ) {
      cout << "Usage: " << argv[0] << " [ARG]" << endl;
      cout << "  If ARG = true, existing FCL file is used." << endl;
      return 0;
    }
    useExistingFcl = sarg == "true" || sarg == "1";
  }
  return test_CnrGroupWeighted(useExistingFcl);
}

//**********************************************************************
