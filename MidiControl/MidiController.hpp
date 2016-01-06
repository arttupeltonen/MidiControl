#pragma once

#include <string>
#include <array>
#include <unordered_map>
#include <memory>

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
							
	double					poll(std::vector<unsigned char> &msg);
	bool					poll(InputEvent &e);

	Status					status();
	std::string				errorString();

private:

	std::unique_ptr<RtMidiIn>					m_midiIn;
	std::string									m_errorString;
	Status										m_status;
	MidiDevice									m_activeDevice;
	std::unordered_map<unsigned, std::string>	m_ports;
};
