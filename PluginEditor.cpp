/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveformVisAudioProcessorEditor::WaveformVisAudioProcessorEditor (WaveformVisAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(audioProcessor.waveViewer);
    audioProcessor.waveViewer.setColours(juce::Colours::black, juce::Colours::whitesmoke.withAlpha(0.5f));
    setSize (400, 300);

    waveZoom.setRange(32.0, 1024.0, 1.0);
    waveZoom.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    waveZoom.setTextBoxStyle(Slider::TextBoxBelow,true,50,20);
    addAndMakeVisible(waveZoom);

    waveZoom.onValueChange = [this]()
    {
        audioProcessor.waveViewer.setBufferSize(waveZoom.getValue());
    };
}

WaveformVisAudioProcessorEditor::~WaveformVisAudioProcessorEditor()
{
}

//==============================================================================
void WaveformVisAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void WaveformVisAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    audioProcessor.waveViewer.setBounds(getLocalBounds().withSizeKeepingCentre(getWidth() * 0.5, getHeight() * 0.5));
    waveZoom.setBounds(audioProcessor.waveViewer.getX() + audioProcessor.waveViewer.getWidth(), audioProcessor.waveViewer.getY(), 128, audioProcessor.waveViewer.getHeight());
}
