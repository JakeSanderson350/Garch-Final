#include "ChangeUnitCurrentAnimationEvent.h"

ChangeUnitCurrentAnimationEvent::ChangeUnitCurrentAnimationEvent(Vector2D posClicked) : GameEvent(CHANGE_UNIT_CURRENT_ANIMATION)
{
	mPosClicked = posClicked;
}

ChangeUnitCurrentAnimationEvent::~ChangeUnitCurrentAnimationEvent()
{

}

Vector2D ChangeUnitCurrentAnimationEvent::getPositionClicked() const
{
	return mPosClicked;
}
