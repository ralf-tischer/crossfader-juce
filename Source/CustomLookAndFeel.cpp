#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel()
{
    // Load the background image from the file
    sliderBackground = juce::ImageFileFormat::loadFrom (juce::File ("../Assets/img/Slider.png"));
        if (!sliderBackground.isValid())
    {
        std::cerr << "Failed to load Slider.png" << std::endl;
    }
    else
    {
        std::cout << "Successfully loaded Slider.png" << std::endl;
    }


    // Load the thumb image from the file
    sliderThumb = juce::ImageFileFormat::loadFrom (juce::File ("../Assets/img/Thumb.png"));
}

void CustomLookAndFeel::drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                                          float sliderPos, float minSliderPos, float maxSliderPos,
                                          const juce::Slider::SliderStyle, juce::Slider& slider)
{
    // Draw the background image
    if (sliderBackground.isValid())
    {
        g.drawImage (sliderBackground, x, y, width, height, 0, 0, sliderBackground.getWidth(), sliderBackground.getHeight());
    }
    else
    {
        g.fillAll (juce::Colours::darkgrey); // Fallback background color
    }

    // Draw the slider thumb
    if (sliderThumb.isValid())
    {
        int thumbWidth = sliderThumb.getWidth();
        int thumbHeight = sliderThumb.getHeight();
        g.drawImage (sliderThumb, static_cast<int> (sliderPos) - thumbWidth / 2, y + (height - thumbHeight) / 2, thumbWidth, thumbHeight, 0, 0, thumbWidth, thumbHeight);
    }
    else
    {
        g.setColour (juce::Colours::lightblue);
        g.fillRect (static_cast<int> (sliderPos), y, 10, height);
    }
}