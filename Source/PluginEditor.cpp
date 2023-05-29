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
    inGainSlider.setRange(0, 48);
    inGainSlider.setTextValueSuffix(" dB");
    inGainSlider.addListener(this);
    inGainSlider.setValue(audioProcessor.drive); 
    
    addAndMakeVisible(inGainLabel);
    inGainLabel.setText("drive", juce::dontSendNotification);
    inGainLabel.attachToComponent(&inGainSlider, true); 
    
    addAndMakeVisible(cutoffSlider);
    cutoffSlider.setRange(20.0, 20000.0f);
    cutoffSlider.setTextValueSuffix(" Hz");
    cutoffSlider.addListener(this);
    cutoffSlider.setSkewFactorFromMidPoint(500);
    cutoffSlider.setValue(audioProcessor.cutoff); 

    addAndMakeVisible(cutoffLabel);
    cutoffLabel.setText("cutoff", juce::dontSendNotification);
    cutoffLabel.attachToComponent(&cutoffSlider, true);

    addAndMakeVisible(oscillatorSlider);
    oscillatorSlider.setRange(0, 15.0);
    oscillatorSlider.setTextValueSuffix(" Hz");
    //oscillatorSlider.setSkewFactorFromMidPoint(500);
    oscillatorSlider.addListener(this);
    oscillatorSlider.setValue(audioProcessor.LCOFreq);

    addAndMakeVisible(oscillatorLabel);
    oscillatorLabel.setText("rate", juce::dontSendNotification);
    oscillatorLabel.attachToComponent(&oscillatorSlider, true);

    addAndMakeVisible(levelSlider);
    levelSlider.setRange(-100, 12.0f);
    levelSlider.setTextValueSuffix(" dB");
    levelSlider.addListener(this);
    levelSlider.setValue(0.0f); 

    addAndMakeVisible(levelLabel);
    levelLabel.setText("level", juce::dontSendNotification);
    levelLabel.attachToComponent(&levelSlider, true);

    addAndMakeVisible(amountSlider);
    amountSlider.setRange(0.0, 500.0);
    amountSlider.addListener(this);
    amountSlider.setValue(0.0);

    addAndMakeVisible(amountLabel);
    amountLabel.setText("amount", juce::dontSendNotification);
    amountLabel.attachToComponent(&amountSlider, true);
    

    setSize (400, 300);
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
    amountSlider.setBounds(sliderLeft, 110, getWidth() - sliderLeft - 10, 20);
    levelSlider.setBounds(sliderLeft, 170, getWidth() - sliderLeft - 10, 20);
 

    //durationSlider.setBounds(sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
}

void DiodeClipperAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &inGainSlider)
    {
        audioProcessor.drive = pow(10, inGainSlider.getValue() / 20);
    }
    if (slider == &cutoffSlider)
    {
        audioProcessor.cutoff= cutoffSlider.getValue();
    }
    if (slider == &oscillatorSlider)
    {
        float val = oscillatorSlider.getValue();
        audioProcessor.LCOFreq= val;
    }
    if (slider == &levelSlider)
    {
        audioProcessor.level = pow(10, levelSlider.getValue() / 20);
    }
    if (slider == &amountSlider)
    {
        audioProcessor.amount = amountSlider.getValue();
    }
}
