#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

class EventReceiver : public IEventReceiver
{
public:
	EventReceiver();
	~EventReceiver() = default;
	EventReceiver(const EventReceiver& p_other);

	virtual bool OnEvent(const SEvent& event);

	virtual bool IsKeyDown(EKEY_CODE keyCode) const;

	virtual bool IsMouseDown(int button) const;

private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	bool MouseIsDown[3];
};
