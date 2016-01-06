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

	// Periodically check input queue.
	double stamp;
	bool done = false;
	std::vector<unsigned char> message;
	int nBytes, i;

	while (!done)
	{
		stamp = device.poll(message);
		nBytes = static_cast<int>(message.size());

		for (i = 0; i < nBytes; i++)
			std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
		if (nBytes > 0)
			std::cout << "stamp = " << stamp << std::endl;

		Sleep(1);
	}

	return 0;
}