#pragma once

#include "GameEvent.h"

class UnitOffscreenEvent : public GameEvent
{
public:
	UnitOffscreenEvent(bool orbIsBlue);
	~UnitOffscreenEvent();

	bool isUnitBlue() const;

private:
	bool mIsBlue;
};

