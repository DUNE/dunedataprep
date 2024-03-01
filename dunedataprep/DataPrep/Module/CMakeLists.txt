
art_make( BASENAME_ONLY
          MODULE_LIBRARIES larcorealg::Geometry
	                dunecore::Geometry
	                dunecore::DuneCommon_Utility
	                dunecore::ArtSupport
			larcore::Geometry_Geometry_service
	                lardata::Utilities
			larevt::Filters
			lardataobj::RawData
			lardataobj::RecoBase
			lardata::ArtDataHelper
			dunecore::SignalShapingServiceDUNEDPhase_service
                        dunecore::SignalShapingServiceDUNE_service
			ROOT::Core
			art::Persistency_Common
			art::Persistency_Provenance
			art::Utilities canvas::canvas
			messagefacility::MF_MessageLogger
			
	                fhiclcpp::fhiclcpp
			cetlib::cetlib cetlib_except::cetlib_except
        )

# install_headers()
install_fhicl()
install_source()

