#pragma once

#include <EventListener.h>

#include <Vector2D.h>
#include "Particle.h"

const int POOL_SIZE = 100;
const int FRAMES_PER_PARTICLE = 60;

class ParticleSystem : public EventListener
{
public:
	ParticleSystem();

	bool init(Sprite* particleSprite);

	void createParticle(Vector2D position, Vector2D velocity, int framesToLive);

	void update();
	void draw(GraphicsBuffer* destLoc);

	void cleanup();

	void handleEvent(const Event& currentEvent);

private:
	Sprite mParticleSprite;

	Particle* mFirstAvailable;
	Particle mParticleList[POOL_SIZE];
};