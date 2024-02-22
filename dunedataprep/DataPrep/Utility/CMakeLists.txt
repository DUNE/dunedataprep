# dunetpc/dune/DataPrep/Utility/CMakeLists.txt

find_library( WIRECELL_AUX_LIB     NAMES WireCellAux     PATHS ${WIRECELL_LIB} NO_DEFAULT_PATH ) ### MIGRATE-ACTION-REQUIRED (migrate-3.22.02) - avoid: use find_package() with custom Find<pkg>.cmake for Spack compatibility

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
         ${WIRECELL_AUX_LIB}
         NO_PLUGINS
        ) ### MIGRATE-ACTION-RECOMMENDED (migrate-3.22.02) - deprecated: use art_make_library(), art_dictonary(), and cet_build_plugin() with explicit source lists and plugin base types

install_source()
install_headers()

add_subdirectory(test)
