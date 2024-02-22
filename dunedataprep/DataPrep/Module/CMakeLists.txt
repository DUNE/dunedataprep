
art_make( BASENAME_ONLY
          MODULE_LIBRARIES larcorealg_Geometry
	                dunecore_Geometry
	                dunecore_DuneCommon_Utility
	                dunecore_ArtSupport
			larcore_Geometry_Geometry_service
	                lardata_Utilities
			larevt_Filters
			lardataobj_RawData
			lardataobj_RecoBase
			lardata_ArtDataHelper
			dunecore::SignalShapingServiceDUNEDPhase_service
                        dunecore::SignalShapingServiceDUNE_service
			ROOT::Core
			art::Persistency_Common canvas
			art::Persistency_Provenance canvas
			art::Utilities canvas
			messagefacility::MF_MessageLogger
			
	                fhiclcpp::fhiclcpp
			cetlib::cetlib cetlib_except
        ) ### MIGRATE-ACTION-RECOMMENDED (migrate-3.22.02) - deprecated: use art_make_library(), art_dictonary(), and cet_build_plugin() with explicit source lists and plugin base types

# install_headers()
install_fhicl()
install_source()

