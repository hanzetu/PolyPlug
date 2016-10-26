/*
  ==============================================================================

    SynthVoice.h
    Created: 22 Oct 2016 5:30:49pm
    Author:  Hanze Tu

  ==============================================================================
*/
#ifndef SYNTH_H_INCLUDED
#define SYNTH_H_INCLUDED

#include "stk/SineWave.h" // STK sine osc
#include "stk/BlitSaw.h" // STK sawtooth osc
#include "stk/BlitSquare.h" // STK square osc
#include "stk/ADSR.h"
#include <math.h>
#include "Smooth.h"

#include "PluginProcessor.h"

#define numSmooth 5


using namespace stk;

class SynthSound : public SynthesiserSound
{
public:
    SynthSound() {}

    bool appliesToNote (int /*midiNoteNumber*/) override        { return true; }
    bool appliesToChannel (int /*midiChannel*/) override        { return true; }
};

class SynthVoice : public SynthesiserVoice
{
public:

    //*********** Synth Components **********/
    ADSR carrierADSR, modADSR;
    
    SineWave sine, mod; // sine osc
    BlitSaw saw; // sawtooth osc
    BlitSquare square;
    Random random;
    float level;
    int presetNum = 0;

    int oscSelection = 0; // Sine, Square, Saw, NOISE // 0,1,2,3
    int modSelection = 0; // No, AM, FM // 0,1,2
    double modIndex, gain;
    
    double c_A, c_D, c_S, c_R;
    double m_A, m_D, m_S, m_R;
    double modFreq;
    
    //********** Synth Functions **********/

    SynthVoice(): level(0), modIndex(0), gain(0),
    c_A(0), c_D(0), c_S(0), c_R(0), m_A(0), m_D(0), m_S(0), m_R(0),
    oscFreq(440.0), modFreq(0.0)
    {}

    
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<SynthSound*> (sound) != nullptr;
    }

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {
        oscFreq = MidiMessage::getMidiNoteInHertz (midiNoteNumber);
        updateModFreq(presetNum);
        
        
        // we don't want an ugly sweep when the note begins...
        for (int i=0; i<numSmooth; i++) {
            smooth[i].setSmooth(0);
        }
        smooth[4].tick(oscFreq);
        smooth[1].tick(modFreq);


    
        for(int i=0; i<numSmooth; i++) {
            smooth[i].setSmooth(0.999);
        }
        
        level = velocity;
        
        carrierADSR.setAllTimes(c_A, c_D, c_S, c_R);
        modADSR.setAllTimes(m_A, m_D, m_S, m_R);

        if(oscSelection == 0)
            sine.setFrequency(oscFreq);
        else if (oscSelection == 1)
            square.setFrequency(oscFreq);
        else if (oscSelection == 2)
            saw.setFrequency(oscFreq);
        else {}
        
        
        carrierADSR.keyOn();
        modADSR.keyOn();
        
        
        //std::cout<< "MODINDEX: "<< modIndex << "\n";
        //std::cout<< "NoteNumber: "<< midiNoteNumber << "Velocity: "<<velocity<<"\n";
        //std::cout<<"Level: "<< level <<" gain: "<< gain<<"\n";
      //  std::cout<<"CarrierADSR: "<<carrierADSR.getState()<<"\n";
      //  std::cout<<"ModADSR: "<<modADSR.getState()<<"\n";
     //   std::cout<<"oscSelection: "<<oscSelection<<" modSelection: "<<modSelection<<"\n";
    //    std::cout<<"carrier ADSR: "<<c_A<<" "<<c_D<<" "<<c_S<<" "<<c_R<<"\n";
    //    std::cout<<"mod ADSR: "<<m_A<<" "<<m_D<<" "<<c_S<<" "<<c_R<<"\n";

    }

    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        modADSR.keyOff();
        carrierADSR.keyOff();
        level = 0.0;
    }

    void pitchWheelMoved (int /*newValue*/) override
    {
        // Pitch wheel is an important standard MIDI feature that should be implemented
    }

    void controllerMoved (int /*controllerNumber*/, int /*newValue*/) override
    {
        // Thats where you would change the value of the modulator index and frequency
        // if you wanted to control them with MIDI controllers
    }

    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        while (--numSamples >= 0){
            
            float currentSample = 0.0;
           // currentSample = sine.tick()*carrierADSR.tick(); //TEST USE
            
            if(oscSelection == 0) {
                if (modSelection == 0) // NO modulation
                    currentSample = sine.tick()*smooth[0].tick(gain*level)*carrierADSR.tick();
                    else if (modSelection == 1) // AM
                        currentSample = (sine.tick()*smooth[0].tick(gain*level)*carrierADSR.tick() * (1 + mod.tick()*smooth[3].tick(modIndex)*modADSR.tick()));
                    else if (modSelection == 2) { // FM
                        sine.setFrequency(oscFreq + mod.tick()*modIndex*modADSR.tick());
                        currentSample = sine.tick()*smooth[0].tick(gain*level)*carrierADSR.tick();
                    }
            }
            else if (oscSelection == 1) {
                if (modSelection == 0) // NO modulation
                    currentSample = square.tick()*smooth[0].tick(gain*level)*carrierADSR.tick();
                    else if (modSelection == 1) // AM
                        currentSample = square.tick()*smooth[0].tick(gain*level)*carrierADSR.tick() * (1 + mod.tick()*smooth[3].tick(modIndex)*modADSR.tick());
                    else if (modSelection == 2) { // FM
                        square.setFrequency(oscFreq + mod.tick()*smooth[3].tick(modIndex)*modADSR.tick());
                        currentSample = square.tick()*smooth[0].tick(gain*level)*carrierADSR.tick();
                    }
            }
            else if(oscSelection == 2) {
                if (modSelection == 0) // NO modulation
                    currentSample = saw.tick()*smooth[0].tick(gain*level)*carrierADSR.tick();
                    else if (modSelection == 1) // AM
                        currentSample = saw.tick()*smooth[0].tick(gain*level)*carrierADSR.tick() * (1 + mod.tick()*smooth[3].tick(modIndex)*modADSR.tick());
                    else if (modSelection == 2) { // FM
                        saw.setFrequency(oscFreq + mod.tick()*smooth[3].tick(modIndex)*modADSR.tick());
                        currentSample = saw.tick()*smooth[0].tick(gain*level)*carrierADSR.tick();
                    }
            }
            
            else if(oscSelection == 3) {
                currentSample = (random.nextFloat()*2-1)*gain*carrierADSR.tick();
            }
            else {}
            
            // Limiter
            if (currentSample >= 1)
                currentSample = 0.99;
            else if (currentSample <=-1)
                currentSample = -0.99;
            
            //std::cout<<"currentsample: "<< currentSample <<"\n";
           // std::cout<<"carrierADSR last samp: "<< carrierADSR.lastOut()<<"\n";
            
            // write to the buffer
            for (int i = outputBuffer.getNumChannels(); --i >= 0;){
                outputBuffer.addSample (i, startSample, currentSample);
            }
            ++startSample;
    
        }
    }
    
    

private:
    double oscFreq;
    Smooth smooth[numSmooth];

    void updateModFreq(int p)
    {
        if (p == 1) {
            // modKnob.setValue(processor.oscFreq*1.4);
            mod.setFrequency(oscFreq*1.4);
        }
        else if (p == 2) {
            //modKnob.setValue(processor.oscFreq);
            mod.setFrequency(oscFreq);
        }
        else if (p == 3) {
            oscFreq *= 1.5;
            //modKnob.setValue(processor.oscFreq*2/3);
            mod.setFrequency(oscFreq*2/3);
        }
        else if (p == 4) {
            oscFreq *= 2;
            //modKnob.setValue(3);
            mod.setFrequency(3.0);
        }
        else
            mod.setFrequency(modFreq);
    }
};



#endif  // SYNTH_H_INCLUDED
