# dunetpc/dune/DataPrep/Utility/CMakeLists.txt

#message($ENV)
message("Wirecell: ${WIRECELL_LIB}")
#cet_find_library( WIRECELL_AUX_LIB     NAMES WireCellAux     PATHS ENV WIRECELL_LIB NO_DEFAULT_PATH )
find_library(
  WIRECELL_AUX_LIB
  WireCellAux
  ENV WIRECELL_LIB
  NO_DEFAULT_PATH
)

art_make(BASENAME_ONLY
         LIB_LIBRARIES
         dunecore_ArtSupport
         dunecore_DuneCommon_Utility
	 larcorealg::Geometry
	 larcore::Geometry_Geometry_service	
         art::Utilities
	 art::Framework_Services_Registry
         canvas::canvas
         cetlib::cetlib
	 cetlib_except::cetlib_except
	 fhiclcpp
         ROOT_BASIC_LIB_LIST
         WIRECELL_AUX_LIB
         NO_PLUGINS
        )

install_source()
install_headers()

add_subdirectory(test)
