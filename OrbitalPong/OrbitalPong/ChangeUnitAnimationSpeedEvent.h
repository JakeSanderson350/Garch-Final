#pragma once
#include "GameEvent.h"

class ChangeUnitAnimationSpeedEvent : public GameEvent
{
public:
	ChangeUnitAnimationSpeedEvent(float animationSpeed);
	~ChangeUnitAnimationSpeedEvent();

	float getAnimationSpeed() const;

private:
	float mAnimationSpeed;
};

