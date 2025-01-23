# ======================================================================
#  dunedataprep main build file
# ======================================================================


cmake_minimum_required (VERSION 3.20 FATAL_ERROR)
# cmake_policy(VERSION 3.19)

# cetbuildtools contains our cmake modules
find_package(cetmodules REQUIRED)

project(dunedataprep LANGUAGES CXX)
set(${PROJECT_NAME}_CMAKE_PROJECT_VERSION_STRING 10.03.01d00)

include(CetCMakeEnv)
cet_cmake_env()

cet_cmake_module_directories(Modules BINARY)

cet_set_compiler_flags(DIAGS CAUTIOUS
  WERROR
  NO_UNDEFINED
  EXTRA_FLAGS -pedantic -Wno-unused-local-typedefs
)

cet_report_compiler_flags()

find_package( art REQUIRED EXPORT )
find_package( art_root_io REQUIRED EXPORT )
find_package( canvas_root_io REQUIRED EXPORT )
find_package( Boost REQUIRED )
find_package(ROOT REQUIRED)
find_package(SQLite3 REQUIRED)
find_package( nufinder REQUIRED )
find_package( FFTW3 REQUIRED EXPORT )
find_package( Geant4 REQUIRED EXPORT )
find_package( dunecore REQUIRED EXPORT )
find_package( dunepdlegacy REQUIRED EXPORT )
find_package( larevt REQUIRED EXPORT )
find_package( larcore REQUIRED EXPORT )
find_package( larcoreobj REQUIRED EXPORT )
find_package( larcorealg REQUIRED EXPORT )
find_package( lardata REQUIRED EXPORT )
find_package( lardataalg REQUIRED EXPORT )
find_package( lardataobj REQUIRED EXPORT )
find_package( larwirecell REQUIRED EXPORT )
find_package( WireCell REQUIRED EXPORT )
find_package( jsoncpp REQUIRED )
find_package( spdlog REQUIRED )
find_package( Eigen3 REQUIRED )

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

cet_cmake_config()
