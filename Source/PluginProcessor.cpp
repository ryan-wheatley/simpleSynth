#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SimpleSynthAudioProcessor::SimpleSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ),
    tree(*this, nullptr, "PARAMATER", {std::make_unique<AudioParameterFloat>("triangleAttack","triangleAttack", 0.1f, 4000.0f,200.0f),
        std::make_unique<AudioParameterFloat>("triangleRelease","triangleRelease", 0.1f, 4000.0f,2000.0f),
        std::make_unique<AudioParameterFloat>("triangleThicken","triangleThicken", 0.0f, 1.0f,0.0f),
        std::make_unique<AudioParameterFloat>("triangleLevel","triangleLevel", 0.0f, 1.0f,1.0f),
        std::make_unique<AudioParameterFloat>("triangleDecay","triangleDecay", 0.1f, 1000.0f,500.0f),  
        std::make_unique<AudioParameterFloat>("triangleSustain","triangleSustain", 0.1f, 1.0f,0.5f),
        
        std::make_unique<AudioParameterFloat>("squareLevel","squareLevel", 0.0f, 1.0f,0.0f),
        std::make_unique<AudioParameterFloat>("squareThicken","squareThicken", 0.0f, 1.0f,0.0f),
        std::make_unique<AudioParameterFloat>("squareAttack","squareAttack", 0.1f, 4000.0f,200.0f),
        std::make_unique<AudioParameterFloat>("squareDecay","squareDecay", 0.1f, 1000.0f,500.0f),
        std::make_unique<AudioParameterFloat>("squareSustain","squareSustain", 0.1f, 1.0f,0.5f),
        std::make_unique<AudioParameterFloat>("squareRelease","squareRelease", 0.1f, 4000.0f,2000.0f),

        std::make_unique<AudioParameterFloat>("sawLevel","sawLevel", 0.0f, 1.0f,0.0f),
        std::make_unique<AudioParameterFloat>("sawThicken","sawThicken", 0.0f, 1.0f,0.0f),
        std::make_unique<AudioParameterFloat>("sawAttack","sawAttack", 0.1f, 4000.0f,200.0f),
        std::make_unique<AudioParameterFloat>("sawDecay","sawDecay", 0.1f, 1000.0f,500.0f),
        std::make_unique<AudioParameterFloat>("sawSustain","sawSustain", 0.1f, 1.0f,0.5f),
        std::make_unique<AudioParameterFloat>("sawRelease","sawRelease", 0.1f, 4000.0f,2000.0f),

        std::make_unique<AudioParameterFloat>("releaseDepth","releaseDepth", 0.1f, 10000.0f,2000.0f),
        std::make_unique<AudioParameterFloat>("releaseSpeed","releaseSpeed", 0.1f, 4000.0f,2000.0f)

        } )
#endif
{

    mySynth.clearVoices();

    for (int i = 0; i < 5; i++) {
        mySynth.addVoice(new SynthVoice());
    }

    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());

}

SimpleSynthAudioProcessor::~SimpleSynthAudioProcessor()
{
}

//==============================================================================
const String SimpleSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SimpleSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SimpleSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SimpleSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SimpleSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SimpleSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SimpleSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String SimpleSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void SimpleSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SimpleSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void SimpleSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void SimpleSynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    for (int i= 0 ; i < mySynth.getNumVoices(); i++) {
        if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))) {
            float* newFloatPtr = (float*)tree.getRawParameterValue("triangleAttack");
            float* newFloatPtr2 = (float*)tree.getRawParameterValue("triangleRelease");
            float* newFloatPtr3 = (float*)tree.getRawParameterValue("triangleThicken");
            float* newFloatPtr4 = (float*)tree.getRawParameterValue("triangleLevel");
            float* newFloatPtr5 = (float*)tree.getRawParameterValue("triangleDecay");
            float* newFloatPtr6 = (float*)tree.getRawParameterValue("triangleSustain");
            
            float* newFloatPtr7 = (float*)tree.getRawParameterValue("squareLevel");
            float* newFloatPtr8 = (float*)tree.getRawParameterValue("squareThicken");
            float* newFloatPtr9 = (float*)tree.getRawParameterValue("squareAttack");
            float* newFloatPtr10 = (float*)tree.getRawParameterValue("squareDecay");
            float* newFloatPtr11 = (float*)tree.getRawParameterValue("squareSustain");
            float* newFloatPtr12 = (float*)tree.getRawParameterValue("squareRelease");

            float* newFloatPtr13 = (float*)tree.getRawParameterValue("sawLevel");
            float* newFloatPtr14 = (float*)tree.getRawParameterValue("sawThicken");
            float* newFloatPtr15 = (float*)tree.getRawParameterValue("sawAttack");
            float* newFloatPtr16 = (float*)tree.getRawParameterValue("sawDecay");
            float* newFloatPtr17 = (float*)tree.getRawParameterValue("sawSustain");
            float* newFloatPtr18 = (float*)tree.getRawParameterValue("sawRelease");

            float* newFloatPtr19 = (float*)tree.getRawParameterValue("releaseDepth");
            float* newFloatPtr20 = (float*)tree.getRawParameterValue("releaseSpeed");

            myVoice->getParam(newFloatPtr, newFloatPtr2, newFloatPtr3,newFloatPtr4, newFloatPtr5, newFloatPtr6,
            newFloatPtr7, newFloatPtr8, newFloatPtr9, newFloatPtr10, newFloatPtr11, newFloatPtr12,
            newFloatPtr13, newFloatPtr14, newFloatPtr15, newFloatPtr16, newFloatPtr17, newFloatPtr18, newFloatPtr19, newFloatPtr20);
        }
    }

    buffer.clear();

    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
}

//==============================================================================
bool SimpleSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimpleSynthAudioProcessor::createEditor()
{
    return new SimpleSynthAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SimpleSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SimpleSynthAudioProcessor();
}
