#include "MidiDevice.hpp"


// Define supported devices here

static std::array<int, MidiDevice::KeyCount> inputMappingNanoKontrol2 =
{
	// Special keys
	58, 59, 46, 60, 61, 62, 43, 44, 42, 41, 45,
	// Sliders
	0,  1,  2,  3,  4,  5,  6,  7,
	// Knobs
	16, 17, 18, 19, 20, 21, 22, 23,
	// S keys
	32, 33, 34, 35, 36, 37, 38, 39,
	// M keys
	48, 49, 50, 51, 52, 53, 54, 55,
	// R keys
	64, 65, 66, 67, 68, 69, 70, 71
};


std::vector<MidiDevice> MidiDevice::SupportedDevices = 
{
	MidiDevice({ "nanoKONTROL2 0", MidiDevice::Type::NanoKONTROL2, inputMappingNanoKontrol2 })
};