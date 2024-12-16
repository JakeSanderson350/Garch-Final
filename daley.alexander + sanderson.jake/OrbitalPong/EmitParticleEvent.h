#pragma once
#include "GameEvent.h"

#include <Vector2D.h>

class EmitParticleEvent : public GameEvent
{
public:
	EmitParticleEvent(int numParticles, Vector2D pos, Vector2D directionToEmit);
	~EmitParticleEvent();

	unsigned int getNumParticles() const;
	Vector2D getPos() const;
	Vector2D getDirectionToEmit() const;

private:
	unsigned int mNumParticles;

	Vector2D mPos;
	Vector2D mDirectionToEmit;
};

