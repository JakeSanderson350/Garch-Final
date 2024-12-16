#include "ParticleSystem.h"

#include "EventSystem.h"
#include "EmitParticleEvent.h"

ParticleSystem::ParticleSystem()
{
	mFirstAvailable = &mParticleList[0];

	for (unsigned int i = 0; i < POOL_SIZE - 1; i++)
	{
		mParticleList[i].setNext(&mParticleList[i + 1]);
	}
	mParticleList[POOL_SIZE - 1].setNext(nullptr);

	EventSystem::getInstance()->addListener((EventType)EMIT_PARTICLE_EVENT, this);
}

bool ParticleSystem::init(Sprite* particleSprite)
{
	mParticleSprite = Sprite(*particleSprite);

	return true;
}

void ParticleSystem::createParticle(Vector2D position, Vector2D velocity, int framesToLive)
{
	if (mFirstAvailable != nullptr)
	{
		Particle* newParticle = mFirstAvailable;
		mFirstAvailable = newParticle->getNext();

		newParticle->init(position, velocity, framesToLive);
	}
}

void ParticleSystem::update()
{
	for (unsigned int i = 0; i < POOL_SIZE; i++)
	{
		if (mParticleList[i].update())
		{
			mParticleList[i].setNext(mFirstAvailable);
			mFirstAvailable = &mParticleList[i];
		}
	}
}

void ParticleSystem::draw(GraphicsBuffer* destLoc)
{
	for (unsigned int i = 0; i < POOL_SIZE; i++)
	{
		mParticleList[i].draw(destLoc, mParticleSprite);
	}
}

void ParticleSystem::cleanup()
{
	mFirstAvailable = nullptr;
}

void ParticleSystem::handleEvent(const Event& currentEvent)
{
	if (currentEvent.getType() == EMIT_PARTICLE_EVENT)
	{
		const EmitParticleEvent& particleEvent = static_cast<const EmitParticleEvent&>(currentEvent);

		for (unsigned int i = 0; i < particleEvent.getNumParticles(); i++)
		{
			//Particle Velocity
			float deltaAngle = (float)((rand() % 91) - 45); //range between -45 to 45
			float deltaRadians = deltaAngle * (3.14157f / 180.0f);

			//Normalize direction
			Vector2D partDirection = particleEvent.getDirectionToEmit();

			partDirection.setX((partDirection.getX() * cos(deltaRadians)) - (partDirection.getY() * sin(deltaRadians)));
			partDirection.setY((particleEvent.getDirectionToEmit().getX() * sin(deltaRadians)) + (particleEvent.getDirectionToEmit().getY() * cos(deltaRadians)));

			partDirection.normalize();

			//Get speed relative to framerate
			float partSpeed = (float)((rand() % 5) + 1); //range between 1 to 5

			Vector2D partVelocity = partDirection * partSpeed;

			createParticle(particleEvent.getPos(), partVelocity, FRAMES_PER_PARTICLE);
		}
	}
}
