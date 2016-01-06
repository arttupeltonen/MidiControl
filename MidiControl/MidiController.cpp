#include "MidiController.hpp"

#include <sstream>

#define LYNX_PLATFORM_WIN32

#ifdef LYNX_PLATFORM_WIN32
static const RtMidi::Api s_platform = RtMidi::WINDOWS_MM;
#else
static const RtMidi::Api s_platform = RtMidi::RTMIDI_DUMMY;
#endif

MidiController::MidiController(unsigned messageQueueSize)
	: m_midiIn(nullptr)
	, m_errorString("")
	, m_status(Status::Uninitialized)
	, m_activeDevice()
{
	try 
	{
		m_midiIn = std::make_unique<RtMidiIn>(RtMidi::UNSPECIFIED, "RtMidiClient", messageQueueSize);

		std::vector<RtMidi::Api> apis;
		m_midiIn->getCompiledApi(apis);
	
		bool foundCompatibleApi = false;
		for (auto &api : apis)
		{
			if (api == s_platform)
			{
				foundCompatibleApi = true;
				break;
			}
		}

		if (!foundCompatibleApi)
		{
			m_status = Status::Error;
			std::ostringstream ss;
			ss << "Error: No compatible API found (total " << apis.size() << " found)";
			m_errorString = ss.str();
		}

		unsigned numPorts = m_midiIn->getPortCount();	
		for (unsigned i = 0; i < numPorts; i++)
		{
			std::string portName = m_midiIn->getPortName(i);
			m_ports[i] = portName;
		}
	
		if (m_status != Status::Error)
		{
			bool foundSupportedPort = false;
			for (auto &port : m_ports)
			{
				const std::string &portName = port.second;
				for (auto &device : MidiDevice::SupportedDevices)
				{
					if (portName.compare(device.name) == 0)
					{
						foundSupportedPort = true;
						m_midiIn->openPort(port.first);		
						m_activeDevice = device;
						break;
					}
				}
			}

			if (foundSupportedPort)
			{			
				// Don't ignore sysex, timing, or active sensing messages.
				m_midiIn->ignoreTypes(false, false, false);

				m_status = Status::Ready;
			}
			else
			{			
				m_status = Status::Error;
				m_errorString = "Error: Could not find a supported device";
			}
		}
	}
	catch (RtMidiError &error) 
	{
		m_status = Status::Error;
		m_errorString = error.getMessage();
	}
}

MidiController::~MidiController()
{
	m_midiIn->closePort();
}

double MidiController::poll(std::vector<unsigned char> &msg)
{
	return m_midiIn->getMessage(&msg);
}

bool MidiController::poll(MidiController::InputEvent &e)
{
	std::vector<unsigned char> message;
	m_midiIn->getMessage(&message);

	unsigned messageSize = static_cast<unsigned>(message.size());
	
	if (messageSize == 0)
	{
		return false;
	}

	//LYNX_ASSERT(messageSize == 3);

	int key		  = static_cast<int>(message[1]);
	int rawValue  = static_cast<int>(message[2]);
	static const float conversion = (1.f + 1.f/127.f) / 128.f;

	if (m_activeDevice.keyMapping.count(key) == 0)
	{
		//LYNX_ASSERT(false, "Error in key mapping!");
		return false;
	}

	e.keyCode = static_cast<MidiDevice::Key>(m_activeDevice.keyMapping[key]);
	e.value	  = static_cast<float>(rawValue * conversion);	
	
	return true;
}

MidiController::Status MidiController::status()
{
	return m_status;
}

std::string MidiController::errorString()
{
	return m_errorString;
}
