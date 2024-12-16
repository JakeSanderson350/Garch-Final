#include "UnitOffscreenEvent.h"

UnitOffscreenEvent::UnitOffscreenEvent(Vector2D position) : GameEvent(UNIT_OFFSCREEN)
{
	mPos = position;
}

UnitOffscreenEvent::~UnitOffscreenEvent()
{

}

Vector2D UnitOffscreenEvent::getPosition() const
{
	return mPos;
}
