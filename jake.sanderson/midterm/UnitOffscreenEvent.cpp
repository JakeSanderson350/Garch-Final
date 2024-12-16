#include "UnitOffscreenEvent.h"

UnitOffscreenEvent::UnitOffscreenEvent(bool orbIsBlue) : GameEvent(UNIT_OFFSCREEN)
{
	mIsBlue = orbIsBlue;
}

UnitOffscreenEvent::~UnitOffscreenEvent()
{

}

bool UnitOffscreenEvent::isUnitBlue() const
{
	return mIsBlue;
}
