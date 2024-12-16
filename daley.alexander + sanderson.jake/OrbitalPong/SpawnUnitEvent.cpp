#include "SpawnUnitEvent.h"

SpawnUnitEvent::SpawnUnitEvent(Vector2D spawnPos, Vector2D spawnVel) : GameEvent(SPAWN_UNIT)
{
	mSpawnPos = spawnPos;
	mSpawnVel = spawnVel;
}

SpawnUnitEvent::~SpawnUnitEvent()
{

}

Vector2D SpawnUnitEvent::getSpawnPosition() const
{
	return mSpawnPos;
}

Vector2D SpawnUnitEvent::getSpawnVelocity() const
{
	return mSpawnVel;
}
