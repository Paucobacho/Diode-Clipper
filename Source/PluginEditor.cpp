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
    addAndMakeVisible(pluginTitle);
    pluginTitle.setText("DIODE CLIPPER", juce::dontSendNotification);
    pluginTitle.setFont(juce::Font(30.0f, juce::Font::bold));
    pluginTitle.setColour(juce::Label::textColourId, juce::Colours::lightgreen);

    inGainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    inGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 50);
    inGainSlider.setNumDecimalPlacesToDisplay(2);
    inGainSlider.setRange(0, 60);
    inGainSlider.setTextValueSuffix(" dB");
    inGainSlider.addListener(this);
    inGainSlider.setValue(audioProcessor.drive); 
    addAndMakeVisible(inGainSlider);
    
    addAndMakeVisible(inGainLabel);
    inGainLabel.setText("drive", juce::dontSendNotification);
    //inGainLabel.attachToComponent(&inGainSlider, false); 
    
    cutoffSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutoffSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 50);
    cutoffSlider.setNumDecimalPlacesToDisplay(2);
    cutoffSlider.setRange(20.0, 20000.0f);
    cutoffSlider.setTextValueSuffix(" Hz");
    cutoffSlider.addListener(this);
    cutoffSlider.setSkewFactorFromMidPoint(500);
    cutoffSlider.setValue(audioProcessor.cutoff); 
    addAndMakeVisible(cutoffSlider);

    addAndMakeVisible(cutoffLabel);
    cutoffLabel.setText("cutoff", juce::dontSendNotification);
    //cutoffLabel.attachToComponent(&cutoffSlider, false);

    oscillatorSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    oscillatorSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 50);
    oscillatorSlider.setNumDecimalPlacesToDisplay(2);
    oscillatorSlider.setRange(1.0f, 15.0f);
    oscillatorSlider.setTextValueSuffix(" Hz");
    oscillatorSlider.addListener(this);
    oscillatorSlider.setValue(audioProcessor.LCOFreq);
    addAndMakeVisible(oscillatorSlider);

    addAndMakeVisible(oscillatorLabel);
    oscillatorLabel.setText("rate", juce::dontSendNotification);
    //oscillatorLabel.attachToComponent(&oscillatorSlider, false);

    levelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    levelSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 50);
    levelSlider.setNumDecimalPlacesToDisplay(2);
    levelSlider.setRange(-100, 12.0f);
    levelSlider.setTextValueSuffix(" dB");
    levelSlider.addListener(this);
    levelSlider.setValue(0.0f); 
    addAndMakeVisible(levelSlider);

    addAndMakeVisible(levelLabel);
    levelLabel.setText("level", juce::dontSendNotification);
    //levelLabel.attachToComponent(&levelSlider, false);

    amountSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    amountSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 50);
    amountSlider.setNumDecimalPlacesToDisplay(2);
    amountSlider.setRange(0.0, 500.0);
    amountSlider.addListener(this);
    amountSlider.setValue(0.0);
    addAndMakeVisible(amountSlider);

    addAndMakeVisible(amountLabel);
    amountLabel.setText("amount", juce::dontSendNotification);
    //amountLabel.attachToComponent(&amountSlider, false);

    lfoButton.setClickingTogglesState(true);
    
    lfoButton.onClick = [&]()
    {
        const auto message = lfoButton.getToggleState() ? "LFO On" : "LFO Off";
        lfoButton.setButtonText(message);
        audioProcessor.LCOSwitch = lfoButton.getToggleState() ? true : false;

    };

    addAndMakeVisible(lfoButton);
    

    setSize (750, 300);
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

    auto centralArea = getLocalBounds().toFloat().reduced(10.0f);
    g.drawRoundedRectangle(centralArea, 5.0f, 3.0f);
    g.drawRoundedRectangle(300, 10, 300, getHeight() - 20, 5.0f, 3.0f);





    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void DiodeClipperAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto h = getHeight() / 2 - 30;
    
    pluginTitle.setBounds(15, 15, 200, 50);

    inGainSlider.setBounds(0, h, 150, 150);
    cutoffSlider.setBounds(150, h, 150, 150);
    oscillatorSlider.setBounds(300, h, 150, 150);
    amountSlider.setBounds(450, h, 150, 150);
    levelSlider.setBounds(600, h, 150, 150);

       
    inGainLabel.setBounds(0 + 55, h - 35, 50, 50);
    cutoffLabel.setBounds(150 + 55, h - 35, 50, 50);
    oscillatorLabel.setBounds(300 + 55, h - 35, 50, 50);
    amountLabel.setBounds(450 + 75 - 25, h - 35, 50, 50);
    levelLabel.setBounds(600 + 55, h - 35, 50, 50);
    lfoButton.setBounds(300, 10, 300, 80);
    
 

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
