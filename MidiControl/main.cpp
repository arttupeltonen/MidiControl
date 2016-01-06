#include "MidiController.hpp"

#include <windows.h>

int main()
{
	MidiController device(256);

	if (device.status() != MidiController::Status::Ready)
	{
		std::string msg = device.errorString();
		std::cout << "Failed to initialize NanoKontrol MIDI device: '" << msg.c_str() << "'";
		std::getchar(); // Wait for input
		return EXIT_FAILURE;
	}
		
	bool done = false;
	while (!done)
	{
		MidiController::InputEvent event;
		bool gotEvent = device.poll(event);

		if (gotEvent)
		{
			std::cout << "Key " << static_cast<int>(event.keyCode) 
					  << " = "  << event.value << std::endl;
		}

		Sleep(1);
	}

	return 0;
}