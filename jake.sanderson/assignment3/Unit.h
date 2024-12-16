#pragma once

#include "C:\Users\jake.sanderson\Desktop\Game Arch\shared\DeanLib\include\Trackable.h"

#include <Vector2D.h>
#include <vector>
#include <Animation.h>

class GraphicsBuffer;

class Unit : public Trackable
{
public:
	Unit();
	Unit(Vector2D position, float velocity);
	Unit(Vector2D position, float velocity, Animation* animation);
	Unit(Vector2D position, float velocity, std::vector<Animation*> animations);

	~Unit();

	void update(float elapsedTime);

	void setPostition(Vector2D position);

	void setAnimation(int index, float animSpeed);
	void addAnimation(Animation* animation);

	void draw(GraphicsBuffer* destLoc);

private:
	Vector2D mPos;
	float mVelocity;

	std::vector<Animation*> mAnimations;
	int mCurrentAnimation;
};

