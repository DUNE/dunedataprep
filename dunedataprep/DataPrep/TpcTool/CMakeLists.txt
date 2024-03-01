# dunetpc/dune/DataPrep/TpcTool/CMakeLists.txt

# David Adams
# February 2021
#
# Tools that act on TpcData.
#
# Add plugin for each tool.

cet_build_plugin(AdcToRoi2d   art::tool LIBRARIES
                dunecore::DuneInterface_Data
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(Roi2dToAdc   art::tool LIBRARIES
                dunecore::DuneInterface_Data
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(Tpc2dDeconvolute   art::tool LIBRARIES
                dunecore::DuneInterface_Data
                dunecore::DuneCommon_Utility
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

add_subdirectory(test)
install_source()

