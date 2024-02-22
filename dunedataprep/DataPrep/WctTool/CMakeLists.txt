# dunetpc/dune/DataPrep/WctTool/CMakeLists.txt

# David Adams
# March 2023

#cet_build_plugin(WctDataprepTool art::tool
#                 WireCellSigProc
#                )

find_library( WIRECELL_SIGPROC_LIB NAMES WireCellSigProc PATHS ${WIRECELL_LIB} NO_DEFAULT_PATH ) ### MIGRATE-ACTION-REQUIRED (migrate-3.22.02) - avoid: use find_package() with custom Find<pkg>.cmake for Spack compatibility
find_library( WIRECELL_IFACE_LIB NAMES WireCellIface PATHS ${WIRECELL_LIB} NO_DEFAULT_PATH ) ### MIGRATE-ACTION-REQUIRED (migrate-3.22.02) - avoid: use find_package() with custom Find<pkg>.cmake for Spack compatibility
find_library( WIRECELL_UTIL_LIB NAMES WireCellUtil PATHS ${WIRECELL_LIB} NO_DEFAULT_PATH ) ### MIGRATE-ACTION-REQUIRED (migrate-3.22.02) - avoid: use find_package() with custom Find<pkg>.cmake for Spack compatibility
find_library( WIRECELL_APPS_LIB NAMES WireCellApps PATHS ${WIRECELL_LIB} NO_DEFAULT_PATH ) ### MIGRATE-ACTION-REQUIRED (migrate-3.22.02) - avoid: use find_package() with custom Find<pkg>.cmake for Spack compatibility
set(WIRECELL_LIBS ${WIRECELL_APPS_LIB} ${WIRECELL_SIGPROC_LIB} ${WIRECELL_IFACE_LIB} ${WIRECELL_UTIL_LIB} jsoncpp::jsoncpp)

add_subdirectory(test)
