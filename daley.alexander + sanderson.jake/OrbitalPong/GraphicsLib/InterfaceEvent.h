#pragma once

#include <Event.h>

enum InterfaceEventType
{
	KEY_DOWN_EVENT = NUM_BASE_EVENT_TYPES,
	KEY_UP_EVENT,
	MOUSE_INPUT_EVENT,
	MOUSE_INPUT_DOWN_EVENT,
	MOUSE_INPUT_UP_EVENT,
	NUM_INTERFACE_EVENTS
};

class InterfaceEvent : public Event
{
public:
	InterfaceEvent(InterfaceEventType eventType);
	~InterfaceEvent();

private:
};

