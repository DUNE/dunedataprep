# dunetpc/dune/DataPrep/WctTool/test/CMakeLists.txt

# David Adams
# March 2023

# Build test for each tool.

include(CetTest)

cet_test(test_wirecell
  SOURCES
    test_wirecell.cxx
  LIBRARIES
    WireCellSigProc
    dunecore_ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp
    cetlib::cetlib cetlib_except
    cetlib_except::cetlib_except
    SQLITE3
    Boost::filesystem
    ROOT_BASIC_LIB_LIST
)

cet_enable_asserts()
