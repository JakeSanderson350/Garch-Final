#pragma once
#include "InterfaceEvent.h"
#include <Vector2D.h>

class MouseDownEvent : public InterfaceEvent
{
public:
	MouseDownEvent(unsigned int mouseButtonCode, Vector2D mousePos);
	~MouseDownEvent();

	unsigned int getMouseButtonCode() const;
	Vector2D getMousePos() const;

private:
	unsigned int mMouseButtonCode;
	Vector2D mMousePosition;
};

