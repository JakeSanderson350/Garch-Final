#pragma once

#include <Event.h>

enum InterfaceEventType
{
	KEYPRESS_TYPE = NUM_BASE_EVENT_TYPES,
	MOUSE_MOVE_TYPE,
	NUM_INTERFACE_EVENT_TYPES
};

class InterfaceEvent :public Event
{

};