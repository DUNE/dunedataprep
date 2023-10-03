# DataPrep/TpcTool
David Adams  
September 2023

This directory holds art tools that implement the TpcDataTool interface, i.e. they are used to transform TpcData objects.
The tools are listed with brief escriptions below.
For more information, follow the links to the header files.

[AdcToRoi2d](AdcToRoi2d.h) - Each ADC channel map is used to create a 2D ROI.

[Roi2dToAdc](Roi2dToAdc.h) - The signals from each 2D ROI are added to the correponding ADC channel map.

[Tpc2dDeconvolute](Tpc2dDeconvolute.h) - Use DFT to deconvolute each 2D ROI.
