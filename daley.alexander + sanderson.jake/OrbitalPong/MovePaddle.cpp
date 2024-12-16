#include "MovePaddle.h"

MovePaddle::MovePaddle(float deltaRotation, int paddleIndex) : GameEvent(MOVE_PADDLE_EVENT)
{
	mDeltaRotation = deltaRotation;
	mPaddleIndex = paddleIndex;
}

MovePaddle::~MovePaddle()
{

}
