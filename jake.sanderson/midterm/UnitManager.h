#pragma once

#include <Trackable.h>
#include "Unit.h"

#include <EventSystem.h>
#include "UnitOffscreenEvent.h"

#include <vector>

const int BLUE_ORB_ANIM_INDEX = 1;

class Animation;

class UnitManager :public Trackable
{
public:
	UnitManager() {};
	~UnitManager();

	bool init();

	void cleanup();

	void createAndAddUnit(Vector2D position, Vector2D velocity, Animation* animation);
	void createAndAddUnit(Vector2D position, Vector2D velocity, std::vector<Animation*> animations);

	void destroyUnit(Unit* pUnit);
	void destroyUnit(Vector2D position);
	void destroyUnitsOffScreen(Vector2D bounds);

	void setAllUnitsAnimating(bool isAnimating);
	void toggleCurrentAnimation(Unit* pUnit);

	void update(float elapsedTime);

	void draw(GraphicsBuffer* destLoc);

	Unit* getLastUnit();
	Unit* getUnit(Vector2D position);

	int getSize();

private:
	std::vector<Unit*> mpUnits;

	Vector2D mScreenBounds;
};

