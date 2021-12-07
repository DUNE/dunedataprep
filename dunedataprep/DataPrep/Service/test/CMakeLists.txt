# dunetpc/dune/DataPrep/Service/test/CMakeLists.txt

# David Adams
# May 2016

# Build test for each service.

include(CetTest)

cet_enable_asserts()

cet_test(test_ConfigurableAdcChannelDataCopyService
  SOURCES
    test_ConfigurableAdcChannelDataCopyService.cxx
  LIBRARIES
    dune_ArtSupport
    art::Utilities
    canvas::canvas
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)

cet_test(test_StandardRawDigitExtractService
  SOURCES
    test_StandardRawDigitExtractService.cxx
  LIBRARIES
    dune_ArtSupport
    lardataobj_RawData
    art::Utilities
    canvas::canvas
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)

cet_test(test_InterpolatingAdcMitigationService
  SOURCES
    test_InterpolatingAdcMitigationService.cxx
  LIBRARIES
    dune_ArtSupport
    art::Utilities
    canvas::canvas
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)

cet_test(test_ThresholdNoiseRemovalService
  SOURCES
    test_ThresholdNoiseRemovalService.cxx
  LIBRARIES
    dune_ArtSupport
    art::Utilities
    canvas::canvas
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)

cet_test(test_MultiChannelNoiseRemovalService
  SOURCES
    test_MultiChannelNoiseRemovalService.cxx
  LIBRARIES
    dune_ArtSupport
    art::Utilities
    canvas::canvas
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)

cet_test(test_MedianPedestalService
  SOURCES
    test_MedianPedestalService.cxx
  LIBRARIES
    dune_ArtSupport
    art::Utilities
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)

cet_test(test_AdcSuppressSignalFindingService
  SOURCES
    test_AdcSuppressSignalFindingService.cxx
  LIBRARIES
    dune_ArtSupport
    art::Utilities
    canvas::canvas
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)

cet_test(test_DuneDeconvolutionService
  SOURCES
    test_DuneDeconvolutionService.cxx
  LIBRARIES
    SignalShapingServiceDUNE_service
    dune_ArtSupport
    art::Utilities
    canvas::canvas
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)

cet_test(test_KeepAllRoiBuildingService
  SOURCES
    test_KeepAllRoiBuildingService.cxx
  LIBRARIES
    dune_ArtSupport
    art::Utilities
    canvas::canvas
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)

cet_test(test_DuneRoiBuildingService
  SOURCES
    test_DuneRoiBuildingService.cxx
  LIBRARIES
    dune_DataPrep_Service_DuneRoiBuildingService_service
    dune_ArtSupport
    art::Utilities
    canvas::canvas
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)

cet_test(test_StandardAdcWireBuildingService
  SOURCES
    test_StandardAdcWireBuildingService.cxx
  LIBRARIES
    dune_ArtSupport
    lardataobj_RawData
    art::Utilities
    canvas::canvas
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)

cet_test(test_StandardRawDigitPrepService
  SOURCES
    test_StandardRawDigitPrepService.cxx
  LIBRARIES
    dune_ArtSupport
    lardataobj_RawData
    art::Utilities
    canvas::canvas
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)

cet_test(test_ToolBasedRawDigitPrepService
  SOURCES
    test_ToolBasedRawDigitPrepService.cxx
  LIBRARIES
    dune_ArtSupport
    lardataobj_RawData
    art::Utilities
    canvas::canvas
    ROOT_HIST
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)

cet_test(test_TpcToolBasedRawDigitPrepService
  SOURCES
    test_TpcToolBasedRawDigitPrepService.cxx
  LIBRARIES
    dune_ArtSupport
    lardataobj_RawData
    art::Utilities
    canvas::canvas
    ROOT_HIST
    ART_FRAMEWORK_SERVICES_REGISTRY
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT_BASIC_LIB_LIST
)
