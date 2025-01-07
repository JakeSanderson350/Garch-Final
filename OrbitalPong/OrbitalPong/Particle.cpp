#include "Particle.h"
#include "GraphicsBuffer.h"

Particle::Particle()
{
	mPosition = Vector2D();
	mVelocity = Vector2D();

	mRotation = 0.0f;
	mRotatesRight = (rand() % 2) + 1 > 1; //sets rotation randomly

	mFramesToLive = 0;
}

void Particle::init(Vector2D position, Vector2D velocity, int framesToLive)
{
	mPosition = position;
	mVelocity = velocity;
	mFramesToLive = framesToLive;
}

bool Particle::update()
{
	if (inUse())
	{
		mFramesToLive--;

		mPosition += mVelocity;

		if (mRotatesRight)
		{
			mRotation += 3;
		}
		else
		{
			mRotation -= 3;
		}

		return mFramesToLive == 0;
	}

	else
	{
		return false;
	}
}

void Particle::draw(GraphicsBuffer* destLoc, Sprite particleSprite)
{
	if (inUse())
	{
		destLoc->draw(mPosition, particleSprite, mRotation);
	}
}

void Particle::setNext(Particle* next)
{
	mNext = next;
}
