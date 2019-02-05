#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include "driverChoice.h"
#include <EventReceiver.h>

using namespace irr;

	// This is the one method that we have to implement
	EventReceiver::EventReceiver()
	{
		for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

	EventReceiver::EventReceiver(const EventReceiver & p_other)
	{
		for (int i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		{
			KeyIsDown[i] = p_other.KeyIsDown[i];
		}
	}

	bool EventReceiver::OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

		return false;
	}

	// This is used to check whether a key is being held down
	bool EventReceiver::IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}