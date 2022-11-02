/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SIGMusicFFTDemoAudioProcessorEditor::SIGMusicFFTDemoAudioProcessorEditor (SIGMusicFFTDemoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    analyzer.reset(new AnalyzerComponent(p));
    addAndMakeVisible(analyzer.get());
    setSize (400, 300);
}

SIGMusicFFTDemoAudioProcessorEditor::~SIGMusicFFTDemoAudioProcessorEditor()
{
}

//==============================================================================
void SIGMusicFFTDemoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void SIGMusicFFTDemoAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
