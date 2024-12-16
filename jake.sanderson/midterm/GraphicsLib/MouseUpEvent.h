#pragma once
#include "InterfaceEvent.h"
#include <Vector2D.h>

class MouseUpEvent : public InterfaceEvent
{
public:
	MouseUpEvent(unsigned int mouseButtonCode, Vector2D mousePos);
	~MouseUpEvent();

	unsigned int getMouseButtonCode() const;
	Vector2D getMousePos() const;

private:
	unsigned int mMouseButtonCode;
	Vector2D mMousePosition;
};

