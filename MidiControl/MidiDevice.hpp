#pragma once

#include <string>
#include <unordered_map>
#include <array>
#include <vector>

struct MidiDevice
{	
	enum class Type
	{
		NanoKONTROL,
		NanoKONTROL2,
	};

	enum class Key
	{
		TrackLeft = 0,
		TrackRight,
		Cycle,
		MarkerSet,
		MarkerLeft,
		MarkerRight,
		Rewind,
		Forward,
		Stop,
		Play,
		Record,

		Slider1,
		Slider2,
		Slider3,
		Slider4,
		Slider5,
		Slider6,
		Slider7,
		Slider8,

		Knob1,
		Knob2,
		Knob3,
		Knob4,
		Knob5,
		Knob6,
		Knob7,
		Knob8,

		ButtonS1,
		ButtonS2,
		ButtonS3,
		ButtonS4,
		ButtonS5,
		ButtonS6,
		ButtonS7,
		ButtonS8,

		ButtonM1,
		ButtonM2,
		ButtonM3,
		ButtonM4,
		ButtonM5,
		ButtonM6,
		ButtonM7,
		ButtonM8,

		ButtonR1,
		ButtonR2,
		ButtonR3,
		ButtonR4,
		ButtonR5,
		ButtonR6,
		ButtonR7,
		ButtonR8,

		Count
	};

	static const unsigned KeyCount = static_cast<unsigned>(Key::Count);
	static std::vector<MidiDevice> SupportedDevices;
	
	MidiDevice()
	{
	}

	MidiDevice(std::string name, Type type, std::array<int, KeyCount> keys)
		: name(name)
		, type(type)
	{
		for (int i = 0; i < static_cast<int>(keys.size()); i++)
		{
			int key = keys[i];
			keyMapping[key] = i;
		}
	}
	
	std::string							name;
	Type								type;
	std::unordered_map<int, int>		keyMapping;
};




