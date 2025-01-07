#include "MouseUpEvent.h"

MouseUpEvent::MouseUpEvent(unsigned int mouseButtonCode, Vector2D mousePos) : InterfaceEvent(MOUSE_INPUT_UP_EVENT)
{
	mMouseButtonCode = mouseButtonCode;
	mMousePosition = mousePos;
}

MouseUpEvent::~MouseUpEvent()
{

}

unsigned int MouseUpEvent::getMouseButtonCode() const
{
	return mMouseButtonCode;
}

Vector2D MouseUpEvent::getMousePos() const
{
	return mMousePosition;
}