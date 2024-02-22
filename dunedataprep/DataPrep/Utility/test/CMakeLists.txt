# dunetpc/dune/DataPrep/Utility/test/CMakeLists.txt

# David Adams
# June 2018

# Build test for each utility.

include(CetTest)

cet_test(test_StickyCodeMetrics SOURCES test_StickyCodeMetrics.cxx
  LIBRARIES
    dunedataprep_DataPrep_Utility
    canvas::canvas
    fhiclcpp
    cetlib::cetlib cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

