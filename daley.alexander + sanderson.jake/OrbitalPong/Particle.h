#pragma once

#include <Trackable.h>

#include <Vector2D.h>
#include "Sprite.h"

class Particle : public Trackable
{
public:
	Particle();

	void init(Vector2D position, Vector2D velocity, int framesToLive);

	bool update();
	void draw(GraphicsBuffer* destLoc, Sprite particleSprite);

	bool inUse() const { return mFramesToLive > 0; };
	Particle* getNext() const { return mNext; };

	void setNext(Particle* next);

private:
	Vector2D mPosition;
	Vector2D mVelocity;

	float mRotation;
	bool mRotatesRight;

	int mFramesToLive;

	Particle* mNext;
};

