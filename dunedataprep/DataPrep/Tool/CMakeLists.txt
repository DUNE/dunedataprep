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
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcResultDumper   art::tool
                dunecore_ArtSupport
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcChannelDumper   art::tool
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcChannelTrimmer  art::tool
                dunecore_ArtSupport
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcChannelSplitter  art::tool
                dunecore_ArtSupport
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcChannelPlotter  art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
		ART_FRAMEWORK_SERVICES_REGISTRY
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcPedestalFitter  art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcCodeMitigator  art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcSampleScaler   art::tool
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcRangeSampleScaler   art::tool
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcTimingMitigator  art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcDataDumper   art::tool
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcTickModViewer   art::tool
                dunedataprep_DataPrep_Utility
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcDataPlotter   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
		ART_FRAMEWORK_SERVICES_REGISTRY
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcDetectorPlotter   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                dunecore_Geometry
		ART_FRAMEWORK_SERVICES_REGISTRY
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcChannelMetric   art::tool
                dunecore_DuneCommon_Utility
                dunecore_ArtSupport
		ART_FRAMEWORK_SERVICES_REGISTRY
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcEventViewer   art::tool
                dunecore_DuneCommon_Utility
                dunecore_ArtSupport
		ART_FRAMEWORK_SERVICES_REGISTRY
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AcdDigitReader   art::tool
                dunecore_DuneCommon_Utility
                lardataobj_RawData
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AcdWireReader   art::tool
                dunecore_DuneCommon_Utility
                lardataobj_RecoBase
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcSampleFiller   art::tool
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(SubtractBaseline   art::tool
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(UndershootCorr   art::tool
                        dunepdlegacy_Services_ChannelMap_PdspChannelMapService_service
                        ART_FRAMEWORK_CORE
                        ART_FRAMEWORK_PRINCIPAL
                        ART_FRAMEWORK_SERVICES_REGISTRY
                        ART_ROOT_IO_TFILE_SUPPORT
                        ROOT::Core
                        ART_ROOT_IO_TFILESERVICE_SERVICE
                        art::Utilities canvas
                        messagefacility::MF_MessageLogger
                        ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(ExpTailRemover   art::tool
                dunecore_DuneCommon_Utility
                dunecore_ArtSupport
                dunepdlegacy_Services_ChannelMap_PdspChannelMapService_service
                ART_FRAMEWORK_CORE
                ART_FRAMEWORK_PRINCIPAL
                ART_FRAMEWORK_SERVICES_REGISTRY
                ART_ROOT_IO_TFILE_SUPPORT
                ROOT::Core
                ART_ROOT_IO_TFILESERVICE_SERVICE
                art::Utilities canvas
                messagefacility::MF_MessageLogger
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(ExpTailPedRemover   art::tool
                dunecore_DuneCommon_Utility
                dunecore_ArtSupport
                dunepdlegacy_Services_ChannelMap_PdspChannelMapService_service
                ART_FRAMEWORK_CORE
                ART_FRAMEWORK_PRINCIPAL
                ART_FRAMEWORK_SERVICES_REGISTRY
                ART_ROOT_IO_TFILE_SUPPORT
                ROOT::Core
                ART_ROOT_IO_TFILESERVICE_SERVICE
                art::Utilities canvas
                messagefacility::MF_MessageLogger
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(VintageDeconvoluter   art::tool
                dunecore::SignalShapingServiceDUNE_service
                art::Framework_Services_Registry
                art::Utilities
                canvas::canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(PddpVintageDeconvoluter   art::tool
                dunecore::SignalShapingServiceDUNEDPhase_service
		lardata_Utilities
                art::Framework_Services_Registry
                art::Utilities
                canvas::canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )


cet_build_plugin(AdcUnderflowFlagger   art::tool
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(FclStickyCodeFlagger   art::tool
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcKeepAllSignalFinder   art::tool
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcNoiseSignalFinder   art::tool
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcRoiShifter   art::tool
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(DuneAdcSignalFinder   art::tool
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcRegularSignalFinder   art::tool
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcRoiViewer   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
		canvas::canvas
                cetlib::cetlib 
		cetlib_except::cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcDPhase3x1x1LocalRoiBuilder   art::tool
                dunecore_DuneCommon_Utility
                lardataobj_RawData
                lardataobj_RecoBase
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(FembLinearCalibration   art::tool
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(FloatArrayGainCalibration   art::tool
                dunecore_DuneCommon_Utility
                dunecore_ArtSupport
		canvas::canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(FembMappedAdcModifier   art::tool
                dunecore_ArtSupport
		canvas::canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcChannelFFT   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcDeconvoluteFFT   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
		canvas::canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )
cet_build_plugin(Adc2dConvolute   art::tool
                dunecore_ArtSupport
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcChannelDftPlotter   art::tool
                dunedataprep_DataPrep_Utility
                dunecore_DuneCommon_Utility
                dunecore_ArtSupport
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcDPhase3x1x1RoiBuilder   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                lardataobj_RawData
                lardataobj_RecoBase
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcMultiThreshSignalFinder   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(PdspNoiseRemoval   art::tool
               dunecore_ArtSupport
               larcorealg_Geometry
               dunecore_DuneCommon_Utility
               lardataobj_RawData
               lardataobj_RecoBase
               ART_FRAMEWORK_SERVICES_REGISTRY
               art::Utilities canvas
               cetlib::cetlib cetlib_except
               dunepdlegacy_Services_ChannelMap_PdspChannelMapService_service
               ROOT_BASIC_LIB_LIST
               ROOT_SPECTRUM
             )

cet_build_plugin(RemoveBadChannels   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
		ART_FRAMEWORK_SERVICES_REGISTRY
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcRoiSlicer   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                art::Utilities canvas
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(BaselineDetrend   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(AdcRoiToTree   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(CnrByGroup   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(CnrGroupWeighted   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

cet_build_plugin(IsoRoiByGroup   art::tool
                dunecore_ArtSupport
                dunecore_DuneCommon_Utility
                cetlib::cetlib cetlib_except
                ROOT_BASIC_LIB_LIST
             )

add_subdirectory(test)
install_source()
