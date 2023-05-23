#pragma once

#ifndef DIODECLIPPER_H
#define DIODECLIPPER_H

#include <juce_core/juce_core.h>
#include "chowdsp_wdf/chowdsp_wdf.h"

using namespace chowdsp::wdft;

class DiodeClipper
{
public:
    DiodeClipper() = default;

    void prepare(double sampleRate);
    void reset();
    void setCircuitParams(float cutoff);
    void setCircuitElements(float res, float cap);
    inline float processSample(float x)
    {
        Vs.setVoltage(x);

        dp.incident(P1.reflected());
        auto y = voltage<float>(C1);
        P1.incident(dp.reflected());

        return y;
    }

private:
    ResistorT<float> R1{ 4700.0f };
    ResistiveVoltageSourceT<float> Vs;
    WDFSeriesT<float, decltype (Vs), decltype (R1)> S1{ Vs, R1 };

    CapacitorT<float> C1{ 47.0e-9f };
    WDFParallelT<float, decltype (S1), decltype (C1)> P1{ S1, C1 };

    // GZ34 diode pair
    DiodePairT<float, decltype (P1)> dp{ P1, 2.52e-9f };
};

#endif //DIODECLIPPER_H