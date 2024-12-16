#include "RemoveUnitEvent.h"

RemoveUnitEvent::RemoveUnitEvent(Vector2D deletePos) : GameEvent(REMOVE_UNIT)
{
	mDeletePos = deletePos;
}

RemoveUnitEvent::~RemoveUnitEvent()
{

}

Vector2D RemoveUnitEvent::getDeletePos() const
{
	return mDeletePos;
}
