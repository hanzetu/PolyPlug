/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Synth.h"

//==============================================================================
PolyPlugAudioProcessor::PolyPlugAudioProcessor():
    currentSampleRate (0.0),
    gain(0.5),
    oscFreq(0.0),
    c_A(0.05), c_D(0.05), c_S(0.8), c_R(0.05),      // in seconds
    m_A(0.05), m_D(0.05), m_S(0.8), m_R(0.05),       // in seconds
    lastUIWidth(1020), lastUIHeight(230)
{
    initializeSynth();
    
}

PolyPlugAudioProcessor::~PolyPlugAudioProcessor()
{
}

//==============================================================================
const String PolyPlugAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PolyPlugAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PolyPlugAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double PolyPlugAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PolyPlugAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PolyPlugAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PolyPlugAudioProcessor::setCurrentProgram (int index)
{
}

const String PolyPlugAudioProcessor::getProgramName (int index)
{
    return String();
}

void PolyPlugAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PolyPlugAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    currentSampleRate = sampleRate;
    Stk::setSampleRate(sampleRate); // STK must know the sampling rate
    synth.setCurrentPlaybackSampleRate(sampleRate);
    keyboardState.reset();
    
    for (int i = numVoices; --i >= 0;) {
        modifyVoiceParameters((SynthVoice*)synth.getVoice(i));
    }
    
    reset();
    
}

void PolyPlugAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    keyboardState.reset();
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PolyPlugAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif


/*************************** Process Block ************************************/
void PolyPlugAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    const int numSamples = buffer.getNumSamples();
    //std::cout<<totalNumInputChannels<<" "<<totalNumOutputChannels<< " "<<numSamples<<"\n";
    
    keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);
    synth.renderNextBlock (buffer, midiMessages, 0, numSamples);
//    for (int i = 0; i < numSamples; i++) {
//        std::cout<< "sample: " << buffer.getSample(0, i)<<"\n";
//    }

    
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i) {
        buffer.clear (i, 0, numSamples);
    }
}

//==============================================================================
bool PolyPlugAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PolyPlugAudioProcessor::createEditor()
{
    return new PolyPlugAudioProcessorEditor (*this);
}

//==============================================================================
void PolyPlugAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    XmlElement xml ("MYPLUGINSETTINGS");
    
    // add some attributes to it
    xml.setAttribute ("uiWidth", lastUIWidth);
    xml.setAttribute ("uiHeight", lastUIHeight);
    
    // Store the values of all our parameters, using their param ID as the XML attribute
    for (int i = 0; i < getNumParameters(); ++i){
        if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
            xml.setAttribute (p->paramID, p->getValue());
    }
    
    copyXmlToBinary (xml, destData);
}

void PolyPlugAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        // make sure that it's actually our type of XML object..
        if (xmlState->hasTagName ("MYPLUGINSETTINGS"))
        {
            // ok, now pull out our last window size..
            lastUIWidth  = jmax (xmlState->getIntAttribute ("uiWidth", lastUIWidth), 800);
            lastUIHeight = jmax (xmlState->getIntAttribute ("uiHeight", lastUIHeight), 400);
            
            // Now reload our parameters..
            for (int i = 0; i < getNumParameters(); ++i)
                if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
                    p->setValueNotifyingHost ((float) xmlState->getDoubleAttribute (p->paramID, p->getValue()));
        }
    }
}
    


//================================= Initialize Synth ==============================//
void PolyPlugAudioProcessor::initializeSynth()
{    
    // Add some voices...
    for (int i = numVoices; --i >= 0;) {
        synth.addVoice (new SynthVoice());
    }
    
   // synth.clearSounds();
    
    // ..and give the synth a sound to play
    synth.addSound (new SynthSound());
}

//========================= Update one voice ===================//
void PolyPlugAudioProcessor::modifyVoiceParameters(SynthVoice* voice)
{
    voice->c_A = c_A; voice->c_D = c_D; voice->c_S = c_S; voice->c_R = c_R;
    voice->m_A = m_A; voice->m_D = m_D; voice->m_S = m_S; voice->m_R = m_R;

    voice->oscSelection = oscSelection;
    voice->modSelection = modSelection;
    voice->modFreq = mod;
    voice->modIndex = modIndex;
    voice->gain = gain;
    voice->presetNum = presetNum;
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PolyPlugAudioProcessor();
}
