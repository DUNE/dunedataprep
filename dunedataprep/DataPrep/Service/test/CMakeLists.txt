#dunetpc/dune/DataPrep/Service/test/CMakeLists.txt

# David Adams
# May 2016

# Build test for each service.

include(CetTest)

cet_enable_asserts()

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
