#include "Unit.h"
#include "GraphicsBuffer.h"

Unit::Unit()
{
	mPos = Vector2D(0, 0);
	mVelocity = 0;
	mCurrentAnimation = 0;
}

Unit::Unit(Vector2D position, float velocity)
{
	mPos = position;
	mVelocity = velocity;
}

Unit::Unit(Vector2D position, float velocity, Animation* animation) : Unit(position, velocity)
{
	mAnimations.push_back(animation);
}

Unit::Unit(Vector2D position, float velocity, std::vector<Animation*> animations) : Unit(position, velocity)
{
	for (int i = 0; i < animations.size(); i++)
	{
		mAnimations.push_back(animations[i]);
	}
}

Unit::~Unit()
{
}

void Unit::update(float elapsedTime)
{
	//Update animation and position
	mAnimations[mCurrentAnimation]->update(elapsedTime);

	setPostition(Vector2D(mPos.getX() + mVelocity, mPos.getY()));
}

void Unit::setPostition(Vector2D position)
{
	mPos = position;
}

void Unit::setAnimation(int index, float animSpeed)
{
	//Make sure index given is valid
	if (index < mAnimations.size())
	{
		mCurrentAnimation = index;

		mAnimations[mCurrentAnimation]->setSpeed(animSpeed);
	}
}

void Unit::addAnimation(Animation* animation)
{
	mAnimations.push_back(animation);
}

void Unit::draw(GraphicsBuffer* destLoc)
{
	//Get current sprite in animation and draw
	Sprite currentSprite = mAnimations[mCurrentAnimation]->getCurrentSprite();

	destLoc->draw(mPos, currentSprite);
}
