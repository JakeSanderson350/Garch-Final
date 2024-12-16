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
			EventSystem::getInstance()->fireEvent(UnitOffscreenEvent(pTmpUnit->mCurrentAnimation == BLUE_ORB_ANIM_INDEX));
			delete pTmpUnit;
			mpUnits.erase(mpUnits.begin() + i);
			break;
		}
	}
}

void UnitManager::setAllUnitsAnimating(bool isAnimating)
{
	//Assigns to all units
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		mpUnits[i]->mIsAnimating = isAnimating;
	}
}

void UnitManager::toggleCurrentAnimation(Unit* pUnit)
{
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		Unit* tmpUnit = mpUnits[i];

		if (tmpUnit == pUnit)
		{
			tmpUnit->toggleCurrentAnimation();
		}
	}
}

void UnitManager::update(float elapsedTime)
{
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		mpUnits[i]->update(elapsedTime);


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

//Returns nullptr if unit not at position
Unit* UnitManager::getUnit(Vector2D position)
{
	int unitWidthOffset, unitHeightOffset;
	Vector2D positionOffset;

	//Finds unit that matches position and deletes it
	for (int i = mpUnits.size() - 1; i >= 0; i--)
	{
		Unit* pTmpUnit = mpUnits[i];

		//Offsets used so sprite has to be clicked near center to be deleted
		unitWidthOffset = pTmpUnit->mAnimations[pTmpUnit->mCurrentAnimation].getCurrentSprite().getWidth();
		unitHeightOffset = pTmpUnit->mAnimations[pTmpUnit->mCurrentAnimation].getCurrentSprite().getHeight();
		positionOffset = position + pTmpUnit->calculateOffset();

		if ((positionOffset.getX() >= pTmpUnit->mPos.getX() && positionOffset.getX() <= pTmpUnit->mPos.getX() + unitWidthOffset) &&
			(positionOffset.getY() >= pTmpUnit->mPos.getY() && positionOffset.getY() <= pTmpUnit->mPos.getY() + unitHeightOffset))
		{
			return pTmpUnit;
			break;
		}
	}

	return nullptr;
}

int UnitManager::getSize()
{
	return mpUnits.size();
}
