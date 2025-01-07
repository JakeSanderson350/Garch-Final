#pragma once

#include <Trackable.h>

#include <Vector2D.h>
#include <vector>
#include <Animation.h>

#include <sstream>
#include <fstream>

//Ennumerator for each unique unit
enum UnitType
{
	DEFAULT_UNIT = 0,
	BALL_UNIT,
	PADDLE_UNIT,
	GOAL_UNIT
};

class GraphicsBuffer;

class Unit : public Trackable
{
	friend class UnitManager;//UnitManager is only class capable of making/deleting units
public:
	void update(float elapsedTime);

	void setCurrentAnimation(unsigned int index);
	void toggleCurrentAnimation();
	void setAnimationSpeed(float animSpeed);
	void setAnimation(unsigned int index, float animSpeed);
	void addAnimation(Animation* animation);

	UnitType getUnitType() { return mUnitType; };

	void draw(GraphicsBuffer* destLoc);

	Vector2D calculateOffset();

	static float convertAngle(float angleToBeConverted);
	static float degreeToRadians(float degree);

	friend std::ostream& operator<<(std::ostream& out, const Unit* unit);
	friend std::istream& operator>>(std::istream& in, Unit& unit);
	friend void pushBackUnit(Vector2D offScreen, Unit& unit);  //used strictly for when a unit goes offscreen

private:
	Vector2D mPos;
	Vector2D mVelocity;
	Vector2D mNormal;//used for collsion

	//mRotation is in cord system where 0 is East, 90 is North, 180 is West, and 270 is South
	float mRotation = 0;
	int mUnitWidth;
	int mUnitHeight;
	UnitType mUnitType;
	std::vector<Animation> mAnimations;
	int mCurrentAnimation;

	bool mIsAnimating;

	//Collision
	bool mJustCollided = false;
	float mTimeSinceCollision = 0.0f;

	Unit();
	Unit(Vector2D position, Vector2D velocity, UnitType unitType = DEFAULT_UNIT);
	Unit(Vector2D position, Vector2D velocity, Sprite sprite, UnitType unitType = DEFAULT_UNIT);
	Unit(Vector2D position, Vector2D velocity, Animation* animation, UnitType unitType = DEFAULT_UNIT);
	Unit(Vector2D position, Vector2D velocity, std::vector<Animation*> animations, UnitType unitType = DEFAULT_UNIT);

	~Unit();

	void setUnitDimensions();
	void setNormalToVelocity();

	std::string printUnit() const;
};

