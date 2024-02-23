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

include_directories(${EIGEN3_INCLUDE_DIR})

include(CetTest)


cet_test(test_wirecell
  SOURCES
    test_wirecell.cxx
  LIBRARIES
    dunecore_ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp
    cetlib::cetlib cetlib_except
    cetlib_except::cetlib_except
    SQLITE3
    Boost::filesystem
    ROOT_BASIC_LIB_LIST
    WIRECELL_LIBS
)

get_target_property(myincs test_wirecell INCLUDE_DIRECTORIES)
message("Include path for test_wirecell")
foreach(dir ${myincs})
  message("  ${dir}")
endforeach()

set(CMAKE_VERBOSE_MAKEFILE OFF)
cet_enable_asserts()
