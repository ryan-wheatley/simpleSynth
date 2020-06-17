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
		float* sawLevel, float* sawThicken, float* sawAttack, float* sawDecay, float* sawSustain, float* sawRelease, float* releaseDepth, float* releaseSpeed,
		float* globalCutoff, float* globalResonance, float* gateDepth, float* gateSpeed, float* volume, float* trianglePan, float* squarePan, float* sawPan) {

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

		GlobalCutoff = static_cast<float>(*globalCutoff);
		GlobalResonance = static_cast<double>(*globalResonance);

		GateDepth = static_cast<float>(*gateDepth);
		GateSpeed = static_cast<float>(*gateSpeed);

		TrianglePan = static_cast<double>(*trianglePan)*-1.0;
		SquarePan = static_cast<double>(*squarePan) * -1.0;
		SawPan = static_cast<double>(*sawPan) * -1.0;

		Volume = static_cast<float>(*volume);

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
			double combinedTriangleWaves = triangleEnvelope.adsr(triangleWave + detunedTriangeWave, triangleEnvelope.trigger) * level * TriangleLevel*0.5;

			double squareWave = squareOSC.square(frequency);
			double detunedSquareWave = detunedSquareOSC.square(frequency * SquareDetune);
			double combinedSquareWaves = squareEnvelope.adsr(squareWave + detunedSquareWave, triangleEnvelope.trigger) * level * SquareLevel*0.5;

			double sawWave = sawOSC.saw(frequency);
			double superSaw = (detunedSawOSC1.saw(frequency*1.001) + detunedSawOSC2.saw(frequency * 1.005) 
							+ detunedSawOSC3.saw(frequency * 1.009) + detunedSawOSC4.saw(frequency * 0.996) 
							+ detunedSawOSC5.saw(frequency * 0.993) + detunedSawOSC5.saw(frequency * 0.998))*SawDetune;
			double combinedSawWaves = sawEnvelope.adsr(sawWave + superSaw, triangleEnvelope.trigger) * level * SawLevel * 0.5;
			  
			double filterSweep = releaseFilterEnvelope.adsr(ReleaseDepth, releaseFilterEnvelope.trigger);

			double filteredTriangel = TriangleFilter.lores(combinedTriangleWaves, GlobalCutoff - filterSweep, GlobalResonance);
			double filteredSquare = SquareFilter.lores(combinedSquareWaves , GlobalCutoff - filterSweep, GlobalResonance);
			double filteredSaw = SawFilter.lores(combinedSawWaves, GlobalCutoff - filterSweep, GlobalResonance);


			double gatedTriange = TriangleDistorter.fastAtanDist(filteredTriangel, 7) *0.5* (1-((1+LFO.sinewave(GateSpeed)))*GateDepth)*Volume;
			double gatedSquare = SquareDistorter.fastAtanDist(filteredSquare, 5) * 0.5 * (1 - ((1 + LFO.sinewave(GateSpeed))) * GateDepth) * Volume;
			double gatedSaw = SawDistorter.fastAtanDist(filteredSaw, 5) * 0.5 * (1 - ((1 + LFO.sinewave(GateSpeed))) * GateDepth) * Volume;

			for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
				double trianglePan;
				double squarePan;
				double sawPan;
				if (channel == 1)
				{
					trianglePan = 1 - (TrianglePan + .5);
					squarePan = 1 - SquarePan;
					sawPan = 1 - SawPan;
				}
				else if (channel == 0) {
					trianglePan =  TrianglePan + 0.5;
					squarePan = SquarePan + 0.5;
					sawPan = SawPan + 0.5;
				}
				
				outputBuffer.addSample(channel, startSample, gatedTriange*(trianglePan) );
				outputBuffer.addSample(channel, startSample, gatedSquare * (squarePan));
				outputBuffer.addSample(channel, startSample, gatedSaw * (sawPan));

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
	float GlobalCutoff;
	float GlobalResonance;
	float GateDepth;
	float GateSpeed;
	float Volume;

	float TrianglePan;
	double SquarePan;
	double SawPan;

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
	
	maxiFilter TriangleFilter;
	maxiFilter SquareFilter;
	maxiFilter SawFilter;

	maxiDistortion TriangleDistorter;
	maxiDistortion SquareDistorter;
	maxiDistortion SawDistorter;
};


