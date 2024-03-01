# dunetpc/dune/DataPrep/Utility/CMakeLists.txt

#find_library( WIRECELL_AUX_LIB     NAMES WireCellAux     PATHS ENV WIRECELL_LIB ${WIRECELL_LIB} NO_DEFAULT_PATH )
#include_directories($ENV{WIRECELL_INC})

art_make(BASENAME_ONLY
         LIB_LIBRARIES
         dunecore::ArtSupport
         dunecore::DuneCommon_Utility
	 larcorealg::Geometry
	 larcore::Geometry_Geometry_service	
         art::Utilities
	 art::Framework_Services_Registry
         canvas::canvas
         cetlib::cetlib
	 cetlib_except::cetlib_except
	 fhiclcpp::fhiclcpp
         WireCell::Aux
 #        ${WIRECELL_AUX_LIB}
         NO_PLUGINS
        )

install_source()
install_headers()

add_subdirectory(test)
