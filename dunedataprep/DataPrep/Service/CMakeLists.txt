# dunetpc/dune/DataPrep/Service/CMakeLists.txt

# David Adams
# May 2016

# Add plugin for each service.

include_directories(AFTER $ENV{VALGRIND_INC})

cet_build_plugin(ConfigurableAdcChannelDataCopyService   art::service LIBRARIES
                dunecore::ArtSupport
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(InterpolatingAdcMitigationService   art::service LIBRARIES
                dunecore::ArtSupport
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(StandardRawDigitExtractService   art::service LIBRARIES
                dunecore::ArtSupport
                lardataobj::RawData
                larevt::CalibrationDBI_Providers
                larcore::headers
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(ThresholdNoiseRemovalService   art::service LIBRARIES
                dunecore::ArtSupport
                larcorealg::Geometry
                larcore::headers
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(MultiChannelNoiseRemovalService   art::service LIBRARIES
                dunecore::ArtSupport
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(DuneDPhase3x1x1NoiseRemovalService   art::service LIBRARIES
                dunecore::ArtSupport
                larevt::CalibrationDBI_Providers
                larcorealg::Geometry
                larcore::headers
                lardata::Utilities
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
                ROOT::FFTW
                lardataobj::RawData
             )

cet_build_plugin(MedianPedestalService   art::service LIBRARIES
                dunecore::ArtSupport
                larcore::headers
		art::Framework_Services_Registry
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcSuppressSignalFindingService art::service LIBRARIES
                dunecore::ArtSupport
                larcoreobj::headers
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(DuneDeconvolutionService art::service LIBRARIES
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
                dunecore::SignalShapingServiceDUNE_service
             )

cet_build_plugin(DuneDPhaseDeconvolutionService art::service LIBRARIES
		lardata::Utilities
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
                dunecore::SignalShapingServiceDUNEDPhase_service
             )

cet_build_plugin(KeepAllRoiBuildingService art::service LIBRARIES
                dunecore::ArtSupport
                larcoreobj::headers
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(DuneRoiBuildingService art::service LIBRARIES
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
                dunecore::SignalShapingServiceDUNE_service
             )

cet_build_plugin(DuneDPhaseRoiBuildingService art::service LIBRARIES
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
                dunecore::SignalShapingServiceDUNEDPhase_service
             )

cet_build_plugin(StandardAdcWireBuildingService art::service LIBRARIES
                dunecore::ArtSupport
                dunecore::ArtSupport
                lardataobj::RecoBase
                lardata::ArtDataHelper
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(ToolBasedRawDigitPrepService   art::service LIBRARIES
                dunecore::ArtSupport
                lardataobj::RawData
                lardataobj::RecoBase
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(TpcToolBasedRawDigitPrepService   art::service LIBRARIES
                dunecore::DuneInterface_Data
                dunecore::ArtSupport
                lardataobj::RawData
                lardataobj::RecoBase
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(StandardRawDigitPrepService   art::service LIBRARIES
                dunecore::ArtSupport
                larevt::CalibrationDBI_Providers
                larcore::headers
                lardataobj::RawData
                lardataobj::RecoBase
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

add_subdirectory(test)

install_source()
