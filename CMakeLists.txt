# ======================================================================
#  dunedataprep main build file
# ======================================================================


cmake_minimum_required (VERSION 3.12...3.19 FATAL_ERROR)

# cetbuildtools contains our cmake modules
find_package(cetbuildtools REQUIRED)

project(dunedataprep VERSION 09.41.00.02 LANGUAGES CXX)

include(CetCMakeEnv)
cet_cmake_env()

cet_cmake_module_directories(Modules BINARY)

cet_set_compiler_flags(DIAGS CAUTIOUS
  WERROR
  NO_UNDEFINED
  EXTRA_FLAGS -pedantic -Wno-unused-local-typedefs
)

cet_report_compiler_flags()

find_ups_product( art )
find_ups_product( art_root_io )
find_ups_product( canvas_root_io )
find_ups_boost( )
find_ups_root()
find_ups_product( cetbuildtools )
find_package( dunecore REQUIRED )
find_ups_product( fftw )
find_ups_geant4( )
find_ups_product( dunecore )
find_ups_product( larevt )
find_ups_product( larcore )
find_ups_product( larcoreobj )
find_ups_product( larcorealg )
find_ups_product( lardata )
find_ups_product( lardataalg )
find_ups_product( lardataobj )

include(MakeDuneToolBuilder)
include(dunecore::ToolTypes) # Enable simpler building of tools.

# Define an export set for tool support to enable simpler per-tool build
# call.
cet_register_export_set(SET_NAME PluginTypes NAMESPACE art_plugin_types)

# macros for artdaq_dictionary and simple_plugin
include(ArtDictionary)
include(ArtMake)
include(BuildPlugins)

add_subdirectory(dunedataprep)
add_subdirectory(ups)

include(UseCPack)
