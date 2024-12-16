#include "SpawnUnitEvent.h"

SpawnUnitEvent::SpawnUnitEvent(Vector2D spawnPos) : GameEvent(SPAWN_UNIT)
{
	mSpawnPos = spawnPos;
}

SpawnUnitEvent::~SpawnUnitEvent()
{

}

Vector2D SpawnUnitEvent::getSpawnPos() const
{
	return mSpawnPos;
}
