#include "diodeClipper.h"

void DiodeClipper::prepare(double sampleRate)
{
	C1.prepare((float)sampleRate);
}

void DiodeClipper::reset()
{
	C1.reset();
}

void DiodeClipper::setCircuitParams(float cutoff)
{
	constexpr auto Cap = 47.0e-9f;
	const auto Res = 1.0f / (juce::MathConstants<float>::twoPi * cutoff * Cap);

	C1.setCapacitanceValue(Cap);
	R1.setResistanceValue(Res);
}

void DiodeClipper::setCircuitElements(float res, float cap)
{
	C1.setCapacitanceValue(cap);
	R1.setResistanceValue(res);
}