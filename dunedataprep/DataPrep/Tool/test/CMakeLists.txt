# dunetpc/dune/DataPrep/Tool/test/CMakeLists.txt

# David Adams
# June 2017

# Build test for each service.

include(CetTest)

cet_test(test_StandardAdcChannelStringTool
  SOURCE
    test_StandardAdcChannelStringTool.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcResultDumper
  SOURCE
    test_AdcResultDumper.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcChannelDumper
  SOURCE
    test_AdcChannelDumper.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcChannelPlotter
  SOURCE
    test_AdcChannelPlotter.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcTickModViewer
  SOURCE
    test_AdcTickModViewer.cxx
  LIBRARIES
    dunedataprep_DataPrep_Utility
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcChannelTrimmer
  SOURCE
     test_AdcChannelTrimmer.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcChannelSplitter
  SOURCE
    test_AdcChannelSplitter.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcPedestalFitter
  SOURCE
    test_AdcPedestalFitter.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcCodeMitigator
  SOURCE
    test_AdcCodeMitigator.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_ExpTailRemover
  SOURCE
    test_ExpTailRemover.cxx
  LIBRARIES
    dunecore::ArtSupport
    dunecore::DuneCommon_Utility
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_ExpTailPedRemover
  SOURCE
    test_ExpTailPedRemover.cxx
  LIBRARIES
    dunecore::ArtSupport
    dunecore::DuneCommon_Utility
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_VintageDeconvoluter
  SOURCE
    test_VintageDeconvoluter.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcSampleScaler
  SOURCE
    test_AdcSampleScaler.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcRangeSampleScaler
  SOURCE
    test_AdcRangeSampleScaler.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcDataDumper
  SOURCE
    test_AdcDataDumper.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcEventViewer
  SOURCE
test_AdcEventViewer.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
    ROOT::MathCore
)

cet_test(test_AdcDataPlotter
  SOURCE
    test_AdcDataPlotter.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
    ROOT::MathCore
)

cet_test(test_AdcDetectorPlotter
  SOURCE
    test_AdcDetectorPlotter.cxx
  LIBRARIES
    art::Framework_Services_Registry
    dunecore::ArtSupport
    dunecore::Geometry
    larcorealg::Geometry
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core

)

cet_test(test_AdcChannelMetric
  SOURCE
    test_AdcChannelMetric.cxx
  LIBRARIES
    dunecore::ArtSupport
    dunecore::Geometry
    larcorealg::Geometry
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AcdDigitReader
  SOURCE
    test_AcdDigitReader.cxx
  LIBRARIES
    lardataobj::RawData
    dunecore::ArtSupport
    lardataobj::RawData
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcSampleFiller
  SOURCE
    test_AdcSampleFiller.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_FclStickyCodeFlagger
  SOURCE
    test_FclStickyCodeFlagger.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcKeepAllSignalFinder
  SOURCE
    test_AdcKeepAllSignalFinder.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcThresholdSignalFinder
  SOURCE
    test_AdcThresholdSignalFinder.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcNoiseSignalFinder
  SOURCE
    test_AdcNoiseSignalFinder.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcRoiShifter
  SOURCE
    test_AdcRoiShifter.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcRegularSignalFinder
  SOURCE
    test_AdcRegularSignalFinder.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_DuneAdcSignalFinder
  SOURCE
    test_DuneAdcSignalFinder.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AcdWireReader
  SOURCE
    test_AcdWireReader.cxx
  LIBRARIES
    art::Framework_Services_Registry
    lardataobj::RawData
    lardata::Utilities
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcRoiViewer
  SOURCE
    test_AdcRoiViewer.cxx
  LIBRARIES
    lardataobj::RawData
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    ROOT::Core
    ROOT::MathCore
    SQLite::SQLite3
    Boost::filesystem
)

cet_test(test_FembLinearCalibration
  SOURCE
    test_FembLinearCalibration.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_FloatArrayGainCalibration
  SOURCE
    test_FloatArrayGainCalibration.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcChannelFFT
  SOURCE
    test_AdcChannelFFT.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_Adc2dConvolute
  SOURCE
    test_Adc2dConvolute.cxx
  LIBRARIES
    dunecore::ArtSupport
    dunecore::DuneCommon_Utility
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcDeconvoluteFFT
  SOURCE
    test_AdcDeconvoluteFFT.cxx
  LIBRARIES
    dunecore::ArtSupport
    dunecore::DuneCommon_Utility
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    ROOT::Core
    cetlib::cetlib
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
)

cet_test(test_AdcChannelDftPlotter
  SOURCE
    test_AdcChannelDftPlotter.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_FembMappedAdcModifier
  SOURCE
    test_FembMappedAdcModifier.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcRoiSlicer
  SOURCE
    test_AdcRoiSlicer.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_AdcRoiToTree
  SOURCE
    test_AdcRoiToTree.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib cetlib_except::cetlib_except
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
)

cet_test(test_CnrByGroup
  SOURCE
    test_CnrByGroup.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
    ROOT::MathCore
)

cet_test(test_CnrGroupWeighted
  SOURCE
    test_CnrGroupWeighted.cxx
  LIBRARIES
    dunecore::ArtSupport
    art::Utilities
    canvas::canvas
    fhiclcpp::fhiclcpp
    cetlib::cetlib
    cetlib_except::cetlib_except
    SQLite::SQLite3
    Boost::filesystem
    ROOT::Core
    ROOT::MathCore
)

cet_enable_asserts()
