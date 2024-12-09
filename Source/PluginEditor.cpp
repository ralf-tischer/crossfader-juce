#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CrossfaderjuceAudioProcessorEditor::CrossfaderjuceAudioProcessorEditor (CrossfaderjuceAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
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
}

//==============================================================================
void CrossfaderjuceAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void CrossfaderjuceAudioProcessorEditor::resized()
{
    // Set the bounds of the slider
    amountSlider.setBounds(10, 10, getWidth() - 20, 20);
    amountLabel.setBounds(10, 40, getWidth() - 20, 20);
}

void CrossfaderjuceAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &amountSlider)
    {
        // Handle the slider value change
        audioProcessor.setCrossfadeAmount(slider->getValue());

        // Update the label text
        amountLabel.setText("Crossfade Amount: " + juce::String(slider->getValue()), juce::dontSendNotification);
    }
}