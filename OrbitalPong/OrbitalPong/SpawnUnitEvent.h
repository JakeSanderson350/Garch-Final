#pragma once
#include "GameEvent.h"
#include <Vector2D.h>

class SpawnUnitEvent : public GameEvent
{
public:
	SpawnUnitEvent(Vector2D spawnPos, Vector2D spawnVel);
	~SpawnUnitEvent();

	Vector2D getSpawnPosition() const;
	Vector2D getSpawnVelocity() const;

private:
	Vector2D mSpawnPos;
	Vector2D mSpawnVel;
};

