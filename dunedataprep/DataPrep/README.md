# DataPrep
David Adams  
Updated: September 2023

DUNE dataprep is a collection of utilities, tools, services and modules that aid in the reconstruction of DUNE TPC data.
All but the utilities follow the art conventions and are fcl configured at run time and are dynamically loaded.
Most of the useful code is in the tools because, unlike services and modules, tools are easily used outside the art
event loop, for example in Root and python scripts or a their command lines.
Most tools implement the interface [TpcDataTool](https://github.com/DUNE/dunecore/blob/develop/dunecore/DuneInterface/Tool/TpcDataTool.h)
and most often only the [AdcChannelTool](https://github.com/DUNE/dunecore/blob/develop/dunecore/DuneInterface/Tool/AdcChannelTool.h)
part of that interface.

The heart of low-level dataprep processing is the
[AdcChannelData](https://github.com/DUNE/dunecore/blob/develop/dunecore/DuneInterface/Data/AdcChannelData.h)
data class whichh holds the raw and *prepared* data, i.e. the waveforms, for a single readout channel.
The higher-level [TpcData](https://github.com/DUNE/dunecore/blob/develop/dunecore/DuneInterface/Data/TpcData.h)
holds channel-indexed maps of these channel data objects each typically describing a wire plane.
It also hold a collection of 2D (channel-tick) ROI (region of interest) objects.
The TpcDataTool interface receives a TpcData object and the implementing class may modify the data, typically updating the prepared waveform,
and/or use that data to fill histograms or create displays.

Typical dataprep processing, creates a TpcData object to describe a plane, APA (or CRP) and then runs a series of dataprep tools on that object.
Thus it is easy at run time to change that sequence, e.g. replace one cleaning tool with another or add an event display at any point in the processing.
The AdcChannelData class provides a pointer to raw::RawDigit and recob::Wire to make it easy to incorporate such a sequence in a
traditional larsoft processing chain.

Most of the data prep tool classes are contained in this package.
Those implementing only the AdcChannelTool interface are contained in and described in [DataPrep/Tool](Tool)
while those that implement other parts of the interface are in [DataPrep/TpcTool](TpcTool).
Modules that make it possible to incorporate a dataprep sequence in the larsoft event processing sequence
are in [DataPrep/Module](Module).
Services are in [DataPrep/Service](Service) but most of these are obsolete and have been replaced by tools.
Supporting utility classes, i.e. ordinary classes without fcl configuration or dynamic loading, are in [DataPrep/Utilities](Utilities).
