# dunetpc/dune/DataPrep/WctTool/test/CMakeLists.txt

# David Adams
# March 2023

# Build test for each tool.
set(CMAKE_VERBOSE_MAKEFILE ON)
get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

include_directories( $ENV{EIGEN_INC} )

include(CetTest)

cet_test(test_wirecell
  SOURCE
    test_wirecell.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
    WireCell::SigProc
    WireCell::Iface
    WireCell::Util
    WireCell::Apps
    Eigen3::Eigen
)

get_target_property(myincs test_wirecell INCLUDE_DIRECTORIES)
message("Include path for test_wirecell")
foreach(dir ${myincs})
  message("  ${dir}")
endforeach()

set(CMAKE_VERBOSE_MAKEFILE OFF)
cet_enable_asserts()
