
art_make( BASENAME_ONLY
          MODULE_LIBRARIES larcorealg::Geometry
	                dunecore::Geometry
			larcore::Geometry_Geometry_service
	                lardata::Utilities
			larevt::Filters
			lardataobj::RawData
			lardataobj::RecoBase
			lardata::ArtDataHelper
			lardataalg::DetectorInfo
			dunecore::SignalShapingServiceDUNEDPhase_service
                        dunecore::SignalShapingServiceDUNE_service
			ROOT::Core
			ROOT::Gpad
			art::Persistency_Common canvas
			art::Persistency_Provenance canvas
			art::Utilities canvas
			messagefacility::MF_MessageLogger
			art_root_io::tfile_support
	                fhiclcpp::fhiclcpp
			cetlib::cetlib cetlib_except
        ) ### MIGRATE-ACTION-RECOMMENDED (migrate-3.22.02) - deprecated: use art_make_library(), art_dictonary(), and cet_build_plugin() with explicit source lists and plugin base types

# install_headers()
install_fhicl()
install_source()

