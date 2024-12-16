#pragma once
#include "GameEvent.h"

class ChangeUnitCurrentAnimationEvent : public GameEvent
{
public:
	ChangeUnitCurrentAnimationEvent(unsigned int animationIndex);
	~ChangeUnitCurrentAnimationEvent();

	unsigned int getCurrentAnimationIndex() const;

private:
	unsigned int mCurrentAnimationIndex;
};

