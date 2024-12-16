#include "UnitManager.h"
#include "Unit.h"

void UnitManager::cleanup()
{	
	for (std::vector<Unit*>::iterator iter = mpUnits.begin(); iter != mpUnits.end(); ++iter)
	{
		Unit* theUnit = *iter;
		delete theUnit;
	}
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		Unit* pUnit = mpUnits[i];
		delete pUnit;
	}

	mpUnits.clear();
}

void UnitManager::createAndAddUnit()
{
	//create unit
	Unit* pUnit = new Unit;
	//manage the unit
	mpUnits.push_back(pUnit);
}

void UnitManager::destroyUnit(Unit* pUnitToDestroy)
{
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		Unit* pUnit = mpUnits[i];
		if (pUnit == pUnitToDestroy)
		{
			delete pUnit;
			mpUnits.erase(mpUnits.begin() + i);
			break;
		}

	}

}

void UnitManager::update(double dt)
{
	for (std::vector<Unit*>::iterator iter = mpUnits.begin(); iter != mpUnits.end(); ++iter)
	{
		Unit* pUnit = *iter;
		//pUnit->update(dt);
	}
}

void UnitManager::draw()
{
	for (std::vector<Unit*>::iterator iter = mpUnits.begin(); iter != mpUnits.end(); ++iter)
	{
		Unit* pUnit = *iter;
		//pUnit->draw();
	}

}

Unit* UnitManager::getUnit()
{
	if (mpUnits.size() > 0)
		return mpUnits[0];
	else
		return nullptr;
}
