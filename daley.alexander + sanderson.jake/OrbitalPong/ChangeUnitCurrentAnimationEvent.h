#pragma once

#include "GameEvent.h"
#include <Vector2D.h>

class ChangeUnitCurrentAnimationEvent : public GameEvent
{
public:
	ChangeUnitCurrentAnimationEvent(Vector2D posClicked);
	~ChangeUnitCurrentAnimationEvent();

	Vector2D getPositionClicked() const;

private:
	Vector2D mPosClicked;
};

