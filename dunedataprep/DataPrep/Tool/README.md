# DataPrep/Tool

This page describes the dataprep tools which ar restricted to the AdcChannelData part of the dataprep interface.
For tools that go beyond that part, see [DataPrep/TpcTool](../TpcTool).
That part of the interace has two type signatures: one that takes a single channel and one that takes a map of channels
(typically a wire plane or CRP).
Implentaations typically provide one of these and where the latter is not provided, the default is simply to call the former for all channels.
For each of these there are separate view and update methods with the former not modifying the passed data.
The default implementation for update simply passes the object to view.
In typical dataprep processing all calls are made through the channel-map update interface.

Each of the descriptions below includes a link to the tool header where more a detailed (and perhaps more up to date)
description may be found.

## Reconstruction Tools

[AdcDigitReader](AdcDigitReader.h) populates the raw ADC waveform and pedestal for each channel using the associated raw::RawDigit.
This is typically the first tool to be run in a sequence embeddded in a larsoft event loop.

[AdcWireReader](AdcWireeReader.h) populates the prepared ADC waveform for each channel from the associated recob::Wire object.
This would be used when another actor (Monte Carlo, another reco framewor or an earlier dataprep job) has written TPC data in the format.

## Simulation Tools

[Adc2dConvolute](Adc2dConvolute) convolutes the prepared waveforms with a 2D (channel-wire) kernel provided as part of the tool configuration.

## More to come...
