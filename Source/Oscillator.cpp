#include "Oscillator.h"

void Oscillator::prepare(double sampleRate)
{
	C1.prepare((float)sampleRate);
	I1.prepare((float)sampleRate);
}

void Oscillator::reset()
{
	C1.reset();
	I1.reset();
}

void Oscillator::setCircuitParams(float freq, bool switchClosed)
{
	const auto cap = 1.0e-6f;
	const auto ind = 1.0f / (std::pow(juce::MathConstants<float>::twoPi * freq, 2.0f) * cap);

	C1.setCapacitanceValue(cap);
	I1.setInductanceValue(ind);
	Sw1.setClosed(switchClosed);
}