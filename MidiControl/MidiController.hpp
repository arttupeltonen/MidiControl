#pragma once

#include <string>
#include <array>
#include <unordered_map>

#include "MidiDevice.hpp"

#include "../rtmidi-2.1.0/RtMidi.h"

// Required: #pragma comment(lib, "winmm.lib")
// Required: #define __WINDOWS_MM__

class MidiController
{
public:

	enum class Status
	{
		Uninitialized,
		Ready,
		Error
	};

	struct InputEvent
	{
		MidiDevice::Key		keyCode;
		float				value;
	};

	MidiController(unsigned messageQueueSize = 256);
	~MidiController();

	double			poll(std::vector<unsigned char> &msg);

	Status			status();
	std::string	errorString();

private:

	RtMidiIn*		m_midiIn; // TODO: no pointer
	std::string		m_errorString;
	Status			m_status;
	std::unordered_map<unsigned, std::string> m_ports;
};
