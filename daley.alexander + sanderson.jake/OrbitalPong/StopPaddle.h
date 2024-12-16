#pragma once
#include "GameEvent.h"

class StopPaddle : public GameEvent
{

public:
	StopPaddle(int paddleIndex);
	~StopPaddle();

	int getPaddleIndex() const { return mPaddleIndex; };

private:
	int mPaddleIndex;
};

