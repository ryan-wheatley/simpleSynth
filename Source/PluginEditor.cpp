#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
SimpleSynthAudioProcessorEditor::SimpleSynthAudioProcessorEditor (SimpleSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (692, 478);

    initialiseAttackOrReleaseSlider(triangleAttackSlider);
    initialiseAttackOrReleaseSlider(squareAttackSlider);
    initialiseAttackOrReleaseSlider(sawAttackSlider);

    initialiseAttackOrReleaseSlider(triangleReleaseSlider);
    initialiseAttackOrReleaseSlider(squareReleaseSlider);
    initialiseAttackOrReleaseSlider(sawReleaseSlider);

    initialiseSustainSlider(triangleSustainSlider);
    initialiseSustainSlider(squareSustainSlider);
    initialiseSustainSlider(sawSustainSlider);

    initialisePanSlider(trianglePanSlider);
    initialisePanSlider(squarePanSlider);
    initialisePanSlider(sawPanSlider);

    initialiseLevelSliders(triangleLevelSlider);
    initialiseLevelSliders(squareLevelSlider);
    initialiseLevelSliders(sawLevelSlider);

    triangleDecaySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    triangleDecaySlider.setRange(0.1f, 1000.0f);
    triangleDecaySlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    triangleDecaySlider.setValue(500.0f);
    triangleDecaySlider.addListener(this);
    triangleDecaySlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&triangleDecaySlider);

    triangleThickenSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    triangleThickenSlider.setRange(0.0f, 1.0f);
    triangleThickenSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    triangleThickenSlider.setValue(0.0f);
    triangleThickenSlider.addListener(this);
    triangleThickenSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&triangleThickenSlider);

    squareDecaySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    squareDecaySlider.setRange(0.1f, 1000.0f);
    squareDecaySlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    squareDecaySlider.setValue(500.0f);
    squareDecaySlider.addListener(this);
    squareDecaySlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&squareDecaySlider);

    squareThickenSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    squareThickenSlider.setRange(0.0f, 1.0f);
    squareThickenSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    squareThickenSlider.setValue(0.0f);
    squareThickenSlider.addListener(this);
    squareThickenSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&squareThickenSlider);

    sawDecaySlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sawDecaySlider.setRange(0.1f, 1000.0f);
    sawDecaySlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    sawDecaySlider.setValue(500.0f);
    sawDecaySlider.addListener(this);
    sawDecaySlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&sawDecaySlider);

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
    releaseDepthSlider.setRange(0, 8000);
    releaseDepthSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    releaseDepthSlider.setValue(2000);
    releaseDepthSlider.addListener(this);
    releaseDepthSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&releaseDepthSlider);
    
    globalCutoffSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    globalCutoffSlider.setRange(40,8000);
    globalCutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    globalCutoffSlider.setValue(7000);
    globalCutoffSlider.addListener(this);
    globalCutoffSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&globalCutoffSlider);

    globalResonanceSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    globalResonanceSlider.setRange(0.0f, 10.0f);
    globalResonanceSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    globalResonanceSlider.setValue(0.0f);
    globalResonanceSlider.addListener(this);
    globalResonanceSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&globalResonanceSlider);

    gateDepthSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gateDepthSlider.setRange(0.0f, 1.0f);
    gateDepthSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    gateDepthSlider.setValue(0.0f);
    gateDepthSlider.addListener(this);
    gateDepthSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&gateDepthSlider);

    gateSpeedSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gateSpeedSlider.setRange(0.0f, 10.0f);
    gateSpeedSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    gateSpeedSlider.setValue(4.0f);
    gateSpeedSlider.addListener(this);
    gateSpeedSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&gateSpeedSlider);

    volumeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumeSlider.setRange(0.0f, 1.0f);
    volumeSlider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    volumeSlider.setValue(0.5f);
    volumeSlider.addListener(this);
    volumeSlider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&volumeSlider);

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

    sliderTreeTrianglePan = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "trianglePan", trianglePanSlider);
    sliderTreeSquarePan = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "squarePan", squarePanSlider);
    sliderTreeSawPan = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "sawPan", sawPanSlider);

    sliderTreeReleaseSpeed = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "releaseSpeed", releaseSpeedSlider);
    sliderTreeReleaseDepth = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "releaseDepth", releaseDepthSlider);

    sliderTreeGlobalCutoff = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "globalCutoff", globalCutoffSlider);
    sliderTreeGlobalResonance = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "globalResonance", globalResonanceSlider);

    sliderTreeGateDepth = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "gateDepth", gateDepthSlider);
    sliderTreeGateSpeed = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "gateSpeed", gateSpeedSlider);

    sliderTreeVolume = std::make_unique< AudioProcessorValueTreeState::SliderAttachment>(processor.tree, "volume", volumeSlider);
}

SimpleSynthAudioProcessorEditor::~SimpleSynthAudioProcessorEditor()
{
}

//==============================================================================
void SimpleSynthAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);

    g.setColour(Colours::whitesmoke);
    g.fillRoundedRectangle(10, 50, 249, 274, 1.5);
    g.fillRoundedRectangle(263, 50, 330, 274, 1.5);
    g.fillRoundedRectangle(10, 328, 249, 140, 1.5);
    g.fillRoundedRectangle(263, 328, 165, 140, 1.5);
    g.fillRoundedRectangle(432, 328, 161, 140, 1.5);
    g.fillRoundedRectangle(597, 50, 85, 274, 1.5);
    g.fillRoundedRectangle(597, 328, 85, 140, 1.5);

    g.setColour (Colours::whitesmoke);
    g.setFont (15.0f);
    g.setFont(Font("Times New Roman", 20.0f, Font::italic));
    g.drawText("Mine Is Yours", 450, 5, 200, 40, Justification::centred, true);
    g.drawLine(10, 25, 480, 25,1);
    g.drawLine(615, 25, 682, 25, 1);

    g.setColour(Colours::black);
    g.setFont(Font("Arial", 12.0f, Font::bold));
    g.drawText("LEVEL", 85, 60, 80, 20, Justification::centred, true);
    g.drawText("THICKEN", 165, 60, 80, 20, Justification::centred, true);
    g.drawText("DEPTH", 85, 440, 80, 20, Justification::centred, true);
    g.drawText("ATTACK", 165, 440, 80, 20, Justification::centred, true);
    g.drawText("CUT OFF", 270, 440, 80, 20, Justification::centred, true);
    g.drawText("RES", 350, 440, 80, 20, Justification::centred, true);
    g.drawText("DEPTH", 430, 440, 80, 20, Justification::centred, true);
    g.drawText("RATE", 510, 440, 80, 20, Justification::centred, true);
    g.drawText("VOLUME", 600, 340, 80, 20, Justification::centred, true);

    g.drawText("RELEASE FILTER SWEEP", 10, 340, 180, 20, Justification::centred, true);
    g.drawText("GLOBAL LOW PASS", 275, 340, 130, 20, Justification::centred, true);
    g.drawText("GATE", 405, 340, 130, 20, Justification::centred, true);

    g.setColour(Colours::darkgrey);
    g.drawText("(SUPER)", 165, 230, 80, 20, Justification::centred, true);

    g.setColour(Colours::black);
    g.drawText("A", 300, 60, 20, 20, Justification::centred, true);
    g.drawText("D", 380, 60, 20, 20, Justification::centred, true);
    g.drawText("S", 460, 60, 20, 20, Justification::centred, true);
    g.drawText("R", 540, 60, 20, 20, Justification::centred, true);
    g.drawText("PAN", 620, 60, 40, 20, Justification::centred, true);

    g.setColour(Colours::indianred);

    g.drawLine(20, 120, 40, 100, 3);
    g.drawLine(40, 100, 60, 120, 3);
    g.drawLine(60, 120, 80, 100, 3);

    g.drawLine(20, 200, 20, 180, 3);
    g.drawLine(20, 180, 40, 180, 3);
    g.drawLine(40, 200, 40, 180, 3);
    g.drawLine(40, 200, 60, 200, 3);
    g.drawLine(60, 180, 60, 200, 3);
    g.drawLine(60, 180, 80, 180, 3);

    g.drawLine(20, 280, 40, 260, 3);
    g.drawLine(40, 260, 40, 280, 3);
    g.drawLine(40, 280, 60, 260, 3);
    g.drawLine(60, 260, 60, 280, 3);
    g.drawLine(60, 280, 80, 260, 3);
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

    trianglePanSlider.setBounds(605, 80, 70, 70);
    squarePanSlider.setBounds(605, 160, 70, 70);
    sawPanSlider.setBounds(605, 240, 70, 70);


    releaseDepthSlider.setBounds(90, 370, 70, 70);
    releaseSpeedSlider.setBounds(170, 370, 70, 70);

    globalCutoffSlider.setBounds(275, 370, 70, 70);
    globalResonanceSlider.setBounds(355, 370, 70, 70);

    gateDepthSlider.setBounds(435, 370, 70, 70);
    gateSpeedSlider.setBounds(515, 370, 70, 70);

    volumeSlider.setBounds(605, 370, 70, 70);
}

void  SimpleSynthAudioProcessorEditor::initialiseLevelSliders(Slider& slider) {

    slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setRange(0.0f, 1.0f);
    slider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    slider.addListener(this);
    slider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&slider);
}    

void  SimpleSynthAudioProcessorEditor::initialiseAttackOrReleaseSlider(Slider& slider) {

    slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setRange(0.1f, 4000.0f);
    slider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    slider.setValue(2000);
    slider.addListener(this);
    slider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&slider);
}

void  SimpleSynthAudioProcessorEditor::initialiseSustainSlider(Slider& slider) {
    slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setRange(0.1f, 1.0f);
    slider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    slider.setValue(0.5f);
    slider.addListener(this);
    slider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&slider);
}

void  SimpleSynthAudioProcessorEditor::initialisePanSlider(Slider& slider) {
    slider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setRange(-0.5f, 0.5f);
    slider.setTextBoxStyle(Slider::NoTextBox, false, 100, 20);
    slider.setValue(0.0f);
    slider.addListener(this);
    slider.setPopupDisplayEnabled(true, true, nullptr, -1);
    addAndMakeVisible(&slider);
}

void SimpleSynthAudioProcessorEditor::sliderValueChanged(Slider* slider)
{

}
