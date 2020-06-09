#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Maximilian.h"

class SynthVoice : public SynthesiserVoice {

public:
	bool canPlaySound(SynthesiserSound* sound) {
		return dynamic_cast<SynthSound*>(sound) != nullptr;
	}
	void getParam(float* triangleAttack, float* triangleRelease, float* triangleThicken,float* triangleLevel,float* triangleDecay,float* triangleSustain,
		float* squareLevel, float* squareThicken, float* squareAttack, float* squareDecay, float* squareSustain, float* squareRelease,
		float* sawLevel, float* sawThicken, float* sawAttack, float* sawDecay, float* sawSustain, float* sawRelease, float* releaseDepth, float* releaseSpeed) {

		TriangleLevel = static_cast<double>(*triangleLevel);
		TriangleDetune = 1 - (static_cast<double>(*triangleThicken) / 100);
		triangleEnvelope.setAttack(static_cast<double>(*triangleAttack));
		triangleEnvelope.setDecay(static_cast<double>(*triangleDecay));
		triangleEnvelope.setSustain(static_cast<double>(*triangleSustain));
		triangleEnvelope.setRelease(static_cast<double>(*triangleRelease));

		SquareLevel = static_cast<double>(*squareLevel);
		SquareDetune = 1 - (static_cast<double>(*squareThicken) / 100);
		squareEnvelope.setAttack(static_cast<double>(*squareAttack));
		squareEnvelope.setDecay(static_cast<double>(*squareDecay));
		squareEnvelope.setSustain(static_cast<double>(*squareSustain));
		squareEnvelope.setRelease(static_cast<double>(*squareRelease));
	
		SawLevel = static_cast<double>(*sawLevel);
		SawDetune = static_cast<double>(*sawThicken);
		sawEnvelope.setAttack(static_cast<double>(*sawAttack));
		sawEnvelope.setDecay(static_cast<double>(*sawDecay));
		sawEnvelope.setSustain(static_cast<double>(*sawSustain));
		sawEnvelope.setRelease(static_cast<double>(*sawRelease));

		ReleaseDepth = static_cast<double>(*releaseDepth);
		releaseFilterEnvelope.setAttack(static_cast<double>(*releaseSpeed));


	}
	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) {
		triangleEnvelope.trigger = 1;
		releaseFilterEnvelope.trigger = 0;

		level = velocity;
		frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	}
	void stopNote(float velocity, bool allowTailOff) {

		triangleEnvelope.trigger = 0;
		releaseFilterEnvelope.trigger = 1;

		if (velocity == 0)  
			clearCurrentNote(); 

	}
	void pitchWheelMoved(int newPitchWheelValue) {}
	void controllerMoved(int controllerNumber, int newControllerValue) {}
	void renderNextBlock(AudioBuffer< float >& outputBuffer, int startSample, int numSamples){
	

		releaseFilterEnvelope.setDecay(30000);
		releaseFilterEnvelope.setSustain(1);
		releaseFilterEnvelope.setRelease(2000);

		for (int sample = 0; sample < numSamples; ++sample) {

			double triangleWave = triangleOSC.triangle(frequency) ;
			double detunedTriangeWave = detunedTriangleOSC.triangle(frequency*TriangleDetune);
			double combinedTriangleWaves = triangleEnvelope.adsr(triangleWave + detunedTriangeWave, triangleEnvelope.trigger) * level * TriangleLevel;

			double squareWave = squareOSC.square(frequency);
			double detunedSquareWave = detunedSquareOSC.square(frequency * SquareDetune);
			double combinedSquareWaves = squareEnvelope.adsr(squareWave + detunedSquareWave, triangleEnvelope.trigger) * level * SquareLevel;

			double sawWave = sawOSC.saw(frequency);
			double superSaw = (detunedSawOSC1.saw(frequency*1.001) + detunedSawOSC2.saw(frequency * 1.005) + detunedSawOSC3.saw(frequency * 1.009) + detunedSawOSC4.saw(frequency * 0.996) +
				detunedSawOSC5.saw(frequency * 0.993) + detunedSawOSC5.saw(frequency * 0.998))*SawDetune;
			double combinedSawWaves = sawEnvelope.adsr(sawWave + superSaw, triangleEnvelope.trigger) * level * SawLevel;
			  

			double filterSweep = releaseFilterEnvelope.adsr(ReleaseDepth, releaseFilterEnvelope.trigger);
			double filteredSignal = gloabalFilter.lores(combinedTriangleWaves + combinedSquareWaves + combinedSawWaves, 10000-filterSweep, 5);

			double distortedSignal = gloabalDistorter.fastAtanDist(filteredSignal, 5) /**(1+LFO.sinewave(5))*/;

			for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
				outputBuffer.addSample(channel, startSample, distortedSignal );

			}
			++startSample;
		}
	
	}

private:
	double level;
	double frequency;
	int releaseCutOffFrequency;
	float TriangleDetune;
	float TriangleLevel;
	float SquareDetune;
	float SquareLevel;
	float SawDetune;
	float SawLevel;
	float ReleaseDepth;

	maxiOsc triangleOSC; 
	maxiOsc squareOSC;
	maxiOsc detunedTriangleOSC;
	maxiOsc detunedSquareOSC;
	maxiOsc sawOSC;
	maxiOsc detunedSawOSC1;
	maxiOsc detunedSawOSC2;
	maxiOsc detunedSawOSC3;
	maxiOsc detunedSawOSC4;
	maxiOsc detunedSawOSC5;
	maxiOsc detunedSawOSC6;
	maxiOsc LFO;
	maxiEnv triangleEnvelope;
	maxiEnv squareEnvelope;
	maxiEnv sawEnvelope;
	maxiEnv releaseFilterEnvelope;
	maxiFilter gloabalFilter;
	maxiDistortion gloabalDistorter;

};


