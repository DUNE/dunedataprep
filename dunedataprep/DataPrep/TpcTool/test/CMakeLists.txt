# dunetpc/dune/DataPrep/TpcTool/test/CMakeLists.txt

# David Adams
# February 2021

# Build test for each tool.

include(CetTest)

cet_test(test_AdcToRoi2d SOURCES test_AdcToRoi2d.cxx
  LIBRARIES
    dunecore_DuneInterface_Data
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

cet_test(test_Roi2dToAdc SOURCES test_Roi2dToAdc.cxx
  LIBRARIES
    dunecore_DuneInterface_Data
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

cet_test(test_Tpc2dDeconvolute SOURCES test_Tpc2dDeconvolute.cxx
  LIBRARIES
    dunecore_DuneCommon_Utility
    dunecore_DuneInterface_Data
    dunecore_ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp
    cetlib::cetlib cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ${ROOT_BASIC_LIB_LIST}
)

cet_enable_asserts()
