#pragma once
#include "InterfaceEvent.h"
#include <Vector2D.h>

class MouseEvent :  public InterfaceEvent
{
public:
	MouseEvent(unsigned int mouseButtonCode, Vector2D mousePos);
	~MouseEvent();

	unsigned int getMouseButtonCode() const;
	Vector2D getMousePos() const;

private:
	unsigned int mMouseButtonCode;
	Vector2D mMousePosition;
};

