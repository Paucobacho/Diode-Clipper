#pragma once

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "chowdsp_wdf/chowdsp_wdf.h"
#include <juce_core/juce_core.h>

using namespace chowdsp::wdft;

class Oscillator
{
public:
    Oscillator() = default;

    void prepare(double sampleRate);
    void reset();
    void setCircuitParams(float freq, bool switchClosed);
    inline float processSample(float x)
    {
        Vs.setVoltage(x);

        Sw1.incident(S1.reflected());
        S1.incident(Sw1.reflected());

        return voltage<float>(C1);
    }


private:
    CapacitorT<float> C1{ 1.0e-3f };
    InductorT<float> I1{ 1.0e3f };
    WDFSeriesT<float, decltype (I1), decltype (C1)> S2{ I1, C1 };

    ResistiveVoltageSourceT<float> Vs;
    WDFSeriesT<float, decltype (Vs), decltype (S2)> S1{ Vs, S2 };

    SwitchT<float, decltype (S1)> Sw1{ S1 };
};

#endif