# DataPrep/Module
David Adams  
September 2023

This directory holds dataperep modules--the are entry point to dataprep processing

[DataPrepModule](DataPrepModule_module.cc) is the original module. It reads raw::RawDigit objects from the event store and writes recob::Wire objects.

[DataPrepByApaModule](DataPrepByApaModule_module.cc] is an upgrade of that module that additionally provides the option
to read the raw digits for selected APAs using a tool.
This was used for ProtoDUNE-SP and intended for it and other detectors where dataprep can be run one APA at a time
to reduce memory consumption.

