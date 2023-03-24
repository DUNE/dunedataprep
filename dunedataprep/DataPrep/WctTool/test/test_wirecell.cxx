// test_wirecell.cxx
//
// David Adams
// March 2023
//
// Test access to wirecell code.

#include "WireCellSigProc/OmnibusSigProc.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#undef NDEBUG
#include <cassert>

using std::string;
using std::cout;
using std::endl;
using std::ostringstream;
using std::ofstream;
using std::vector;
using WireCell::SigProc::OmnibusSigProc;

//**********************************************************************

int test_wirecell() {
  const string myname = "test_wirecell: ";
#ifdef NDEBUG
  cout << myname << "NDEBUG must be off." << endl;
  abort();
#endif
  string line = "-----------------------------";

  cout << myname << line << endl;
  cout << myname << "Instantiate OmnibusSigProc." << endl;
  OmnibusSigProc osp;

  cout << myname << "Display default config." << endl;
  cout << osp.default_configuration() << endl;
  
  cout << myname << line << endl;
  cout << myname << "Done." << endl;
  return 0;
}

//**********************************************************************

int main(int argc, char* argv[]) {
  return test_wirecell();
}

//**********************************************************************
