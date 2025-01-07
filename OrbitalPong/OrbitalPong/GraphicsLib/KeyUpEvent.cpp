#include "KeyUpEvent.h"

KeyUpEvent::KeyUpEvent(unsigned int keycode) : InterfaceEvent(KEY_UP_EVENT)
{
	mKeyCode = keycode;
}

KeyUpEvent::~KeyUpEvent()
{

}

unsigned int KeyUpEvent::getKeyCode() const
{
	return mKeyCode;
}