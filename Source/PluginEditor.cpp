/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DiodeClipperAudioProcessorEditor::DiodeClipperAudioProcessorEditor (DiodeClipperAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(inGainSlider);
    inGainSlider.setRange(0, 50.0f);
    inGainSlider.setTextValueSuffix(" dB");
    inGainSlider.addListener(this);
    //inGainSlider.setValue(500.0); 
    
    addAndMakeVisible(inGainLabel);
    inGainLabel.setText("drive", juce::dontSendNotification);
    inGainLabel.attachToComponent(&inGainSlider, true); 

    addAndMakeVisible(cutoffSlider);
    cutoffSlider.setRange(0, 20000.0f);
    cutoffSlider.setTextValueSuffix(" Hz");
    cutoffSlider.addListener(this);
    //inGainSlider.setValue(500.0); 

    addAndMakeVisible(cutoffLabel);
    cutoffLabel.setText("cutoff", juce::dontSendNotification);
    cutoffLabel.attachToComponent(&cutoffSlider, true);

    addAndMakeVisible(oscillatorSlider);
    oscillatorSlider.setRange(0, 5000.0);
    oscillatorSlider.setTextValueSuffix(" Hz");
    oscillatorSlider.addListener(this);
    oscillatorSlider.setValue(1.0);

    addAndMakeVisible(oscillatorLabel);
    oscillatorLabel.setText("cutoff osc", juce::dontSendNotification);
    oscillatorLabel.attachToComponent(&oscillatorSlider, true);

    addAndMakeVisible(levelSlider);
    levelSlider.setRange(0, 10.0f);
    levelSlider.setTextValueSuffix(" dB");
    levelSlider.addListener(this);
    //inGainSlider.setValue(500.0); 

    addAndMakeVisible(levelLabel);
    levelLabel.setText("level", juce::dontSendNotification);
    levelLabel.attachToComponent(&levelSlider, true);

    addAndMakeVisible(dryWetSlider);
    dryWetSlider.setRange(0, 1.0);
    //levelSlider.setTextValueSuffix(" dB");
    dryWetSlider.addListener(this);
    dryWetSlider.setValue(1.0);

    addAndMakeVisible(dryWetLabel);
    dryWetLabel.setText("dry/wet", juce::dontSendNotification);
    dryWetLabel.attachToComponent(&dryWetSlider, true);

    

    setSize (400, 200);
}

DiodeClipperAudioProcessorEditor::~DiodeClipperAudioProcessorEditor()
{
}

//==============================================================================
void DiodeClipperAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void DiodeClipperAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto sliderLeft = 60;
    inGainSlider.setBounds(sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
    cutoffSlider.setBounds(sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
    oscillatorSlider.setBounds(sliderLeft, 80, getWidth() - sliderLeft - 10, 20);
    levelSlider.setBounds(sliderLeft, 110, getWidth() - sliderLeft - 10, 20);
    dryWetSlider.setBounds(sliderLeft, 140, getWidth() - sliderLeft - 10, 20);
    //durationSlider.setBounds(sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
}

void DiodeClipperAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &inGainSlider)
    {
        audioProcessor.drive = inGainSlider.getValue();
    }
    if (slider == &cutoffSlider)
    {
        audioProcessor.cutoff= cutoffSlider.getValue();
    }
    if (slider == &oscillatorSlider)
    {
        float val = oscillatorSlider.getValue();
        audioProcessor.LCOFreq= val;
        if (val == 0.0)
        {
            audioProcessor.LCOSwitch = false;
        }
        else {
            audioProcessor.LCOSwitch = true;
        }  
    }
    if (slider == &levelSlider)
    {
        audioProcessor.level= levelSlider.getValue();
    }
    if (slider == &dryWetSlider)
    {
        audioProcessor.dryWet = dryWetSlider.getValue();
    }
}
