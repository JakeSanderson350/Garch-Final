#include "StopPaddle.h"

StopPaddle::StopPaddle(int paddleIndex) : GameEvent(STOP_PADDLE_EVENT)
{
	mPaddleIndex = paddleIndex;
}

StopPaddle::~StopPaddle()
{
}
