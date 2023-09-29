# DataPrep/Module
David Adams  
September 2023

This directory holds the dataprep modules--they are the art entry point to dataprep processing.
These are intended to provide the first step in the art processing chain, reading in raw data and writing out the ROIs (regions of interest)
used in downstream processing.
The input is a container of raw::RawDigit objects either read from the event data store or fetched with a tool.
Output is a container of recob::Wire objects writen to the event store.
There are options to also read and write other data types.

[DataPrepModule](DataPrepModule_module.cc) is the original module. It reads digits from the event store.

[DataPrepByApaModule](DataPrepByApaModule_module.cc) is an upgrade of that module that additionally provides the option
to read the raw digits for selected APAs using a tool.
This was used for ProtoDUNE-SP and intended for it and other detectors where dataprep can be run one APA at a time
to reduce memory consumption.

Here is an example fcl configuration of the second tool:
<pre>
  producers: {
    caldata: {
      ApaChannelCounts: [2560]
      BeamEventLabel: ""
      ChannelGroups: ["all"]
      DecoderTool: "vdtool"
      DeltaTickCount: 0.005
      DigitLabel: "tpcrawdecoder:daq"
      KeepChannels: []
      LogLevel: 3
      OnlineChannelMapTool: "onlineChannelMapVdcb"
      OutputDigitName: ""
      OutputTimeStampName: ""
      OutputWireName: ""
      SkipChannels: []
      SkipEmptyChannels: "true"
      module_type: "DataModule"
    }
    ...
  }
</pre>
