# dunetpc/dune/DataPrep/TpcTool/CMakeLists.txt

# David Adams
# February 2021
#
# Tools that act on TpcData.
#
# Add plugin for each tool.

cet_build_plugin(AdcToRoi2d   art::tool
                dunecore_DuneInterface_Data
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT::Core
             )

cet_build_plugin(Roi2dToAdc   art::tool
                dunecore_DuneInterface_Data
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT::Core
             )

cet_build_plugin(Tpc2dDeconvolute   art::tool
                dunecore_DuneInterface_Data
                dunecore_DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT::Core
             ) ### MIGRATE-ACTION-RECOMMENDED (migrate-3.22.02) - deprecated: use cet_build_plugin() with explicit source lists and plugin base types

add_subdirectory(test)
install_source()

