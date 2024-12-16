#pragma once

#include <Trackable.h>

class Unit:public Trackable
{
public:
	friend class UnitManager;

	void setAnimation() {}

private:
	Unit() {};
	~Unit() {};

};