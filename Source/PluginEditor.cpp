#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
SimpleSynthAudioProcessorEditor::SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (800, 600);

    triangleAttackSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    triangleAttackSlider.setRange(0.1f, 4000.0f);
    triangleAttackSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    triangleAttackSlider.setValue(2000);
    triangleAttackSlider.addListener(this);
    triangleAttackSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&triangleAttackSlider);

    triangleDecaySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    triangleDecaySlider.setRange(0.1f, 1000.0f);
    triangleDecaySlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    triangleDecaySlider.setValue(500.0f);
    triangleDecaySlider.addListener(this);
    triangleDecaySlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&triangleDecaySlider);

    triangleSustainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    triangleSustainSlider.setRange(0.1f, 1.0f);
    triangleSustainSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    triangleSustainSlider.setValue(0.5f);
    triangleSustainSlider.addListener(this);
    triangleSustainSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&triangleSustainSlider);

    triangleReleaseSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    triangleReleaseSlider.setRange(0.1f, 4000.0f);
    triangleReleaseSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    triangleReleaseSlider.setValue(2000.0f);
    triangleReleaseSlider.addListener(this);
    triangleReleaseSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&triangleReleaseSlider);

    triangleLevelSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    triangleLevelSlider.setRange(0.0f, 1.0f);
    triangleLevelSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    triangleLevelSlider.setValue(0.0f);
    triangleLevelSlider.addListener(this);
    triangleLevelSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&triangleLevelSlider);

    triangleThickenSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    triangleThickenSlider.setRange(0.0f, 1.0f);
    triangleThickenSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    triangleThickenSlider.setValue(0.0f);
    triangleThickenSlider.addListener(this);
    triangleThickenSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&triangleThickenSlider);

    squareAttackSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    squareAttackSlider.setRange(0.1f, 4000.0f);
    squareAttackSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    squareAttackSlider.setValue(2000);
    squareAttackSlider.addListener(this);
    squareAttackSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&squareAttackSlider);

    squareDecaySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    squareDecaySlider.setRange(0.1f, 1000.0f);
    squareDecaySlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    squareDecaySlider.setValue(500.0f);
    squareDecaySlider.addListener(this);
    squareDecaySlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&squareDecaySlider);

    squareSustainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    squareSustainSlider.setRange(0.1f, 1.0f);
    squareSustainSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    squareSustainSlider.setValue(0.5f);
    squareSustainSlider.addListener(this);
    squareSustainSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&squareSustainSlider);

    squareReleaseSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    squareReleaseSlider.setRange(0.1f, 4000.0f);
    squareReleaseSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    squareReleaseSlider.setValue(2000.0f);
    squareReleaseSlider.addListener(this);
    squareReleaseSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&squareReleaseSlider);

    squareLevelSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    squareLevelSlider.setRange(0.0f, 1.0f);
    squareLevelSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    squareLevelSlider.setValue(0.0f);
    squareLevelSlider.addListener(this);
    squareLevelSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&squareLevelSlider);

    squareThickenSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    squareThickenSlider.setRange(0.0f, 1.0f);
    squareThickenSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    squareThickenSlider.setValue(0.0f);
    squareThickenSlider.addListener(this);
    squareThickenSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&squareThickenSlider);

    sawAttackSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sawAttackSlider.setRange(0.1f, 4000.0f);
    sawAttackSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    sawAttackSlider.setValue(2000);
    sawAttackSlider.addListener(this);
    sawAttackSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&sawAttackSlider);

    sawDecaySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sawDecaySlider.setRange(0.1f, 1000.0f);
    sawDecaySlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    sawDecaySlider.setValue(500.0f);
    sawDecaySlider.addListener(this);
    sawDecaySlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&sawDecaySlider);

    sawSustainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sawSustainSlider.setRange(0.1f, 1.0f);
    sawSustainSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    sawSustainSlider.setValue(0.5f);
    sawSustainSlider.addListener(this);
    sawSustainSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&sawSustainSlider);

    sawReleaseSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sawReleaseSlider.setRange(0.1f, 4000.0f);
    sawReleaseSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    sawReleaseSlider.setValue(2000.0f);
    sawReleaseSlider.addListener(this);
    sawReleaseSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&sawReleaseSlider);

    sawLevelSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sawLevelSlider.setRange(0.0f, 1.0f);
    sawLevelSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    sawLevelSlider.setValue(0.0f);
    sawLevelSlider.addListener(this);
    sawLevelSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&sawLevelSlider);

    sawThickenSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sawThickenSlider.setRange(0.0f, 1.0f);
    sawThickenSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    sawThickenSlider.setValue(0.0f);
    sawThickenSlider.addListener(this);
    sawThickenSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&sawThickenSlider);

    releaseSpeedSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSpeedSlider.setRange(0.1f, 4000.0f);
    releaseSpeedSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    releaseSpeedSlider.setValue(2000.0f);
    releaseSpeedSlider.addListener(this);
    releaseSpeedSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&releaseSpeedSlider);

    releaseDepthSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseDepthSlider.setRange(0.1f, 10000.0f);
    releaseDepthSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    releaseDepthSlider.setValue(2000.0f);
    releaseDepthSlider.addListener(this);
    releaseDepthSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&releaseDepthSlider);
    
    sliderTreeTriangleLevel = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "triangleLevel", triangleLevelSlider);
    sliderTreeTriangleThicken = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "triangleThicken", triangleThickenSlider);
    sliderTreeTriangleAttack = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "triangleAttack", triangleAttackSlider);
    sliderTreeTriangleDecay = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "triangleDecay", triangleDecaySlider);
    sliderTreeTriangleSustain = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "triangleSustain", triangleSustainSlider);
    sliderTreeTrinagleRelease = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "triangleRelease", triangleReleaseSlider);

    sliderTreeSquareLevel = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "squareLevel", squareLevelSlider);
    sliderTreeSquareThicken = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "squareThicken", squareThickenSlider);
    sliderTreeSquareAttack = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "squareAttack", squareAttackSlider);
    sliderTreeSquareDecay = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "squareDecay", squareDecaySlider);
    sliderTreeSquareSustain = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "squareSustain", squareSustainSlider);
    sliderTreeSquareRelease = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "squareRelease", squareReleaseSlider);

    sliderTreeSawLevel = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "sawLevel", sawLevelSlider);
    sliderTreeSawThicken = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "sawThicken", sawThickenSlider);
    sliderTreeSawAttack = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "sawAttack", sawAttackSlider);
    sliderTreeSawDecay = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "sawDecay", sawDecaySlider);
    sliderTreeSawSustain = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "sawSustain", sawSustainSlider);
    sliderTreeSawRelease = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "sawRelease", sawReleaseSlider);

    sliderTreeReleaseSpeed = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "releaseSpeed", releaseSpeedSlider);
    sliderTreeReleaseDepth = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "releaseDepth", releaseDepthSlider);
}

SimpleSynthAudioProcessorEditor::~SimpleSynthAudioProcessorEditor()
{
}

//==============================================================================
void SimpleSynthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);

    g.setColour(Colours::whitesmoke);
    g.fillRoundedRectangle(10, 50, 245, 270, 1.5);
    g.fillRoundedRectangle(265, 50, 330, 270, 1.5);
    g.fillRoundedRectangle(10, 330, 245, 140, 1.5);


    g.setColour (Colours::whitesmoke);
    g.setFont (15.0f);
    g.setFont(Font("Times New Roman", 20.0f, Font::italic));
    g.drawText("Mine Is Yours", 500, 5, 200, 40, Justification::centred, true);

    g.setColour(Colours::black);
    g.setFont(Font("Arial", 16.0f, Font::bold));
    g.drawText("LEVEL", 85, 60, 80, 20, Justification::centred, true);
    g.drawText("THICKEN", 165, 60, 80, 20, Justification::centred, true);
    g.drawText("DEPTH", 85, 440, 80, 20, Justification::centred, true);
    g.drawText("SPEED", 165, 440, 80, 20, Justification::centred, true);
    g.drawText("RELEASE FILTER SWEEP", 10, 340, 200, 20, Justification::centred, true);

    g.setColour(Colours::darkgrey);
    g.drawText("(SUPER)", 165, 230, 80, 20, Justification::centred, true);

    g.setColour(Colours::black);
    g.drawText("A", 300, 60, 20, 20, Justification::centred, true);
    g.drawText("D", 380, 60, 20, 20, Justification::centred, true);
    g.drawText("S", 460, 60, 20, 20, Justification::centred, true);
    g.drawText("R", 540, 60, 20, 20, Justification::centred, true);

    g.drawLine(20, 120, 40, 100, 3);
    g.drawLine(40, 100, 60, 120, 3);
    g.drawLine(60, 120, 80, 100, 3);

}

void SimpleSynthAudioProcessorEditor::resized()
{
    triangleLevelSlider.setBounds(90, 80, 70, 70);
    triangleThickenSlider.setBounds(170, 80, 70, 70);
    triangleAttackSlider.setBounds(275, 80, 70, 70);
    triangleDecaySlider.setBounds(355, 80, 70, 70);
    triangleSustainSlider.setBounds(435, 80, 70, 70);
    triangleReleaseSlider.setBounds(515, 80, 70, 70);
   
    squareLevelSlider.setBounds(90, 160, 70, 70);
    squareThickenSlider.setBounds(170, 160, 70, 70);
    squareAttackSlider.setBounds(275, 160, 70, 70);
    squareDecaySlider.setBounds(355, 160, 70, 70);
    squareSustainSlider.setBounds(435, 160, 70, 70);
    squareReleaseSlider.setBounds(515, 160, 70, 70);

    sawLevelSlider.setBounds(90, 240, 70, 70);
    sawThickenSlider.setBounds(170, 240, 70, 70);
    sawAttackSlider.setBounds(275, 240, 70, 70);
    sawDecaySlider.setBounds(355, 240, 70, 70);
    sawSustainSlider.setBounds(435, 240, 70, 70);
    sawReleaseSlider.setBounds(515, 240, 70, 70);

    releaseDepthSlider.setBounds(90, 370, 70, 70);
    releaseSpeedSlider.setBounds(170, 370, 70, 70);
}

void SimpleSynthAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
 
}
