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

StandardAdcWireBuildingService ([header](StandardAdcWireBuildingService.h), [source](StandardAdcWireBuildingService_service.cc))
is used for that last step.

