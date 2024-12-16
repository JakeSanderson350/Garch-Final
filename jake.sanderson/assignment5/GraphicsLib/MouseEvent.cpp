#include "MouseEvent.h"

MouseEvent::MouseEvent(unsigned int mouseButtonCode, Vector2D mousePos) : InterfaceEvent (MOUSE_INPUT_EVENT)
{
	mMouseButtonCode = mouseButtonCode;
	mMousePosition = mousePos;
}

MouseEvent::~MouseEvent()
{
}

unsigned int MouseEvent::getMouseButtonCode() const
{
	return mMouseButtonCode;
}

Vector2D MouseEvent::getMousePos() const
{
	return mMousePosition;
}
