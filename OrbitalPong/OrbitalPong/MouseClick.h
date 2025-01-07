#pragma once

#include "GameEvent.h"
#include <Vector2D.h>

class MouseClick : public GameEvent
{
public:
	MouseClick(Vector2D posClicked);
	~MouseClick();

	Vector2D getPositionClicked() const;

private:
	Vector2D mPosClicked;
};
