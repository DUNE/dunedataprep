# dunetpc/dune/DataPrep/TpcTool/test/CMakeLists.txt

# David Adams
# February 2021

# Build test for each tool.

include(CetTest)

cet_test(test_AdcToRoi2d SOURCES test_AdcToRoi2d.cxx
  LIBRARIES
    dune_DuneInterface_Data
    dune_ArtSupport
    art_Utilities
    canvas
    fhiclcpp
    cetlib cetlib_except
    cetlib_except
    ${SQLITE3}
    ${Boost_FILESYSTEM_LIBRARY}
)

cet_test(test_Roi2dToAdc SOURCES test_Roi2dToAdc.cxx
  LIBRARIES
    dune_DuneInterface_Data
    dune_ArtSupport
    art_Utilities
    canvas
    fhiclcpp
    cetlib cetlib_except
    cetlib_except
    ${SQLITE3}
    ${Boost_FILESYSTEM_LIBRARY}
)

cet_enable_asserts()