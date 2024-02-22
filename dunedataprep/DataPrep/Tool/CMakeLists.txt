# dunetpc/dune/DataPrep/Tool/CMakeLists.txt

# David Adams
# June 2017

# Add plugin for each tool.

cet_build_plugin(AdcThresholdSignalFinder dunecore::TpcDataTool
                 LIBRARIES PRIVATE
                 ROOT::Core
                 canvas::canvas
                 art::Utilities
                 dunecore::ArtSupport
                 dunecore::DuneCommon_Utility)

cet_build_plugin(StandardAdcChannelStringTool   art::tool
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcResultDumper   art::tool
                dunecore::ArtSupport
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelDumper   art::tool
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelTrimmer  art::tool
                dunecore::ArtSupport
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelSplitter  art::tool
                dunecore::ArtSupport
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelPlotter  art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcPedestalFitter  art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcCodeMitigator  art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcSampleScaler   art::tool
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcRangeSampleScaler   art::tool
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcTimingMitigator  art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcDataDumper   art::tool
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcTickModViewer   art::tool
                dunedataprep_DataPrep_Utility
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
		ROOT::Tree
             )

cet_build_plugin(AdcDataPlotter   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcDetectorPlotter   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                dunecore::Geometry
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelMetric   art::tool
                dunecore::DuneCommon_Utility
                dunecore::ArtSupport
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcEventViewer   art::tool
                dunecore::DuneCommon_Utility
                dunecore::ArtSupport
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AcdDigitReader   art::tool
                dunecore::DuneCommon_Utility
                lardataobj_RawData
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AcdWireReader   art::tool
                dunecore::DuneCommon_Utility
                lardataobj_RecoBase
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcSampleFiller   art::tool
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(SubtractBaseline   art::tool
                canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(UndershootCorr   art::tool
                        dunepdlegacy_Services_ChannelMap_PdspChannelMapService_service
			art::Framework_Services_Registry
                        art::Utilities canvas::canvas
                        messagefacility::MF_MessageLogger
                        ROOT::Core
             )

cet_build_plugin(ExpTailRemover   art::tool
                dunecore::DuneCommon_Utility
                dunecore::ArtSupport
                dunepdlegacy_Services_ChannelMap_PdspChannelMapService_service
                ROOT::Core
                art::Utilities canvas
                messagefacility::MF_MessageLogger
                ROOT::Core
             )

cet_build_plugin(ExpTailPedRemover   art::tool
                dunecore::DuneCommon_Utility
                dunecore::ArtSupport
                dunepdlegacy_Services_ChannelMap_PdspChannelMapService_service
                ROOT::Core
                art::Utilities canvas
                messagefacility::MF_MessageLogger
                ROOT::Core
             )

cet_build_plugin(VintageDeconvoluter   art::tool
                dunecore::SignalShapingServiceDUNE_service
                art::Framework_Services_Registry
                art::Utilities
                canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(PddpVintageDeconvoluter   art::tool
                dunecore::SignalShapingServiceDUNEDPhase_service
		lardata_Utilities
                art::Framework_Services_Registry
                art::Utilities
                canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )


cet_build_plugin(AdcUnderflowFlagger   art::tool
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(FclStickyCodeFlagger   art::tool
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcKeepAllSignalFinder   art::tool
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcNoiseSignalFinder   art::tool
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcRoiShifter   art::tool
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(DuneAdcSignalFinder   art::tool
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcRegularSignalFinder   art::tool
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcRoiViewer   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
		canvas::canvas
                cetlib::cetlib 
		cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcDPhase3x1x1LocalRoiBuilder   art::tool
                dunecore::DuneCommon_Utility
                lardataobj_RawData
                lardataobj_RecoBase
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(FembLinearCalibration   art::tool
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(FloatArrayGainCalibration   art::tool
                dunecore::DuneCommon_Utility
                dunecore::ArtSupport
		canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(FembMappedAdcModifier   art::tool
                dunecore::ArtSupport
		canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelFFT   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcDeconvoluteFFT   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
		canvas::canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )
cet_build_plugin(Adc2dConvolute   art::tool
                dunecore::ArtSupport
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcChannelDftPlotter   art::tool
                dunedataprep_DataPrep_Utility
                dunecore::DuneCommon_Utility
                dunecore::ArtSupport
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcDPhase3x1x1RoiBuilder   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                lardataobj_RawData
                lardataobj_RecoBase
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcMultiThreshSignalFinder   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(PdspNoiseRemoval   art::tool
               dunecore::ArtSupport
               larcorealg_Geometry
               dunecore::DuneCommon_Utility
               lardataobj_RawData
               lardataobj_RecoBase
               art::Utilities canvas
               cetlib::cetlib cetlib_except::cetlib_except
               dunepdlegacy_Services_ChannelMap_PdspChannelMapService_service
               ROOT::Core
               ROOT::Spectrum
             )

cet_build_plugin(RemoveBadChannels   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcRoiSlicer   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(BaselineDetrend   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcRoiToTree   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
		ROOT::Core ROOT::Tree
             )

cet_build_plugin(CnrByGroup   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(CnrGroupWeighted   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(AdcSumSignalFinder   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(IsoRoiByGroup   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
             )

cet_build_plugin(IsoRoiMatcher   art::tool
                dunecore::ArtSupport
                dunecore::DuneCommon_Utility
                dunedataprep_DataPrep_Utility
                cetlib::cetlib cetlib_except::cetlib_except
                ROOT::Core
		ROOT::Tree
             )

add_subdirectory(test)
install_source()
