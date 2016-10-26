/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PolyPlugAudioProcessorEditor::PolyPlugAudioProcessorEditor (PolyPlugAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1020, 230);
    addAndMakeVisible (frequencySlider);
    frequencySlider.setRange (50.0, 5000.0);
    frequencySlider.setValue(440);
    frequencySlider.setSliderStyle(Slider::Rotary);
    frequencySlider.setSkewFactorFromMidPoint (1500.0);
    frequencySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 0,0);
    frequencySlider.addListener (this);

    addAndMakeVisible(frequencyLabel);
    frequencyLabel.setText ("Freq", dontSendNotification);
    frequencyLabel.attachToComponent (&frequencySlider, false);
    
    
    // OSC Selection Knob and Labels
    addAndMakeVisible(oscKnob);
    oscKnob.setRange (0, 3, 1);
    oscKnob.setSliderStyle(Slider::Rotary);
    oscKnob.setTextBoxStyle(Slider::NoTextBox, false, 0,0);
    addAndMakeVisible(sineLabel);
    addAndMakeVisible(sqrLabel);
    addAndMakeVisible(sawLabel);
    addAndMakeVisible(noiseLabel);
    addAndMakeVisible(oscName);
    sineLabel.setText("sin",dontSendNotification);
    sqrLabel.setText ("sqr", dontSendNotification);
    sawLabel.setText("saw", dontSendNotification);
    noiseLabel.setText("noise", dontSendNotification);
    oscName.setText("OSCILLATOR", dontSendNotification);
    oscKnob.addListener(this);
    
    // OSC Volume Knob and Labels
    addAndMakeVisible(oscVolumeKnob);
    addAndMakeVisible(oscVolumeLabel);
    oscVolumeKnob.setRange(0, 1);
    oscVolumeKnob.setValue(0.3);
    oscVolumeKnob.setSliderStyle(Slider::RotaryVerticalDrag);
    oscVolumeKnob.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    oscVolumeKnob.addListener(this);
    
    oscVolumeLabel.setText("Volume", dontSendNotification);
    oscVolumeLabel.attachToComponent(&oscVolumeKnob, false);
    
    // Modulation Selection Knob and Labels;
    addAndMakeVisible(modSelectionKnob);
    addAndMakeVisible(modOffLabel);
    addAndMakeVisible(AMLabel);
    addAndMakeVisible(FMLabel);
    addAndMakeVisible(modSelectionLabel);
    modSelectionKnob.setRange(0, 2, 1);
    modSelectionKnob.setSliderStyle(Slider::Rotary);
    modSelectionKnob.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    modSelectionKnob.addListener(this);
    modOffLabel.setText("off", dontSendNotification);
    AMLabel.setText("AM", dontSendNotification);
    FMLabel.setText("FM", dontSendNotification);
    modSelectionLabel.setText("MOD SELECT", dontSendNotification);
    
    
    // Modulation LFO Knob and Labels
    addAndMakeVisible(modKnob);
    addAndMakeVisible(modLabel);
    
    modKnob.setRange(0.01, 5000);
    modKnob.setValue(0.0);
    modKnob.setSliderStyle(Slider::Rotary);
    modKnob.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    modKnob.addListener(this);
    modLabel.setText("Mod Freq", dontSendNotification);
    modLabel.attachToComponent(&modKnob, false);
    
    // Modulation Index Knob and Labels
    addAndMakeVisible(modIndexKnob);
    addAndMakeVisible(modIndexLabel);
    modIndexKnob.setSliderStyle(Slider::Rotary);
    modIndexKnob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    modIndexKnob.addListener(this);
    modIndexLabel.setText("Index", dontSendNotification);
    modIndexLabel.attachToComponent(&modIndexKnob, false);
    // BELOW: by default. AM has different settings
    modIndexKnob.setValue(1.0);
    
    // Carrier ADSR Knobs and Labels
    addAndMakeVisible(c_A_Knob);
    addAndMakeVisible(c_D_Knob);
    addAndMakeVisible(c_S_Knob);
    addAndMakeVisible(c_R_Knob);
    addAndMakeVisible(cNameLabel);
    c_A_Knob.setSliderStyle(Slider::Rotary);
    c_D_Knob.setSliderStyle(Slider::Rotary);
    c_S_Knob.setSliderStyle(Slider::Rotary);
    c_R_Knob.setSliderStyle(Slider::Rotary);
    c_A_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    c_D_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    c_S_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    c_R_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    c_A_Knob.setRange (1, 1000, 1);
    c_D_Knob.setRange (1, 5000, 1);
    c_S_Knob.setRange (0, 1);
    c_R_Knob.setRange (1, 5000, 1);
    c_A_Knob.setValue(50);
    c_D_Knob.setValue(50);
    c_S_Knob.setValue(0.8);
    c_R_Knob.setValue(50);
    c_A_Knob.addListener(this);
    c_D_Knob.addListener(this);
    c_S_Knob.addListener(this);
    c_R_Knob.addListener(this);
    
    c_A_Label.setText("A (ms)", dontSendNotification);
    c_D_Label.setText("D (ms)", dontSendNotification);
    c_S_Label.setText("S (level)", dontSendNotification);
    c_R_Label.setText("R (ms)", dontSendNotification);
    cNameLabel.setText("CARRIER ADSR", dontSendNotification);
    c_A_Label.attachToComponent(&c_A_Knob, false);
    c_D_Label.attachToComponent(&c_D_Knob, false);
    c_S_Label.attachToComponent(&c_S_Knob, false);
    c_R_Label.attachToComponent(&c_R_Knob, false);
    
    
    // Carrier ADSR Knobs and Labels
    addAndMakeVisible(m_A_Knob);
    addAndMakeVisible(m_D_Knob);
    addAndMakeVisible(m_S_Knob);
    addAndMakeVisible(m_R_Knob);
    addAndMakeVisible(mNameLabel);
    m_A_Knob.setSliderStyle(Slider::Rotary);
    m_D_Knob.setSliderStyle(Slider::Rotary);
    m_S_Knob.setSliderStyle(Slider::Rotary);
    m_R_Knob.setSliderStyle(Slider::Rotary);
    m_A_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    m_D_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    m_S_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    m_R_Knob.setTextBoxStyle(Slider::NoTextBox, false, 40, 20);
    m_A_Knob.setRange (1, 1000, 1);
    m_D_Knob.setRange (1, 5000, 1);
    m_S_Knob.setRange (0, 1);
    m_R_Knob.setRange (1, 5000, 1);
    m_D_Knob.setSkewFactorFromMidPoint(1000);
    m_R_Knob.setSkewFactorFromMidPoint(1000);
    m_A_Knob.setValue(50);
    m_D_Knob.setValue(10);
    m_S_Knob.setValue(0.8);
    m_R_Knob.setValue(50);
    m_A_Knob.addListener(this);
    m_D_Knob.addListener(this);
    m_S_Knob.addListener(this);
    m_R_Knob.addListener(this);
    
    m_A_Label.setText("A (ms)", dontSendNotification);
    m_D_Label.setText("D (ms)", dontSendNotification);
    m_S_Label.setText("S (level)", dontSendNotification);
    m_R_Label.setText("R (ms)", dontSendNotification);
    mNameLabel.setText("MOD ADSR", dontSendNotification);
    m_A_Label.attachToComponent(&m_A_Knob, false);
    m_D_Label.attachToComponent(&m_D_Knob, false);
    m_S_Label.attachToComponent(&m_S_Knob, false);
    m_R_Label.attachToComponent(&m_R_Knob, false);
    
    // Drop Down Menu
    addAndMakeVisible(dropDown);
    addAndMakeVisible(dropDownLabel);
    dropDown.addItemList({"Bell","Brass","Clarinet", "Police"}, 1);
    dropDown.addListener(this);
    dropDownLabel.setText("Presets", dontSendNotification);
    dropDownLabel.attachToComponent(&dropDown, false);
    
    
}

PolyPlugAudioProcessorEditor::~PolyPlugAudioProcessorEditor()
{
}



//==============================================================================
void PolyPlugAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

}

/********************* RESIZED *****************/
void PolyPlugAudioProcessorEditor::resized()
{
    const int labelColumnWidth = 80;
    const int componentsHeight = 20;
    const int toTop = 40;
    
    oscKnob.setBounds(labelColumnWidth, toTop, componentsHeight*3, componentsHeight*3);
    sineLabel.setBounds(labelColumnWidth-25,toTop+35,componentsHeight*3,componentsHeight);
    sqrLabel.setBounds(labelColumnWidth-25,toTop-5,componentsHeight*3,componentsHeight);
    sawLabel.setBounds(labelColumnWidth+55,toTop-5,componentsHeight*3,componentsHeight);
    noiseLabel.setBounds(labelColumnWidth+55,toTop+35,componentsHeight*3,componentsHeight);
    oscName.setBounds(labelColumnWidth-componentsHeight+5, toTop-componentsHeight*1.5, componentsHeight*5, componentsHeight);
    
    oscVolumeKnob.setBounds(labelColumnWidth+200, toTop, componentsHeight*3, componentsHeight*3);
    frequencySlider.setBounds (labelColumnWidth+100, toTop, componentsHeight*3, componentsHeight*3);
    modKnob.setBounds(labelColumnWidth+100, toTop+100, componentsHeight*3, componentsHeight*3);
    
    modSelectionKnob.setBounds(labelColumnWidth, toTop+100, componentsHeight*3, componentsHeight*3);
    modOffLabel.setBounds(labelColumnWidth-25,toTop+135,componentsHeight*3,componentsHeight);
    AMLabel.setBounds(labelColumnWidth+15,toTop+85,componentsHeight*3,componentsHeight);
    FMLabel.setBounds(labelColumnWidth+55,toTop+135,componentsHeight*3,componentsHeight);
    modSelectionLabel.setBounds(labelColumnWidth-componentsHeight+5, toTop+65, componentsHeight*5, componentsHeight);
    
    modIndexKnob.setBounds(labelColumnWidth+200, toTop+100, componentsHeight*3, componentsHeight*3);
    
    
    // Carrier ADSR drawing
    c_A_Knob.setBounds(labelColumnWidth+400, toTop, componentsHeight*3, componentsHeight*3);
    c_D_Knob.setBounds(labelColumnWidth+500, toTop, componentsHeight*3, componentsHeight*3);
    c_S_Knob.setBounds(labelColumnWidth+600, toTop, componentsHeight*3, componentsHeight*3);
    c_R_Knob.setBounds(labelColumnWidth+700, toTop, componentsHeight*3, componentsHeight*3);
    cNameLabel.setBounds(labelColumnWidth+300, toTop+10, componentsHeight*5, componentsHeight);
    
    // Mod ADSR drawing
    m_A_Knob.setBounds(labelColumnWidth+400, toTop+100, componentsHeight*3, componentsHeight*3);
    m_D_Knob.setBounds(labelColumnWidth+500, toTop+100, componentsHeight*3, componentsHeight*3);
    m_S_Knob.setBounds(labelColumnWidth+600, toTop+100, componentsHeight*3, componentsHeight*3);
    m_R_Knob.setBounds(labelColumnWidth+700, toTop+100, componentsHeight*3, componentsHeight*3);
    mNameLabel.setBounds(labelColumnWidth+300, toTop+110, componentsHeight*5, componentsHeight);
    
    // DropDown Menu
    dropDown.setBounds(labelColumnWidth+800, toTop, componentsHeight*5, componentsHeight);
    
    // MIDI Selection Dropdown
    
}


/********************* Slider Value Changed *****************/
void PolyPlugAudioProcessorEditor:: sliderValueChanged (Slider* slider)
{
    if (slider == &frequencySlider)
    {
        if (processor.currentSampleRate > 0.0){
            processor.oscFreq = frequencySlider.getValue();
        }
    }
    if (slider == &oscVolumeKnob)
    {
        if (processor.currentSampleRate > 0.0){
            processor.gain = oscVolumeKnob.getValue();
        }
    }
    if (slider == &modKnob) { //change mod frequency
        if (processor.currentSampleRate > 0.0)
            processor.mod = modKnob.getValue();
    }
    if (slider == &modIndexKnob) {
        if (processor.currentSampleRate > 0.0)
            processor.modIndex = modIndexKnob.getValue();
    }
    if (slider == &oscKnob) {
        processor.oscSelection = int(oscKnob.getValue());
    }
    if (slider == &modSelectionKnob) {
        if (modSelectionKnob.getValue() == 1.0) {
            processor.modSelection = 1;
            modIndexKnob.setValue(0.2);
            modIndexKnob.setRange(0,1);
        }
        else if (modSelectionKnob.getValue() == 2.0) {
            processor.modSelection = 2;
            modIndexKnob.setRange(0,2000);
            modIndexKnob.setSkewFactorFromMidPoint(200);
        }
        else {
            processor.modSelection = 0;
        }
    }
    
    //Carrier ADSR Set Up
    if (slider == &c_A_Knob)
        processor.c_A = c_A_Knob.getValue()/1000;
    else if (slider == &c_D_Knob)
        processor.c_D= c_D_Knob.getValue()/1000;
    else if (slider == &c_S_Knob)
        processor.c_S = c_S_Knob.getValue();
    else if (slider == &c_R_Knob)
        processor.c_R = c_R_Knob.getValue()/1000;
    
    //Mod ADSR Set Up
    else if (slider == &m_A_Knob)
        processor.m_A = m_A_Knob.getValue()/1000;
    else if (slider == &m_D_Knob)
        processor.m_D = m_D_Knob.getValue()/1000;
    else if (slider == &m_S_Knob)
        processor.m_S = m_S_Knob.getValue();
    else if (slider == &m_R_Knob)
        processor.m_R = m_R_Knob.getValue()/1000;
    else {}
    
    // Apply Slider values to actual synth parameters
    for (int i = processor.numVoices; --i >= 0;) {
        processor.modifyVoiceParameters((SynthVoice*)processor.synth.getVoice(i));
    }
}

void PolyPlugAudioProcessorEditor:: comboBoxChanged (ComboBox* box) // PRESETS
{
    if (box == & dropDown) {
        switch (dropDown.getSelectedId()) {
            case 1: processor.presetNum = 1; loadPresets(1); break;
            case 2: processor.presetNum = 2; loadPresets(2);break;
            case 3: processor.presetNum = 3; loadPresets(3);break;
            case 4: processor.presetNum = 4; loadPresets(4);break;
            default: std::cout<<"Default Case"; break;
        }
    }
}

//========================== Presets Related =====================/
void PolyPlugAudioProcessorEditor:: loadPresets(int p) {
    if (p == 1) {
        oscKnob.setValue(0.0); processor.oscSelection = oscKnob.getValue();
        modSelectionKnob.setValue(2.0); processor.modSelection = 2;
        modKnob.setValue(processor.oscFreq*1.4); processor.mod = modKnob.getValue();
        modIndexKnob.setValue(800.0);
        processor.modIndex = modIndexKnob.getValue();
        
        c_A_Knob.setValue(1.0); processor.c_A = c_A_Knob.getValue();
        c_D_Knob.setValue(2000.0); processor.c_D = c_D_Knob.getValue();
        c_S_Knob.setValue(0.0); processor.c_S = c_S_Knob.getValue();
        c_R_Knob.setValue(1000.0); processor.c_R = c_R_Knob.getValue();
        m_A_Knob.setValue(5.0); processor.m_A = m_A_Knob.getValue();
        m_D_Knob.setValue(1.0); processor.m_D = m_D_Knob.getValue();
        m_S_Knob.setValue(1.0); processor.m_S = m_S_Knob.getValue();
        m_R_Knob.setValue(1.0); processor.m_R = m_R_Knob.getValue();
        
    }
    if (p == 2) {
        oscKnob.setValue(0.0); processor.oscSelection = oscKnob.getValue();
        modSelectionKnob.setValue(2.0); processor.modSelection = 2;
        modKnob.setValue(processor.oscFreq); processor.mod = modKnob.getValue();
        modIndexKnob.setValue(1000.0);
        processor.modIndex = modIndexKnob.getValue();
        
        c_A_Knob.setValue(50); processor.c_A = c_A_Knob.getValue();
        c_D_Knob.setValue(200.0); processor.c_D = c_D_Knob.getValue();
        c_S_Knob.setValue(0.45); processor.c_S = c_S_Knob.getValue();
        c_R_Knob.setValue(400.0); processor.c_R = c_R_Knob.getValue();
        m_A_Knob.setValue(150); processor.m_A = m_A_Knob.getValue();
        m_D_Knob.setValue(200); processor.m_D = m_D_Knob.getValue();
        m_S_Knob.setValue(0.85); processor.m_S = m_S_Knob.getValue();
        m_R_Knob.setValue(200.0); processor.m_R = m_R_Knob.getValue();
    }
    if (p == 3) {
        oscKnob.setValue(0.0); processor.oscSelection = oscKnob.getValue();
        modSelectionKnob.setValue(2.0); processor.modSelection = 2;
        modKnob.setValue(processor.oscFreq*2/3); processor.mod = modKnob.getValue();
        modIndexKnob.setValue(1500.0);
        processor.modIndex = modIndexKnob.getValue();
        
        c_A_Knob.setValue(40); processor.c_A = c_A_Knob.getValue();
        c_D_Knob.setValue(800.0);processor.c_D = c_D_Knob.getValue();
        c_S_Knob.setValue(0.1); processor.c_S = c_S_Knob.getValue();
        c_R_Knob.setValue(10.0); processor.c_R = c_R_Knob.getValue();
        m_A_Knob.setValue(40); processor.m_A = m_A_Knob.getValue();
        m_D_Knob.setValue(900); processor.m_D = m_D_Knob.getValue();
        m_S_Knob.setValue(0); processor.m_S = m_S_Knob.getValue();
        m_R_Knob.setValue(10); processor.m_R = m_R_Knob.getValue();
    }
    if (p == 4) {
        oscKnob.setValue(0.0); processor.oscSelection = oscKnob.getValue();
        modSelectionKnob.setValue(2.0); processor.modSelection = 2;
        modKnob.setValue(3); processor.mod = modKnob.getValue();
        modIndexKnob.setValue(650);
        processor.modIndex = modIndexKnob.getValue();
        
        c_A_Knob.setValue(20); processor.c_A = c_A_Knob.getValue();
        c_D_Knob.setValue(1.0); processor.c_D = c_D_Knob.getValue();
        c_S_Knob.setValue(1.0); processor.c_S = c_S_Knob.getValue();
        c_R_Knob.setValue(20.0); processor.c_R = c_R_Knob.getValue();
        m_A_Knob.setValue(20); processor.m_A = m_A_Knob.getValue();
        m_D_Knob.setValue(1); processor.m_D = m_D_Knob.getValue();
        m_S_Knob.setValue(1.0); processor.m_S = m_S_Knob.getValue();
        m_R_Knob.setValue(20); processor.m_R = m_R_Knob.getValue();
    }
    // apply updates to voices
    for (int i = processor.numVoices; --i >= 0;) {
        processor.modifyVoiceParameters((SynthVoice*)processor.synth.getVoice(i));
    }
}
