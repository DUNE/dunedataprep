# dunetpc/dune/DataPrep/WctTool/CMakeLists.txt

# David Adams
# March 2023

#cet_build_plugin(WctDataprepTool art::tool
#                 WireCellSigProc
#                )

cet_find_library( WIRECELL_SIGPROC_LIB NAMES WireCellSigProc PATHS ENV WIRECELL_LIB NO_DEFAULT_PATH )
cet_find_library( WIRECELL_IFACE_LIB NAMES WireCellIface PATHS ENV WIRECELL_LIB NO_DEFAULT_PATH )
cet_find_library( WIRECELL_UTIL_LIB NAMES WireCellUtil PATHS ENV WIRECELL_LIB NO_DEFAULT_PATH )
cet_find_library( WIRECELL_APPS_LIB NAMES WireCellApps PATHS ENV WIRECELL_LIB NO_DEFAULT_PATH )
cet_find_library( JSONCPP_LIBS NAMES jsoncpp PATHS ENV JSONCPP_LIB NO_DEFAULT_PATH )
set(WIRECELL_LIBS ${WIRECELL_APPS_LIB} ${WIRECELL_SIGPROC_LIB} ${WIRECELL_IFACE_LIB} ${WIRECELL_UTIL_LIB} ${JSON_CPP_LIBS})

add_subdirectory(test)
