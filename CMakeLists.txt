# ======================================================================
#  dunedataprep main build file
# ======================================================================


cmake_minimum_required (VERSION 3.20 FATAL_ERROR) ### MIGRATE-CHANGED (migrate-3.22.02) - VERSION 3.12...3.19 -> 3.20
# cmake_policy(VERSION 3.19) ### MIGRATE-ACTION-COMPATIBILITY (migrate-3.22.02) - Uncomment to preserve compatibility with older CMake versions

# cetbuildtools contains our cmake modules
find_package(cetmodules REQUIRED) ### MIGRATE-CHANGED (migrate-3.22.02) - cetbuildtools -> cetmodules

project(dunedataprep LANGUAGES CXX)
set(${PROJECT_NAME}_CMAKE_PROJECT_VERSION_STRING 09.83.01d00)

include(CetCMakeEnv)
cet_cmake_env()

cet_cmake_module_directories(Modules BINARY)

cet_set_compiler_flags(DIAGS CAUTIOUS
  WERROR
  NO_UNDEFINED
  EXTRA_FLAGS -pedantic -Wno-unused-local-typedefs
)

cet_report_compiler_flags() ### MIGRATE-ACTION-RECOMMENDED (migrate-3.22.02) - add args: REPORT_THRESHOLD VERBOSE

find_package( art REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(art ...) -> find_package(art REQUIRED ...)
find_package( art_root_io REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(art_root_io ...) -> find_package(art_root_io REQUIRED ...)
find_package( canvas_root_io REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(canvas_root_io ...) -> find_package(canvas_root_io REQUIRED ...)
find_package( Boost REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(...) -> find_package(REQUIRED ...)
find_package(ROOT REQUIRED) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(...) -> find_package(REQUIRED ...)
find_package(SQLite3 REQUIRED)
find_package( dunecore REQUIRED )
find_package( FFTW3 REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(fftw ...) -> find_package(fftw REQUIRED ...)
find_package( Geant4 REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(...) -> find_package(REQUIRED ...)
find_package( dunecore REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(dunecore ...) -> find_package(dunecore REQUIRED ...)
find_package( larevt REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(larevt ...) -> find_package(larevt REQUIRED ...)
find_package( larcore REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(larcore ...) -> find_package(larcore REQUIRED ...)
find_package( larcoreobj REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(larcoreobj ...) -> find_package(larcoreobj REQUIRED ...)
find_package( larcorealg REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(larcorealg ...) -> find_package(larcorealg REQUIRED ...)
find_package( lardata REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(lardata ...) -> find_package(lardata REQUIRED ...)
find_package( lardataalg REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(lardataalg ...) -> find_package(lardataalg REQUIRED ...)
find_package( lardataobj REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(lardataobj ...) -> find_package(lardataobj REQUIRED ...)
find_package( larwirecell REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(larwirecell ...) -> find_package(larwirecell REQUIRED ...)
#find_package( wirecell REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(wirecell ...) -> find_package(wirecell REQUIRED ...)
find_package( jsoncpp REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(jsoncpp ...) -> find_package(jsoncpp REQUIRED ...)
find_package( spdlog REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(spdlog ...) -> find_package(spdlog REQUIRED ...)
find_package( Eigen3 REQUIRED ) ### MIGRATE-CHANGED (migrate-3.22.02) - find_ups_product(eigen ...) -> find_package(eigen REQUIRED ...)

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

cet_cmake_config() ### MIGRATE-ADDED (migrate-3.22.02) - required cmd
