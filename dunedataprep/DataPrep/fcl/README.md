## dunedataprep/dunedataprep/DataPrep/fcl

Fcl configuration files for dataprep. These are not top-level config

* [dataprep_dune.fcl](dataprep_dune.fcl) - Generic prolog including dataprep module configs.
* [dataprep_tools.fcl](dataprep_tools.fcl) - Generic tool configs.
* [hdcb_dataprep_tools.fcl](hdcb_dataprep_tools.fcl) - Tool configs for HD CB data.
* [iceberg_dataprep_sequences.fcl](iceberg_dataprep_sequences.fcl) - Iceberg sequences
* [iceberg_dataprep_services.fcl](iceberg_dataprep_services.fcl) - Iceberg sequences
* [iceberg_dataprep_tools.fcl](iceberg_dataprep_tools.fcl) - Iceberg tool configs.
* [PdspChannelMapService.fcl](PdspChannelMapService.fcl) - Temporary channel map prolog for PDSP channel map (obsolete?).
* [pdsp_dataprep_sequences.fcl](pdsp_dataprep_sequences.fcl) - Dataprep sequences for PDSP.
* [pdsp_decoder.fcl](pdsp_decoder.fcl) - Copy of PDSP decoder config moved out of prolog (obsolete?).
* [protodune_dataprep_services.fcl](protodune_dataprep_services.fcl) - Prolog definitions of PDSP sequences (obsolete?).
* [protodune_dataprep_tools.fcl](protodune_dataprep_tools.fcl) - Tool configs for PDSP.
* [test_dataprep.fcl](test_dataprep.fcl) - Tools for use in unit testing.
* [vdcb1_tools.fcl](vdcb1_tools.fcl) - Tool configs for VD CB CRP1.
* [vdcb2_tools.fcl](vdcb2_tools.fcl) - Tool configs for VD CB CRP2+ (CRP2, CRP3, ...).
* [vdcb_dataprep_sequences.fcl](vdcb_dataprep_sequences.fcl) - Dataprep sequences for VD CB.
* [vdcb_tools.fcl](vdcb_tools.fcl) - Obsolete. used to hold VD CB tool configs.

### Terminology

* CB - CERN cold box data taken in 2021-2022.
* config - Fcl configuration.
* HD - horizontal drift TPT with APA readout.
* Iceberg - Prototype detector at FNAL.
* PDSP - Run 1 large ProtoDUNE HD at CERN. 
* prolog - Special fcl block that must precede all others (use is discouraged here).
* sequence - List of tools executed in dataprep (grep for ToolNames).
* tool - Art tool classe or config. Most dataprep configuration is named tools.
* VD - verical drift
