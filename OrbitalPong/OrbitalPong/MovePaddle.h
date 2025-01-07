#pragma once
#include "GameEvent.h"

class MovePaddle : public GameEvent
{
public:
	MovePaddle(float deltaRotation, int paddleIndex);
	~MovePaddle();

	float getDeltaRotation() const { return mDeltaRotation; };
	int getPaddleIndex() const { return mPaddleIndex; };

private:
	float mDeltaRotation;  //Change in rotation of paddle
	int mPaddleIndex;  //Index of which paddle to move
};

