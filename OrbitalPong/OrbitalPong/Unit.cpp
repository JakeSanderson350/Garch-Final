#include "Unit.h"
#include "GraphicsBuffer.h"

Unit::Unit()
{
	mPos = Vector2D(0, 0);
	mVelocity = Vector2D(0, 0);
	mNormal = Vector2D(0, 1);

	mCurrentAnimation = 0;
	mIsAnimating = true;

	mUnitType = DEFAULT_UNIT;
}

Unit::Unit(Vector2D position, Vector2D velocity, UnitType unitType)
{
	mPos = position;
	mVelocity = velocity;
	setNormalToVelocity();

	mCurrentAnimation = 0;
	mIsAnimating = true;

	mUnitType = unitType;
}

Unit::Unit(Vector2D position, Vector2D velocity, Sprite sprite, UnitType unitType) : Unit(position, velocity, unitType)
{
	mAnimations.push_back(Animation(sprite));

	setUnitDimensions();
}

Unit::Unit(Vector2D position, Vector2D velocity, Animation* animation, UnitType unitType) : Unit(position, velocity, unitType)
{
	mAnimations.push_back(Animation(*animation));

	setUnitDimensions();
}

Unit::Unit(Vector2D position, Vector2D velocity, std::vector<Animation*> animations, UnitType unitType) : Unit(position, velocity, unitType)
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

void Unit::update(float elapsedTime)
{
	//Update animation and position
	if (mIsAnimating)
	{
		mAnimations[mCurrentAnimation].update(elapsedTime);
	}
	//Normalize velocity directional vector
	//mVelocity.normalize();
	mPos += mVelocity;

	//If just collided count how long since collided
	if (mJustCollided)
	{
		mTimeSinceCollision += elapsedTime;

		if (mTimeSinceCollision >= 250.0f) //If time since last collision is greater than 1/4 second allow it to be able to collide again
		{
			mJustCollided = false;
			mTimeSinceCollision = 0.0f;
		}
	}

	setUnitDimensions();
}

void Unit::setCurrentAnimation(unsigned int index)
{
	if (index < mAnimations.size())
	{
		mCurrentAnimation = index;
	}
}

void Unit::toggleCurrentAnimation()
{
	mCurrentAnimation = (mCurrentAnimation + 1) % mAnimations.size();
}

void Unit::setAnimationSpeed(float animSpeed)
{
	for (unsigned int i = 0; i < mAnimations.size() - 1; i++)
	{
		mAnimations[mCurrentAnimation].setSpeed(animSpeed);
	}
}

void Unit::setAnimation(unsigned int index, float animSpeed)
{
	//Make sure index given is valid
	if (index < mAnimations.size())
	{
		mCurrentAnimation = index;

		setAnimationSpeed(animSpeed);
	}
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

	destLoc->draw((mPos - offset), currentSprite, convertAngle(mRotation));
}

Vector2D Unit::calculateOffset()
{
	float xOffset = mUnitWidth / 2;
	float yOffset = mUnitHeight / 2;

	return Vector2D(xOffset, yOffset);
}

//Take in angle in cord system where 0 is East, 90 is North, 180 is West, and 270 is South
//Converts to angle in cord system where 0 is North, 90 is East, 180 is South, and 270 is West
float Unit::convertAngle(float angleToBeConverted)
{
	float newAngle = (int)((-1.0f * angleToBeConverted) + 90.0f) % 360;

	return newAngle;
}

float Unit::degreeToRadians(float degree)
{
	float radian = degree * (3.14157f / 180.0f);

	return radian;
}

void Unit::setUnitDimensions()
{
	mUnitWidth = mAnimations[mCurrentAnimation].getCurrentSprite().getWidth();
	mUnitHeight = mAnimations[mCurrentAnimation].getCurrentSprite().getHeight();
}

void Unit::setNormalToVelocity()
{
	if (mVelocity == Vector2D(0.0f, 0.0f))
	{
		mNormal = Vector2D(1.0f, 1.0f);
	}

	else
	{
		Vector2D normVector = mVelocity;
		normVector.normalize();

		mNormal = normVector;
	}
}

//Return string with unit values
std::string Unit::printUnit() const
{
	std::stringstream strs;
	strs << mUnitType << '\n';
	strs << mPos.getX() << " " << mPos.getY() << '\n';
	strs << mVelocity.getX() << " " << mVelocity.getY() << '\n';
	strs << mNormal.getX() << " " << mNormal.getY() << '\n';
	strs << mRotation << '\n';
	return strs.str();
}

std::ostream& operator<<(std::ostream& out, const Unit* unit)
{
	out << unit->printUnit();
	return out;
}

std::istream& operator>>(std::istream& in, Unit& unit)
{
	float xPos, yPos;
	in >> xPos >> yPos;
	unit.mPos = Vector2D(xPos, yPos);

	float xVel, yVel;
	in >> xVel >> yVel;
	unit.mVelocity = Vector2D(xVel, yVel);

	float xNorm, yNorm;
	in >> xNorm >> yNorm;
	unit.mNormal = Vector2D(xNorm, yNorm);

	in >> unit.mRotation;

	return in;
}

void pushBackUnit(Vector2D offScreen, Unit& unit)
{
	unit.mPos = unit.mPos - offScreen;
}
