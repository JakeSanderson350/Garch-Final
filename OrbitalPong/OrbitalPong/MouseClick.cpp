#include "MouseClick.h"

MouseClick::MouseClick(Vector2D posClicked) : GameEvent(MOUSE_CLICK_EVENT)
{
	mPosClicked = posClicked;
}

MouseClick::~MouseClick()
{
}

Vector2D MouseClick::getPositionClicked() const
{
	return mPosClicked;
}
