// DpWctFrameConverter.cxx

#include "dunedataprep/DataPrep/Utility/DpWctFrameConverter.h"
#include "WireCellAux/SimpleTrace.h"
#include "WireCellAux/SimpleFrame.h"
#include <limits>

using WireCell::ITrace;
using WireCell::IFrame;
using WireCell::Aux::SimpleTrace;
using WireCell::Aux::SimpleFrame;

//**********************************************************************

DpWctFrameConverter::DpWctFrameConverter(AdcChannelDataMap& acm)
: m_acm(acm) { }

//**********************************************************************

IFrame::pointer DpWctFrameConverter::getFrame(int ident, double dsam) {
  const double tremfac = 1.e-9;    // Assume trem is in ns
  double t0 = 0.0;
  if ( m_acm.size() ) {
    t0 = std::numeric_limits<double>::max();
    for ( auto iacd : m_acm ) {
      const AdcChannelData& acd = iacd.second;
      double t0ch = double(acd.time()) + tremfac*double(acd.timerem());
      if ( t0ch < t0 ) t0 = t0ch;
    }
  }
  ITrace::vector traces(m_acm.size());
  unsigned int itra = 0; 
  for ( auto iacd : m_acm ) {
    int icha = iacd.first;
    const AdcChannelData& acd = iacd.second;
    double t0ch = double(acd.time()) + tremfac*double(acd.timerem());
    double dtick = (t0ch - t0)/dsam;
    int tbin = int(dtick + 0.5);
    assert( icha = acd.channel() );
    const AdcSignalVector& dpsams = acd.samples;
    SimpleTrace* ptra = new SimpleTrace(icha, tbin, dpsams.size());
    ITrace::ChargeSequence& wcsams = ptra->charge();
    wcsams.insert(wcsams.begin(), dpsams.begin(), dpsams.end());
    traces[itra++].reset(ptra);
  }
  return IFrame::pointer(new SimpleFrame(ident, t0, traces, dsam));
}

//**********************************************************************

