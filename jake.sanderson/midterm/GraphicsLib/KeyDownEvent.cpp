#include "KeyDownEvent.h"

KeyDownEvent::KeyDownEvent(unsigned int keycode) : InterfaceEvent(KEY_DOWN_EVENT)
{
	mKeyCode = keycode;
}

KeyDownEvent::~KeyDownEvent()
{

}

unsigned int KeyDownEvent::getKeyCode() const
{
	return mKeyCode;
}