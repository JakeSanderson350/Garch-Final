#pragma once

#include <Vector2D.h>
#include "GameEvent.h"

class MoveEvent : public GameEvent
{
public:
	MoveEvent( const Vector2D& loc );
	~MoveEvent();

	Vector2D getLocation() const { return mLoc; };

private:
	Vector2D mLoc;
};