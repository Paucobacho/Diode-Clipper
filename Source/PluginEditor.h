/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DiodeClipperAudioProcessorEditor  : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    DiodeClipperAudioProcessorEditor (DiodeClipperAudioProcessor&);
    ~DiodeClipperAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:
    juce::Slider inGainSlider;
    juce::Label inGainLabel;
    juce::Slider cutoffSlider;
    juce::Label cutoffLabel;
    juce::Slider oscillatorSlider;
    juce::Label oscillatorLabel;
    juce::Slider levelSlider;
    juce::Label levelLabel;
    juce::Slider dryWetSlider;
    juce::Label dryWetLabel;
    juce::Slider amountSlider;
    juce::Label amountLabel;

    juce::TextButton oscillatorButton{ "oscillator" };
    float oscillatorSwitch = false;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DiodeClipperAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiodeClipperAudioProcessorEditor)
};
