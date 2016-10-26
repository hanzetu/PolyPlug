/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

#include "stk/SineWave.h" // STK sine osc
#include "stk/BlitSaw.h" // STK sawtooth osc
#include "stk/BlitSquare.h" // STK square osc
#include "stk/ADSR.h"
#include <math.h>
#include "Smooth.h"
using namespace stk;

#define nChans 2
#define numKeys 12
#define transpose 1


//============================= The Editor Class =================================
/**
*/
class PolyPlugAudioProcessorEditor  :
public AudioProcessorEditor,
private Slider::Listener,
private ComboBox::Listener
//private MidiInputCallback

{
public:
    /** Constructor, Destructor**/
    PolyPlugAudioProcessorEditor (PolyPlugAudioProcessor&);
    ~PolyPlugAudioProcessorEditor();

    //** Member Functions **/
    void paint (Graphics&) override;
    void resized() override;
    
    
    

private:
    
    PolyPlugAudioProcessor& processor;
    
    //****** functions: ***********/
    void sliderValueChanged (Slider* slider) override;
    void comboBoxChanged (ComboBox *box) override;

    void loadPresets(int p);
    
    
    //****** Synth Components ********//
    Slider frequencySlider;
    Slider gainSlider, oscKnob, oscVolumeKnob, modSelectionKnob, modKnob, modIndexKnob;
    Slider c_A_Knob, c_D_Knob, c_S_Knob, c_R_Knob; //Carrier
    Slider m_A_Knob, m_D_Knob, m_S_Knob, m_R_Knob; //Modulator
    
    Label frequencyLabel;
    Label gainLabel;
    Label sineLabel, sqrLabel, sawLabel, noiseLabel;
    Label oscName, oscVolumeLabel, modLabel, modSelectionLabel, modIndexLabel, modOffLabel, AMLabel, FMLabel;
    Label c_A_Label, c_D_Label, c_S_Label, c_R_Label, cNameLabel;
    Label m_A_Label, m_D_Label, m_S_Label, m_R_Label, mNameLabel;
    Label dropDownLabel;
    
    ComboBox dropDown;
    
    

    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolyPlugAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
