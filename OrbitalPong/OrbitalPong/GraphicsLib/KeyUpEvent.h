#pragma once
#include "InterfaceEvent.h"

class KeyUpEvent : public InterfaceEvent
{
public:
	KeyUpEvent(unsigned int keycode);
	~KeyUpEvent();

	unsigned int getKeyCode() const;

private:
	unsigned int mKeyCode;
};

