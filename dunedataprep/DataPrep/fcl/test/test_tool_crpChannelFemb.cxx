// test_tool_crpChannelFemb.cxx

// David Adams
// May 2023
//
// Test for tool instance crpChannelFemb.

#include "dunecore/DuneInterface/Tool/IndexMapTool.h"
#include "dunecore/ArtSupport/DuneToolManager.h"
#include <string>
#include <iostream>
#include <map>

using std::string;
using std::cout;
using std::endl;
using std::map;

using Index = unsigned int;

#undef NDEBUG
#include <cassert>

int test_tool_crpChannelFemb() {

  string line = "-------------------------------------------------------";
  string fclnam = "vdcb2_tools.fcl";
  string tnam = "crpChannelFemb";
  cout << "Testing tool " << tnam << " in fcl file " << fclnam << endl;

  cout << line << endl;
  cout << "Creating tool manager from fcl " << fclnam << endl;
  DuneToolManager* ptm = DuneToolManager::instance(fclnam);

  cout << line << endl;
  cout << "Fetching tool " << tnam << " from tool manager." << endl;
  auto ptoo = ptm->getPrivate<IndexMapTool>(tnam);
  assert( ptoo != nullptr );

  cout << line << endl;
  cout << "Looping over channels." << endl;
  Index nchan = 3072;
  map<Index, Index> fembChanCount;
  Index fmin = 1;
  Index fmax = 24;
  for ( Index icha=0; icha<nchan; ++icha ) {
    Index ifmb = ptoo->get(icha);
    if ( fembChanCount.count(ifmb) == 0 ) {
      cout << "Adding FEMB " << ifmb << endl;
      fembChanCount[ifmb] = 0;
    }
    assert( ifmb >= fmin );
    assert( ifmb <= fmax );
    ++fembChanCount[ifmb];
  }

  cout << line << endl;
  cout << "Checking FEMB channel counts." << endl;
  for ( auto ent : fembChanCount ) {
    Index ifmb = ent.first;
    Index count = ent.second;
    cout << "FEMB " << ifmb << " has " << count << " channels." << endl;
    assert( count == 128 );
  }

  cout << line << endl;
  cout << "All tests pass." << endl;
  return 0;
}

int main() {
  return test_tool_crpChannelFemb();
}
