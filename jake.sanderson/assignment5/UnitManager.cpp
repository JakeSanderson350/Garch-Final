#include "UnitManager.h"

UnitManager::~UnitManager()
{
	cleanup();
}

bool UnitManager::init()
{
	return true;
}

void UnitManager::cleanup()
{
	//Goes through vector of units and deletes each one
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		Unit* pUnit = mpUnits[i];
		delete pUnit;
	}

	mpUnits.clear();
}

void UnitManager::createAndAddUnit(Vector2D position, Vector2D velocity, Animation* animation)
{
	Unit* newUnit = new Unit(position, velocity, animation);

	mpUnits.push_back(newUnit);
}

void UnitManager::createAndAddUnit(Vector2D position, Vector2D velocity, std::vector<Animation*> animations)
{
	Unit* newUnit = new Unit(position, velocity, animations);

	mpUnits.push_back(newUnit);
}

void UnitManager::destroyUnit(Unit* pUnitToBeDestroyed)
{
	//Finds unit that matches pointer and deletes it
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		Unit* pTmpUnit = mpUnits[i];

		if (pTmpUnit == pUnitToBeDestroyed)
		{
			delete pTmpUnit;
			mpUnits.erase(mpUnits.begin() + i);
			break;
		}
	}
}

void UnitManager::destroyUnit(Vector2D position)
{
	int unitWidthOffset, unitHeightOffset;
	Vector2D positionOffset;

	//Finds unit that matches position and deletes it
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		Unit* pTmpUnit = mpUnits[i];

		//Offsets used so sprite has to be clicked near center to be deleted
		unitWidthOffset = pTmpUnit->mAnimations[pTmpUnit->mCurrentAnimation].getCurrentSprite().getWidth();
		unitHeightOffset = pTmpUnit->mAnimations[pTmpUnit->mCurrentAnimation].getCurrentSprite().getHeight();
		positionOffset = position + pTmpUnit->calculateOffset();

		if ((positionOffset.getX() >= pTmpUnit->mPos.getX() && positionOffset.getX() <= pTmpUnit->mPos.getX() + unitWidthOffset) &&
			(positionOffset.getY() >= pTmpUnit->mPos.getY() && positionOffset.getY() <= pTmpUnit->mPos.getY() + unitHeightOffset))
		{
			delete pTmpUnit;
			mpUnits.erase(mpUnits.begin() + i);
			break;
		}
	}
}

void UnitManager::destroyUnitsOffScreen(Vector2D bounds)
{
	//Check if units position is offscreen and deletes if they are
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		Unit* pTmpUnit = mpUnits[i];

		if ((pTmpUnit->mPos.getX() > bounds.getX() || pTmpUnit->mPos.getX() < 0) ||
			(pTmpUnit->mPos.getY() > bounds.getY() || pTmpUnit->mPos.getY() < 0))
		{
			delete pTmpUnit;
			mpUnits.erase(mpUnits.begin() + i);
			break;
		}
	}
}

void UnitManager::toggleAnimations()
{
	//Toggles if units are animating or not
	if (mUnitsAnimating)
	{
		mUnitsAnimating = false;
	}
	else
	{
		mUnitsAnimating = true;
	}

	//Assigns to all units
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		mpUnits[i]->mIsAnimating = mUnitsAnimating;
	}
}

void UnitManager::toggleCurrentAnimation()
{
	//Changes all units to next animation in each unit
	/*for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		mpUnits[i]->mCurrentAnimation = (mpUnits[i]->mCurrentAnimation + 1) % mpUnits[i]->mAnimations.size();
	}*/

	//Changes last unit to nex animation
	Unit* lastUnit = getLastUnit();

	lastUnit->mCurrentAnimation = (lastUnit->mCurrentAnimation + 1) % lastUnit->mAnimations.size();
}

void UnitManager::update(float dt)
{
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		mpUnits[i]->update(dt);


	}
}

void UnitManager::draw(GraphicsBuffer* destLoc)
{
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		mpUnits[i]->draw(destLoc);
	}
}

Unit* UnitManager::getLastUnit()
{
	if (mpUnits.size() > 0)
	{
		return mpUnits[mpUnits.size() - 1];
	}
	
	return nullptr;
}

int UnitManager::getSize()
{
	return mpUnits.size();
}
