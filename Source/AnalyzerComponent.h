/*
  =============================================================================

    AnalyzerComponent.
    Created: 2 Nov 2022 4:44:00p
    Author:  Andrew Oral

  =============================================================================
*/

#pragma onc

#include <JuceHeader.h>
#include "PluginProcessor.h"

//=============================================================================
class AnalyzerComponent  : public juce::Component,
                           private juce::Timer
{
public:
    AnalyzerComponent(SIGMusicFFTDemoAudioProcessor& ap_) : ap(ap_),
                          forwardFFT(ap.fftOrder),
                          window(ap.fftSize, juce::dsp::WindowingFunction<float>::hann)
    {
        setOpaque (true);
        startTimerHz(30);
        setSize (700, 500);
    }
    
    ~AnalyzerComponent() override {}
   
    virtual void timerCallback() override
    {
        if (ap.nextFFTBlockReady)
        {
            drawNextFrameOfSpectrum();
            ap.nextFFTBlockReady = false;
            repaint();
        }
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::black);

        g.setOpacity (1.0f);
        g.setColour (juce::Colours::white);
        drawFrame (g);
    }
 
    void drawNextFrameOfSpectrum()
    {
        // first apply a windowing function to our data
        window.multiplyWithWindowingTable (ap.fftData, ap.fftSize);       // [1]

        // then render our FFT data..
        forwardFFT.performFrequencyOnlyForwardTransform (ap.fftData);  // [2]

        auto mindB = -100.0f;
        auto maxdB =    0.0f;

        for (int i = 0; i < ap.scopeSize; ++i)                         // [3]
        {
            auto skewedProportionX = 1.0f - std::exp (std::log (1.0f - (float) i / (float) ap.scopeSize) * 0.2f);
            auto fftDataIndex = juce::jlimit (0, ap.fftSize / 2, (int) (skewedProportionX * (float) ap.fftSize * 0.5f));
            auto level = juce::jmap (juce::jlimit (mindB, maxdB, juce::Decibels::gainToDecibels (ap.fftData[fftDataIndex])
                                                               - juce::Decibels::gainToDecibels ((float) ap.fftSize)),
                                     mindB, maxdB, 0.0f, 1.0f);

            ap.scopeData[i] = level;                                   // [4]
        }
    }

    void drawFrame (juce::Graphics& g)
    {
        for (int i = 1; i < ap.scopeSize; ++i)
        {
            auto width  = getLocalBounds().getWidth();
            auto height = getLocalBounds().getHeight();

            g.drawLine ({ (float) juce::jmap (i - 1, 0, ap.scopeSize - 1, 0, width),
                                  juce::jmap (ap.scopeData[i - 1], 0.0f, 1.0f, (float) height, 0.0f),
                          (float) juce::jmap (i,     0, ap.scopeSize - 1, 0, width),
                                  juce::jmap (ap.scopeData[i],     0.0f, 1.0f, (float) height, 0.0f) });
        }
    }

private:
    SIGMusicFFTDemoAudioProcessor& ap;
    juce::dsp::FFT forwardFFT;                      // [4]
    juce::dsp::WindowingFunction<float> window;     // [5]

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalyzerComponent);
};

