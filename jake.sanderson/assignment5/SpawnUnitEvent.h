#pragma once
#include "GameEvent.h"
#include <Vector2D.h>

class SpawnUnitEvent : public GameEvent
{
public:
	SpawnUnitEvent(Vector2D spawnPos);
	~SpawnUnitEvent();

	Vector2D getSpawnPos() const;

private:
	Vector2D mSpawnPos;
};

