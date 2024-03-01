# dunetpc/dune/DataPrep/TpcTool/test/CMakeLists.txt

# David Adams
# February 2021

# Build test for each tool.

include(CetTest)

cet_test(test_AdcToRoi2d SOURCE test_AdcToRoi2d.cxx
  LIBRARIES
    dunecore::DuneInterface_Data
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_Roi2dToAdc SOURCE test_Roi2dToAdc.cxx
  LIBRARIES
    dunecore::DuneInterface_Data
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_Tpc2dDeconvolute SOURCE test_Tpc2dDeconvolute.cxx
  LIBRARIES
    dunecore::DuneCommon_Utility
    dunecore::DuneInterface_Data
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_enable_asserts()
