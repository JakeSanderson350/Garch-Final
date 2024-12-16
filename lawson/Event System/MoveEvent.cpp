#include "MoveEvent.h"

MoveEvent::MoveEvent(const Vector2D& loc)
:GameEvent( MOVE_EVENT )
,mLoc(loc)
{
}

MoveEvent::~MoveEvent()
{
}
