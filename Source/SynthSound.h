#pragma once

#include <JuceHeader.h>

class SynthSound : public SynthesiserSound
{
public:
	bool appliesToNote(int /*midiNoteNumber*/) { return true; }
	bool appliesToChannel(int /*channelNo*/) { return true; }

};