# DataPrep/Service
David Adams
September 2023

This directory contains dataprep services (art services).
Most are obsolete and were replaced by tools many years ago whe dataprep was upgraded.
The exceptions are:

ToolBasedRawDigitPrepService ([header](ToolBasedRawDigitPrepService.h), [source](ToolBasedRawDigitPrepService_service.cc))
is called by the dataprep modules (see [../Modules](../Modules)).
It provides method _prepare_ which is passed dataprep channel (_AdcChannelDataMap_) which it passes to
a sequence of tools for processing.
If the call also cotains a recob::Wire container, than that container is filled using the channel data.

TpcToolBasedRawDigitPrepService ([header](TpcToolBasedRawDigitPrepService.h), [source](TpcToolBasedRawDigitPrepService_service.cc))
is an alternative that calls a sequence of tools to process _TpcData_ instead e.g. to process an APA instead of an APA plane.

StandardAdcWireBuildingService ([header](StandardAdcWireBuildingService.h), [source](StandardAdcWireBuildingService_service.cc))
is used by the above to construct recob::Wire containers from the dataprep data. 

Here are some example configurations for these services:
<pre>
  RawDigitPrepService: {
    CallgrindToolNames: []
    DoWires: "false"
    LogLevel: 3
    ToolNames: ["digitReader", "adcSampleFiller", "adcScaleAdcToKe", "cht_vdcb2u_prp", "cht_vdcb2v_prp", "cht_vdcb2z_prp", "vdcb2_adcChannelSamRmsPlotter", "vdcb2_adcChannelSamRms30Plotter", "vdcb2_adcChannelSamRms50Plotter", "adcKeepAllSignalFinder"]
    service_provider: "ToolBasedRawDigitPrepService"
  }
  
  AdcWireBuildingService: {
    LogLevel: 1
    service_provider: "StandardAdcWireBuildingService"
  }
</pre>
Note each is referenced by the name of its base class.

