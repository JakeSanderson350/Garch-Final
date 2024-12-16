#pragma once

#include <Trackable.h>
#include <vector>

class Unit;

class UnitManager :public Trackable
{
public:
	UnitManager() {};
	~UnitManager() { cleanup(); };

	void cleanup();

	void createAndAddUnit();
	void destroyUnit(Unit* pUnit);
	void update(double dt);
	void draw();
	Unit* getUnit();
private:
	std::vector<Unit*> mpUnits;
};