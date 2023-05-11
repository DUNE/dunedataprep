// DpWctFrameConverter.h
//
// David Adams
// April 2023
//
// Utility to convert between dataprep AdcChannelData and WCT IFrame.
//

#include "dunecore/DuneInterface/Data/AdcChannelData.h"
#include "WireCellIface/IFrame.h"

class DpWctFrameConverter {

  // Ctor from a dataprep channel map.
  DpWctFrameConverter(AdcChannelDataMap& acm);

  // Return the dataprep channel data map.
  AdcChannelDataMap& getDataMap() const { return m_acm; }

  // Return the WCT waveforms
  WireCell::IFrame::pointer getFrame(int ident =0, double dsam =0.5*WireCell::units::microsecond);

  // Set the dataprep waveforms.
  int setFrame(WireCell::IFrame::pointer pif);

private:

  AdcChannelDataMap& m_acm;

};
