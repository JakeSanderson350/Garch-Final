#pragma once

#include <Trackable.h>

#include <Vector2D.h>
#include <vector>
#include <Animation.h>

class GraphicsBuffer;

class Unit : public Trackable
{
	friend class UnitManager;//UnitManager is only class capable of making/deleting units
public:
	void update(float elapsedTime);

	void setPostition(Vector2D position);

	void setAnimation(unsigned int index, float animSpeed);
	void addAnimation(Animation* animation);

	void draw(GraphicsBuffer* destLoc);

	Vector2D calculateOffset();

private:
	Vector2D mPos;
	Vector2D mVelocity;

	int mUnitWidth;
	int mUnitHeight;

	std::vector<Animation> mAnimations;
	int mCurrentAnimation;

	bool mIsAnimating;

	Unit();
	Unit(Vector2D position, Vector2D velocity);
	Unit(Vector2D position, Vector2D velocity, Animation* animation);
	Unit(Vector2D position, Vector2D velocity, std::vector<Animation*> animations);

	~Unit();

	void setUnitDimensions();
};

