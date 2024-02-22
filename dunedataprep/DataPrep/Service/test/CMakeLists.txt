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
    dunecore::ArtSupport
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_StandardRawDigitExtractService
  SOURCES
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
  SOURCES
    test_InterpolatingAdcMitigationService.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_ThresholdNoiseRemovalService
  SOURCES
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
  SOURCES
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
  SOURCES
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
  SOURCES
    test_AdcSuppressSignalFindingService.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_DuneDeconvolutionService
  SOURCES
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
  SOURCES
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
  SOURCES
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
  SOURCES
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
  SOURCES
    test_StandardRawDigitPrepService.cxx
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

cet_test(test_ToolBasedRawDigitPrepService
  SOURCES
    test_ToolBasedRawDigitPrepService.cxx
  LIBRARIES
    dunecore::ArtSupport
    lardataobj::RawData
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    ROOT::Hist
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)

cet_test(test_TpcToolBasedRawDigitPrepService
  SOURCES
    test_TpcToolBasedRawDigitPrepService.cxx
  LIBRARIES
    dunecore::ArtSupport
    lardataobj::RawData
    art::Utilities
    art::Framework_Services_Registry
    canvas::canvas
    ROOT::Hist
    cetlib::cetlib
    cetlib_except::cetlib_except
    ROOT::Core
)
