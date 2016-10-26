/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Synth.h"


#define nChans 2
#define numKeys 12
#define transpose 1

//==============================================================================
/**
*/
class PolyPlugAudioProcessor  : public AudioProcessor
{
public:
    const int numVoices = 10;
    
    double currentSampleRate, gain, mod, oscFreq, modIndex;
    double c_A, c_D, c_S, c_R;
    double m_A, m_D, m_S, m_R;
    int oscSelection = 0, oscOnOff = 0, modSelection = 0;
    int presetNum = 0;
    
    int lastUIWidth, lastUIHeight;
    
    Synthesiser synth;
    
    
    //==============================================================================
    PolyPlugAudioProcessor();
    ~PolyPlugAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;
//    void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override
//    {
//        jassert (! isUsingDoublePrecision());
//        process (buffer, midiMessages);
//    }
//    
//    void processBlock (AudioBuffer<double>& buffer, MidiBuffer& midiMessages) override
//    {
//        jassert (isUsingDoublePrecision());
//        process (buffer, midiMessages);
//    }
    
    
    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
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
    
    // Update synth parameters when UI changes
    void modifyVoiceParameters(SynthVoice* voice);
    
    // In a plugin this is the only useful MIDI stuff
    MidiKeyboardState keyboardState;
    
private:
    
    void initializeSynth();

    template <typename FloatType>
    void process (AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages);



    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolyPlugAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
