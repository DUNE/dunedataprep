# dunetpc/dune/DataPrep/Service/CMakeLists.txt

# David Adams
# May 2016

# Add plugin for each service.

include_directories(AFTER $ENV{VALGRIND_INC})

cet_build_plugin(ConfigurableAdcChannelDataCopyService   art::service
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(InterpolatingAdcMitigationService   art::service
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(StandardRawDigitExtractService   art::service
                dunecore_ArtSupport
                lardataobj_RawData
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(ThresholdNoiseRemovalService   art::service
                larcorealg_Geometry
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(MultiChannelNoiseRemovalService   art::service
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(DuneDPhase3x1x1NoiseRemovalService   art::service
                dunecore_ArtSupport
                larcorealg_Geometry
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
                ROOT_FFTW
                lardataobj_RawData
             )

cet_build_plugin(MedianPedestalService   art::service
		ART_FRAMEWORK_SERVICES_REGISTRY
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcSuppressSignalFindingService art::service
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(DuneDeconvolutionService art::service
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
                dunecore::SignalShapingServiceDUNE_service
             )

cet_build_plugin(DuneDPhaseDeconvolutionService art::service
		lardata_Utilities
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
                dunecore::SignalShapingServiceDUNEDPhase_service
             )

cet_build_plugin(KeepAllRoiBuildingService art::service
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(DuneRoiBuildingService art::service
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
                dunecore::SignalShapingServiceDUNE_service
             )

cet_build_plugin(DuneDPhaseRoiBuildingService art::service
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
                dunecore::SignalShapingServiceDUNEDPhase_service
             )

cet_build_plugin(StandardAdcWireBuildingService art::service
                lardataobj_RecoBase
                lardata_ArtDataHelper
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(ToolBasedRawDigitPrepService   art::service
                dunecore_ArtSupport
                lardataobj_RawData
                lardataobj_RecoBase
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(TpcToolBasedRawDigitPrepService   art::service
                dunecore_DuneInterface_Data
                dunecore_ArtSupport
                lardataobj_RawData
                lardataobj_RecoBase
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(StandardRawDigitPrepService   art::service
                dunecore_ArtSupport
                lardataobj_RawData
                lardataobj_RecoBase
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

add_subdirectory(test)

install_source()
