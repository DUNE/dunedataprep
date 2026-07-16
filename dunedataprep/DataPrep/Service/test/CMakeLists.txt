#dunetpc/dune/DataPrep/Service/test/CMakeLists.txt

# David Adams
# May 2016

# Build test for each service.

include(CetTest)

cet_enable_asserts()

cet_transitive_paths(FHICL_DIR BINARY IN_TREE)
cet_test_env_prepend(FHICL_FILE_PATH "." ${TRANSITIVE_PATHS_WITH_FHICL_DIR} ${PROJECT_BINARY_DIR}/fcl ${dunecalib_BINARY_DIR}/fcl ${dunesim_BINARY_DIR}/fcl ${dunesw_BINARY_DIR}/fcl ${duneopdet_BINARY_DIR}/fcl ${duneprototypes_BINARY_DIR}/fcl)
cet_transitive_paths(LIBRARY_DIR BINARY IN_TREE)
cet_test_env_prepend(CET_PLUGIN_PATH ${TRANSITIVE_PATHS_WITH_LIBRARY_DIR})
cet_test_env_prepend(FW_SEARCH_APTH ${PROJECT_BINARY_DIR}/fcl)

cet_test(test_ConfigurableAdcChannelDataCopyService
  SOURCE
    test_ConfigurableAdcChannelDataCopyService.cxx
  LIBRARIES
    dunecore::ArtSupport
    lardataobj::RawData
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_StandardRawDigitExtractService
  SOURCE
    test_StandardRawDigitExtractService.cxx
  LIBRARIES
    dunecore::ArtSupport
    lardataobj::RawData
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_InterpolatingAdcMitigationService
  SOURCE
    test_InterpolatingAdcMitigationService.cxx
  LIBRARIES
    dunecore::ArtSupport
    lardataobj::RawData
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_ThresholdNoiseRemovalService
  SOURCE
    test_ThresholdNoiseRemovalService.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    art::Framework_Services_Registry
    cetlib::cetlib
    ROOT::Core
)

cet_test(test_MultiChannelNoiseRemovalService
  SOURCE
    test_MultiChannelNoiseRemovalService.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_MedianPedestalService
  SOURCE
    test_MedianPedestalService.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_AdcSuppressSignalFindingService
  SOURCE
    test_AdcSuppressSignalFindingService.cxx
  LIBRARIES
    dunecore::ArtSupport
    lardataobj::RawData
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_DuneDeconvolutionService
  SOURCE
    test_DuneDeconvolutionService.cxx
  LIBRARIES
    dunecore::SignalShapingServiceDUNE_service
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_KeepAllRoiBuildingService
  SOURCE
    test_KeepAllRoiBuildingService.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Framework_Services_Registry
    art::Utilities
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_DuneRoiBuildingService
  SOURCE
    test_DuneRoiBuildingService.cxx
  LIBRARIES
    dunedataprep_DataPrep_Service_DuneRoiBuildingService_service
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_StandardAdcWireBuildingService
  SOURCE
    test_StandardAdcWireBuildingService.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Framework_Services_Registry
    lardataobj::RawData
    art::Utilities
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_StandardRawDigitPrepService
  SOURCE
    test_StandardRawDigitPrepService.cxx
  LIBRARIES
    dunecore::ArtSupport
    lardataobj::RawData
    lardata::Utilities
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_ToolBasedRawDigitPrepService
  SOURCE
    test_ToolBasedRawDigitPrepService.cxx
  LIBRARIES
    dunecore::ArtSupport
    lardataobj::RawData
    lardata::Utilities
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    ROOT::Hist
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_TpcToolBasedRawDigitPrepService
  SOURCE
    test_TpcToolBasedRawDigitPrepService.cxx
  LIBRARIES
    dunecore::ArtSupport
    lardataobj::RawData
    lardata::Utilities
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    ROOT::Hist
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)
