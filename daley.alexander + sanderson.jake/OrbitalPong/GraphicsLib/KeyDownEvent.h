#pragma once
#include "InterfaceEvent.h"

class KeyDownEvent : public InterfaceEvent
{
public:
	KeyDownEvent(unsigned int keycode);
	~KeyDownEvent();

	unsigned int getKeyCode() const;

private:
	unsigned int mKeyCode;
};