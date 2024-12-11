#include "PluginProcessor.h"
#include "PluginEditor.h"

CrossfaderjuceAudioProcessor::CrossfaderjuceAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input1", juce::AudioChannelSet::stereo(), true)
                       .withInput  ("Input2", juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       )
#endif
{
    addParameter(crossfaderParam = new juce::AudioParameterFloat("crossfader", "Crossfader", 0.0f, 1.0f, 0.5f));
}

CrossfaderjuceAudioProcessor::~CrossfaderjuceAudioProcessor()
{
}

//==============================================================================

const juce::String CrossfaderjuceAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CrossfaderjuceAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CrossfaderjuceAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CrossfaderjuceAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CrossfaderjuceAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CrossfaderjuceAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CrossfaderjuceAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CrossfaderjuceAudioProcessor::setCurrentProgram (int index)
{
    // Example: Set crossfader value based on program index
    if (index == 0)
        crossfaderParam->setValueNotifyingHost(0.0f);
    else if (index == 1)
        crossfaderParam->setValueNotifyingHost(1.0f);
    else
        crossfaderParam->setValueNotifyingHost(0.5f);
}

const juce::String CrossfaderjuceAudioProcessor::getProgramName (int index)
{
    return {};
}

void CrossfaderjuceAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================

void CrossfaderjuceAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Initialize the ProcessSpec structure
    mySpec.sampleRate = sampleRate;
    mySpec.maximumBlockSize = samplesPerBlock;
    mySpec.numChannels = getTotalNumOutputChannels();
}

void CrossfaderjuceAudioProcessor::releaseResources()
{
    // Release resources
}

bool CrossfaderjuceAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return true;
}

void CrossfaderjuceAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear any output channels that didn't contain input data
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Ensure we have 4 input channels and 2 output channels
    if (totalNumInputChannels >= 4 && totalNumOutputChannels >= 2)
    {
        auto* input1L = buffer.getReadPointer(0);
        auto* input1R = buffer.getReadPointer(1);
        auto* input2L = buffer.getReadPointer(2);
        auto* input2R = buffer.getReadPointer(3);
        auto* outputL = buffer.getWritePointer(0);
        auto* outputR = buffer.getWritePointer(1);

        // Ensure the pointers are valid before using them
        if (input1L != nullptr && input1R != nullptr && input2L != nullptr && input2R != nullptr && outputL != nullptr && outputR != nullptr)
        {
            // Process the audio data here
            float crossfadeAmount = getCrossfadeAmount();
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
            {
                outputL[sample] = input1L[sample] * (1.0f - crossfadeAmount) + input2L[sample] * crossfadeAmount;
                outputR[sample] = input1R[sample] * (1.0f - crossfadeAmount) + input2R[sample] * crossfadeAmount;
            }
        }
    }
}

//==============================================================================

bool CrossfaderjuceAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

void CrossfaderjuceAudioProcessor::setCrossfadeAmount(float amount)
{
    crossfadeAmount = amount;
    crossfader.setWetMixProportion(amount);
}

float CrossfaderjuceAudioProcessor::getCrossfadeAmount() const {
    return crossfadeAmount;
}

juce::AudioProcessorEditor* CrossfaderjuceAudioProcessor::createEditor()
{
    return new CrossfaderjuceAudioProcessorEditor (*this);
}

//==============================================================================

void CrossfaderjuceAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
}

void CrossfaderjuceAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block.
}

// This creates new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CrossfaderjuceAudioProcessor();
}