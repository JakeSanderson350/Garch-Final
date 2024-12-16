#include "ChangeUnitAnimationSpeedEvent.h"

ChangeUnitAnimationSpeedEvent::ChangeUnitAnimationSpeedEvent(float animationSpeed) : GameEvent (CHANGE_UNIT_ANIMATION_SPEED)
{
	mAnimationSpeed = animationSpeed;
}

ChangeUnitAnimationSpeedEvent::~ChangeUnitAnimationSpeedEvent()
{

}

float ChangeUnitAnimationSpeedEvent::getAnimationSpeed() const
{
	return mAnimationSpeed;
}
