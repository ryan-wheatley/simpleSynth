#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SimpleSynthAudioProcessorEditor : public AudioProcessorEditor,
                                        public Slider::Listener
{
public:
    SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor&);
    ~SimpleSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* ) override;

    void initialiseLevelSliders(Slider&);
    void initialiseAttackOrReleaseSlider(Slider&);
    void initialiseSustainSlider(Slider&);

    void initialisePanSlider(Slider&);

private:

    SimpleSynthAudioProcessor& processor;

    Slider triangleLevelSlider;
    Slider triangleThickenSlider;
    Slider triangleAttackSlider;
    Slider triangleDecaySlider;
    Slider triangleSustainSlider;
    Slider triangleReleaseSlider;
    
    Slider squareLevelSlider;
    Slider squareThickenSlider;
    Slider squareAttackSlider;
    Slider squareDecaySlider;
    Slider squareSustainSlider;
    Slider squareReleaseSlider;

    Slider sawLevelSlider;
    Slider sawThickenSlider;
    Slider sawAttackSlider;
    Slider sawDecaySlider;
    Slider sawSustainSlider;
    Slider sawReleaseSlider;

    Slider releaseSpeedSlider;
    Slider releaseDepthSlider;

    Slider globalCutoffSlider;
    Slider globalResonanceSlider;

    Slider gateDepthSlider;
    Slider gateSpeedSlider;

    Slider trianglePanSlider;
    Slider squarePanSlider;
    Slider sawPanSlider;

    Slider volumeSlider;

public:
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeTriangleLevel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeTriangleThicken;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeTriangleAttack;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeTriangleDecay;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeTriangleSustain;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeTrinagleRelease;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSquareLevel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSquareThicken;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSquareAttack;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSquareDecay;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSquareSustain;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSquareRelease;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSawLevel;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSawThicken;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSawAttack;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSawDecay;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSawSustain;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSawRelease;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeTrianglePan;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSquarePan;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeSawPan;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeReleaseDepth;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeReleaseSpeed;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeGlobalCutoff;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeGlobalResonance;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeGateDepth;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeGateSpeed;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sliderTreeVolume;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleSynthAudioProcessorEditor)
};
