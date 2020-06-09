#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
/**
*/
class SimpleSynthAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SimpleSynthAudioProcessor();
    ~SimpleSynthAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float triangleLevel;
    float triangleThicken;
    float triangleAttackTime;
    float triangleDecayTime;
    float triangleSustainTime;
    float triagleReleaseTime;

    float squareLevel;
    float squareThicken;
    float squareAttackTime;
    float squareDecayTime;
    float squareSustainTime;
    float squareReleaseTime;

   

    AudioProcessorValueTreeState tree;

private:
    Synthesiser mySynth;
    SynthVoice* myVoice;

    double lastSampleRate;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessor)
};
