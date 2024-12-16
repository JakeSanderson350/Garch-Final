#include "Unit.h"
#include "GraphicsBuffer.h"

Unit::Unit()
{
	mPos = Vector2D(0, 0);
	mVelocity = Vector2D(0, 0);
	mCurrentAnimation = 0;
	mIsAnimating = true;
}

Unit::Unit(Vector2D position, Vector2D velocity)
{
	mPos = position;
	mVelocity = velocity;
	mCurrentAnimation = 0;
	mIsAnimating = true;
}

Unit::Unit(Vector2D position, Vector2D velocity, Animation* animation) : Unit(position, velocity)
{
	mAnimations.push_back(Animation(*animation));

	setUnitDimensions();
}

Unit::Unit(Vector2D position, Vector2D velocity, std::vector<Animation*> animations) : Unit(position, velocity)
{
	for (unsigned int i = 0; i < animations.size(); i++)
	{
		mAnimations.push_back(Animation(*animations[i]));
	}

	setUnitDimensions();
}

Unit::~Unit()
{
}

void Unit::setUnitDimensions()
{
	mUnitWidth = mAnimations[mCurrentAnimation].getCurrentSprite().getWidth();
	mUnitHeight = mAnimations[mCurrentAnimation].getCurrentSprite().getHeight();
}

void Unit::update(float elapsedTime)
{
	//Update animation and position
	if (mIsAnimating)
	{
		mAnimations[mCurrentAnimation].update(elapsedTime);
	}

	setPostition(Vector2D(mPos.getX() + mVelocity.getX(), mPos.getY() + mVelocity.getY()));
}

void Unit::setPostition(Vector2D position)
{
	mPos = position;
}

void Unit::setAnimation(unsigned int index, float animSpeed)
{
	//Make sure index given is valid
	if (index < mAnimations.size())
	{
		mCurrentAnimation = index;

		mAnimations[mCurrentAnimation].setSpeed(animSpeed);
	}

	setUnitDimensions();
}

void Unit::addAnimation(Animation* animation)
{
	mAnimations.push_back(Animation(*animation));
}

void Unit::draw(GraphicsBuffer* destLoc)
{
	//Get current sprite in animation and draw
	Sprite currentSprite = mAnimations[mCurrentAnimation].getCurrentSprite();

	//Calculate offset based on size of current sprite
	Vector2D offset = calculateOffset();

	destLoc->draw((mPos - offset), currentSprite);
}

Vector2D Unit::calculateOffset()
{
	float xOffset = mAnimations[mCurrentAnimation].getCurrentSprite().getWidth() / 2;
	float yOffset = mAnimations[mCurrentAnimation].getCurrentSprite().getHeight() / 2;

	return Vector2D(xOffset, yOffset);
}
