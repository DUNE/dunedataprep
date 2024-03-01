
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
			art::Persistency_Common
			art::Persistency_Provenance
			art::Utilities canvas::canvas
			messagefacility::MF_MessageLogger
			art_root_io::tfile_support
	                fhiclcpp::fhiclcpp
			cetlib::cetlib cetlib_except::cetlib_except
        )

# install_headers()
install_fhicl()
install_source()

