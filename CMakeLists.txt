# Usage:
# cmake -B cmake -B cmake-build -DCMAKE_PREFIX_PATH=d:/Tools/Coding/JUCE/install
# cmake --build cmake-build

cmake_minimum_required(VERSION 3.22)

# Set the project name and version
project(Crossfader VERSION 0.1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find JUCE package
find_package(JUCE CONFIG REQUIRED)

if (JUCE_FOUND)
    message(STATUS "JUCE found: ${JUCE_DIR}")
else()
    message(FATAL_ERROR "JUCE not found. Please check the CMAKE_PREFIX_PATH.")
endif()

# Add the executable
juce_add_plugin(Crossfader
    COMPANY_NAME "Ratsi"
    PLUGIN_MANUFACTURER_CODE Juce
    PLUGIN_CODE RSCF
    FORMATS VST3
    PRODUCT_NAME "Ratsi sein Crossfader")

# Generate the JUCE header
juce_generate_juce_header(Crossfader)

# Add source files
target_sources(Crossfader 
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp)

# Add header files
target_compile_definitions(Crossfader
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL)

# Link the JUCE libraries
target_link_libraries(Crossfader
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

# Specify the include directories
target_include_directories(Crossfader PRIVATE "D:/Tools/Coding/JUCE/modules")
