#include "ChangeUnitCurrentAnimationEvent.h"

ChangeUnitCurrentAnimationEvent::ChangeUnitCurrentAnimationEvent(unsigned int animationIndex) : GameEvent(CHANGE_UNIT_CURRENT_ANIMATION)
{
	mCurrentAnimationIndex = animationIndex;
}

ChangeUnitCurrentAnimationEvent::~ChangeUnitCurrentAnimationEvent()
{

}

unsigned int ChangeUnitCurrentAnimationEvent::getCurrentAnimationIndex() const
{
	return mCurrentAnimationIndex;
}
