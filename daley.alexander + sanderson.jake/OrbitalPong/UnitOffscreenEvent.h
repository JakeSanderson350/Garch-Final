#pragma once

#include "GameEvent.h"
#include <Vector2D.h>

class UnitOffscreenEvent : public GameEvent
{
public:
	UnitOffscreenEvent(Vector2D position);
	~UnitOffscreenEvent();

	Vector2D getPosition() const;

private:
	Vector2D mPos;
};

