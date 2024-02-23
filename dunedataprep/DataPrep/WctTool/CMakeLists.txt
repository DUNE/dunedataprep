# dunetpc/dune/DataPrep/WctTool/CMakeLists.txt

# David Adams
# March 2023

#cet_build_plugin(WctDataprepTool art::tool
#                 WireCellSigProc
#                )

find_library(
  WIRECELL_SIGPROC_LIB
  WireCellSigProc
  PATHS ENV WIRECELL_LIB
  NO_DEFAULT_PATH
)

find_library(
  WIRECELL_IFACE_LIB
  WireCellIface
  PATHS ENV WIRECELL_LIB
  NO_DEFAULT_PATH
)

find_library(
  WIRECELL_UTIL_LIB
  WireCellUtil
  PATHS ENV WIRECELL_LIB
  NO_DEFAULT_PATH
)

find_library(
  WIRECELL_APPS_LIB
  WireCellApps
  PATHS ENV WIRECELL_LIB
  NO_DEFAULT_PATH
)

find_library(
  JSONCPP_LIBS
  jsoncpp 
  PATHS ENV JSONCPP_LIB
  NO_DEFAULT_PATH
)

set(WIRECELL_LIBS ${WIRECELL_APPS_LIB} ${WIRECELL_SIGPROC_LIB} ${WIRECELL_IFACE_LIB} ${WIRECELL_UTIL_LIB} ${JSONCPP_LIBS})

add_subdirectory(test)
