#include "EmitParticleEvent.h"

EmitParticleEvent::EmitParticleEvent(int numParticles, Vector2D pos, Vector2D directionToEmit) : GameEvent(EMIT_PARTICLE_EVENT)
{
	mNumParticles = numParticles;
	mPos = pos;
	mDirectionToEmit = directionToEmit;
}

EmitParticleEvent::~EmitParticleEvent()
{

}

unsigned int EmitParticleEvent::getNumParticles() const
{
	return mNumParticles;
}

Vector2D EmitParticleEvent::getPos() const
{
	return mPos;
}

Vector2D EmitParticleEvent::getDirectionToEmit() const
{
	return mDirectionToEmit;
}
