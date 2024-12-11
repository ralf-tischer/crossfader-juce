#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
class CrossfaderjuceAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            private juce::Slider::Listener
{
public:
    CrossfaderjuceAudioProcessorEditor (CrossfaderjuceAudioProcessor&);
    ~CrossfaderjuceAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged (juce::Slider* slider) override;

    CrossfaderjuceAudioProcessor& audioProcessor;

    juce::Slider amountSlider;
    juce::Label amountLabel;
    std::unique_ptr<CustomLookAndFeel> customLookAndFeel; // Add this line

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrossfaderjuceAudioProcessorEditor)
};