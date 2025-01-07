#pragma once
#include "GameEvent.h"
#include <Vector2D.h>

class RemoveUnitEvent : public GameEvent
{
public:
	RemoveUnitEvent(Vector2D deletePos);
	~RemoveUnitEvent();

	Vector2D getDeletePos() const;

private:
	Vector2D mDeletePos;
};

