# dunetpc/dune/DataPrep/Tool/CMakeLists.txt

# David Adams
# June 2017

# Add plugin for each tool.

cet_build_plugin(AdcThresholdSignalFinder dunecore::TpcDataTool LIBRARIES
                 LIBRARIES PRIVATE
                 ROOT::Core
                 canvas::canvas
                 art::Utilities
                 dunecore::ArtSupport
                 dunecore::DuneCommon_Utility)

cet_build_plugin(StandardAdcChannelStringTool   art::tool LIBRARIES
                 dunecore::ArtSupport
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcResultDumper   art::tool LIBRARIES
                dunecore::ArtSupport
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelDumper   art::tool LIBRARIES
                 dunecore::ArtSupport
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelTrimmer  art::tool LIBRARIES
                dunecore::ArtSupport
                art::Utilities canvas::canvas LIBRARIES
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelSplitter  art::tool LIBRARIES
                dunecore::ArtSupport
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelPlotter  art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                larevt::CalibrationDBI_Providers
                larcore::headers
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcPedestalFitter  art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcCodeMitigator  art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcSampleScaler   art::tool LIBRARIES
                art::Utilities canvas::canvas
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcRangeSampleScaler   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcTimingMitigator  art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcDataDumper   art::tool LIBRARIES
                dunecore::DuneCommon_Utility
                larevt::CalibrationDBI_Providers
                larcore::headers
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcTickModViewer   art::tool LIBRARIES
                dunedataprep_DataPrep_Utility
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
		ROOT::Tree
             )

cet_build_plugin(AdcDataPlotter   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcDetectorPlotter   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                dunecore::Geometry
                larevt::CalibrationDBI_Providers
                larcore::headers
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelMetric   art::tool LIBRARIES
                dunecore::DuneCommon_Utility
                dunecore::ArtSupport
                larevt::CalibrationDBI_Providers
                larcore::headers
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcEventViewer   art::tool LIBRARIES
                dunecore::DuneCommon_Utility
                dunecore::ArtSupport
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AcdDigitReader   art::tool LIBRARIES
                dunecore::DuneCommon_Utility
                lardataobj::RawData
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AcdWireReader   art::tool LIBRARIES
                dunecore::DuneCommon_Utility
                lardataobj::RecoBase
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcSampleFiller   art::tool LIBRARIES
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(SubtractBaseline   art::tool LIBRARIES
                dunecore::DuneCommon_Utility
                lardata::Utilities
                canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(UndershootCorr   art::tool LIBRARIES
                        dunepdlegacy::Services_ChannelMap_PdspChannelMapService_service
                        dunecore::DuneCommon_Utility
                        lardata::Utilities
			art::Framework_Services_Registry
                        art::Utilities canvas::canvas
                        messagefacility::MF_MessageLogger
                        ROOT::Core
             )

cet_build_plugin(ExpTailRemover   art::tool LIBRARIES
                dunecore::DuneCommon_Utility
                dunecore::ArtSupport
                dunepdlegacy::Services_ChannelMap_PdspChannelMapService_service
                ROOT::Core
                art::Utilities canvas::canvas
                messagefacility::MF_MessageLogger
                ROOT::Core
             )

cet_build_plugin(ExpTailPedRemover   art::tool LIBRARIES
                dunecore::DuneCommon_Utility
                dunecore::ArtSupport
                dunepdlegacy::Services_ChannelMap_PdspChannelMapService_service
                ROOT::Core
                art::Utilities canvas::canvas
                messagefacility::MF_MessageLogger
                ROOT::Core
             )

cet_build_plugin(VintageDeconvoluter   art::tool LIBRARIES
                dunecore::SignalShapingServiceDUNE_service
                art::Framework_Services_Registry
                art::Utilities
                canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(PddpVintageDeconvoluter   art::tool LIBRARIES
                dunecore::SignalShapingServiceDUNEDPhase_service
		lardata::Utilities
                art::Framework_Services_Registry
                art::Utilities
                canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )


cet_build_plugin(AdcUnderflowFlagger   art::tool LIBRARIES
                dunecore::SignalShapingServiceDUNEDPhase_service
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(FclStickyCodeFlagger   art::tool LIBRARIES
                dunecore::SignalShapingServiceDUNEDPhase_service
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcKeepAllSignalFinder   art::tool LIBRARIES
                dunecore::SignalShapingServiceDUNEDPhase_service
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcNoiseSignalFinder   art::tool LIBRARIES
                dunecore::SignalShapingServiceDUNEDPhase_service
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcRoiShifter   art::tool LIBRARIES
                dunecore::SignalShapingServiceDUNEDPhase_service
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(DuneAdcSignalFinder   art::tool LIBRARIES
                dunecore::SignalShapingServiceDUNEDPhase_service
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcRegularSignalFinder   art::tool LIBRARIES
                dunecore::SignalShapingServiceDUNEDPhase_service
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcRoiViewer   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
		canvas::canvas
                cetlib::cetlib 
		cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcDPhase3x1x1LocalRoiBuilder   art::tool LIBRARIES
                dunecore::DuneCommon_Utility
                lardataobj::RawData
                lardataobj::RecoBase
                lardata::Utilities
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(FembLinearCalibration   art::tool LIBRARIES
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(FloatArrayGainCalibration   art::tool LIBRARIES
                dunecore::DuneCommon_Utility
                dunecore::ArtSupport
		canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(FembMappedAdcModifier   art::tool LIBRARIES
                dunecore::ArtSupport
		canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelFFT   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcDeconvoluteFFT   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
		canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )
cet_build_plugin(Adc2dConvolute   art::tool LIBRARIES
                dunecore::ArtSupport
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelDftPlotter   art::tool LIBRARIES
                dunedataprep_DataPrep_Utility
                dunecore::DuneCommon_Utility
                dunecore::ArtSupport
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcDPhase3x1x1RoiBuilder   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                lardataobj::RawData
                lardataobj::RecoBase
                lardata::Utilities
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcMultiThreshSignalFinder   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                lardata::Utilities
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(PdspNoiseRemoval   art::tool LIBRARIES
               dunecore::ArtSupport
               larcorealg::Geometry
               larcore::headers
               lardata::Utilities
               dunecore::DuneCommon_Utility
               lardataobj::RawData
               lardataobj::RecoBase
               larevt::CalibrationDBI_Providers
               art::Utilities canvas::canvas
               cetlib::cetlib cetlib_except::cetlib_except
               dunepdlegacy::Services_ChannelMap_PdspChannelMapService_service
               ROOT::Core
               ROOT::Spectrum
             )

cet_build_plugin(RemoveBadChannels   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                larevt::CalibrationDBI_Providers
                larcore::headers
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcRoiSlicer   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(BaselineDetrend   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcRoiToTree   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
		ROOT::Core ROOT::Tree
             )

cet_build_plugin(CnrByGroup   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(CnrGroupWeighted   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcSumSignalFinder   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(IsoRoiByGroup   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(IsoRoiMatcher   art::tool LIBRARIES
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                dunedataprep_DataPrep_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
		ROOT::Tree
             )

add_subdirectory(test)
install_source()
