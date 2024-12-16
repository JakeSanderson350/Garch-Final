#pragma once

#include <Trackable.h>
#include "Unit.h"

#include <vector>

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

	void toggleAnimations();

	void update(float dt);

	void draw(GraphicsBuffer* destLoc);

	Unit* getLastUnit();
	int getSize();
private:
	std::vector<Unit*> mpUnits;

	bool mUnitsAnimating = true;
};

