/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SIGMusicFFTDemoAudioProcessor::SIGMusicFFTDemoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

SIGMusicFFTDemoAudioProcessor::~SIGMusicFFTDemoAudioProcessor()
{
}

//==============================================================================
const juce::String SIGMusicFFTDemoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SIGMusicFFTDemoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SIGMusicFFTDemoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SIGMusicFFTDemoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SIGMusicFFTDemoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SIGMusicFFTDemoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SIGMusicFFTDemoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SIGMusicFFTDemoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SIGMusicFFTDemoAudioProcessor::getProgramName (int index)
{
    return {};
}

void SIGMusicFFTDemoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SIGMusicFFTDemoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SIGMusicFFTDemoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SIGMusicFFTDemoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SIGMusicFFTDemoAudioProcessor::pushNextSampleIntoFifo (float sample) noexcept
{
    // if the fifo contains enough data, set a flag to say
    // that the next frame should now be rendered..

    // TODO
}

void SIGMusicFFTDemoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    if (buffer.getNumChannels() > 0)
    {
        auto* channelData = buffer.getReadPointer (0);

        for (auto i = 0; i < buffer.getNumSamples(); ++i)
            (void) i; // TODO
    }
}

//==============================================================================
bool SIGMusicFFTDemoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SIGMusicFFTDemoAudioProcessor::createEditor()
{
    return new SIGMusicFFTDemoAudioProcessorEditor (*this);
}

//==============================================================================
void SIGMusicFFTDemoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SIGMusicFFTDemoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SIGMusicFFTDemoAudioProcessor();
}
