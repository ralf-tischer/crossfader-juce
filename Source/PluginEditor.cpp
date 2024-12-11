#include "PluginEditor.h"
#include "CustomLookAndFeel.h"

CrossfaderjuceAudioProcessorEditor::CrossfaderjuceAudioProcessorEditor (CrossfaderjuceAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Create and set the custom look and feel
    customLookAndFeel = std::make_unique<CustomLookAndFeel>();
    amountSlider.setLookAndFeel(customLookAndFeel.get());

    // Configure the slider
    amountSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    amountSlider.setRange(0.0, 1.0, 0.01);
    amountSlider.setValue(0.5);
    amountSlider.addListener(this);

    // Add the slider to the editor
    addAndMakeVisible(&amountSlider);

    // Configure the label
    amountLabel.setText("Crossfade Amount: 0.5", juce::dontSendNotification);
    addAndMakeVisible(&amountLabel);

    // Set the size of the editor
    setSize (400, 300);
}

CrossfaderjuceAudioProcessorEditor::~CrossfaderjuceAudioProcessorEditor()
{
    // Reset the look and feel to avoid dangling pointers
    amountSlider.setLookAndFeel(nullptr);
}

void CrossfaderjuceAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Fill the background with a solid color
    g.fillAll (juce::Colours::black);
}

void CrossfaderjuceAudioProcessorEditor::resized()
{
    // Set the bounds of the slider and label
    amountSlider.setBounds (10, 10, getWidth() - 20, 20);
    amountLabel.setBounds (10, 40, getWidth() - 20, 20);
}

void CrossfaderjuceAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &amountSlider)
    {
        // Update the label text with the new slider value
        amountLabel.setText ("Crossfade Amount: " + juce::String (amountSlider.getValue()), juce::dontSendNotification);
    }
}