#include "MouseDownEvent.h"

MouseDownEvent::MouseDownEvent(unsigned int mouseButtonCode, Vector2D mousePos) : InterfaceEvent(MOUSE_INPUT_DOWN_EVENT)
{
	mMouseButtonCode = mouseButtonCode;
	mMousePosition = mousePos;
}

MouseDownEvent::~MouseDownEvent()
{

}

unsigned int MouseDownEvent::getMouseButtonCode() const
{
	return mMouseButtonCode;
}

Vector2D MouseDownEvent::getMousePos() const
{
	return mMousePosition;
}