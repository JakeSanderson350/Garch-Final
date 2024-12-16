#include "UnitManager.h"
#include "Game.h"

UnitManager::UnitManager()
{

}

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
	//Goes through every vector of units and deletes each one
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		Unit* pUnit = mpUnits[i];
		delete pUnit;
	}
	mpUnits.clear();

	mpBalls.clear();
	mpPaddles.clear();
	mpGoals.clear();
}

Unit* UnitManager::createAndAddUnit(Vector2D position, Vector2D velocity, Sprite sprite)
{
	Unit* newUnit = new Unit(position, velocity, sprite);

	mpUnits.push_back(newUnit);

	return newUnit;
}

Unit* UnitManager::createAndAddUnit(Vector2D position, Vector2D velocity, Animation* animation)
{
	Unit* newUnit = new Unit(position, velocity, animation);

	mpUnits.push_back(newUnit);

	return newUnit;
}

Unit* UnitManager::createAndAddUnit(Vector2D position, Vector2D velocity, std::vector<Animation*> animations)
{
	Unit* newUnit = new Unit(position, velocity, animations);

	mpUnits.push_back(newUnit);

	return newUnit;
}

Unit* UnitManager::createAndAddBall(Vector2D position, Vector2D velocity, std::vector<Animation*> animations)
{
	Unit* newUnit = new Unit(position, velocity, animations, BALL_UNIT);

	mpUnits.push_back(newUnit);
	mpBalls.push_back(newUnit);

	return newUnit;
}

Unit* UnitManager::createAndAddPaddle(Vector2D position, float rotation, Sprite sprite)
{
	Unit* newUnit = new Unit(position, Vector2D(0.0f, 0.0f), sprite, PADDLE_UNIT);
	newUnit->mRotation = rotation;
	newUnit->mNormal = Vector2D::getVectorInOppositeDirection(Vector2D(cos(Unit::degreeToRadians(rotation)), sin(Unit::degreeToRadians(rotation))));

	mpUnits.push_back(newUnit);
	mpPaddles.push_back(newUnit);
	mPaddleMoves.push_back(false);
	mPaddleDirections.push_back(0.0f);

	return newUnit;
}

Unit* UnitManager::createAndAddGoal(Vector2D position, Vector2D velocity, Animation* animation)
{
	Unit* newUnit = new Unit(position, velocity, animation, GOAL_UNIT);

	mpUnits.push_back(newUnit);
	mpGoals.push_back(newUnit);

	return newUnit;
}

void UnitManager::destroyUnit(Unit* pUnitToBeDestroyed)
{
	//Finds unit that matches pointer and deletes it
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		Unit* pTmpUnit = mpUnits[i];

		if (pTmpUnit == pUnitToBeDestroyed)
		{
			if (mpUnits[i]->mUnitType == DEFAULT_UNIT)
			{
				delete pTmpUnit;
				mpUnits.erase(mpUnits.begin() + i);
			}

			else if (mpUnits[i]->mUnitType == BALL_UNIT)
			{
				for (unsigned int j = 0; j < mpBalls.size(); j++)
				{
					pTmpUnit = mpBalls[j];

					if (pTmpUnit == pUnitToBeDestroyed)
					{
						delete pTmpUnit;
						mpUnits.erase(mpUnits.begin() + i);
						mpBalls.erase(mpBalls.begin() + j);
					}
				}
			}

			else if (mpUnits[i]->mUnitType == PADDLE_UNIT)
			{
				for (unsigned int j = 0; j < mpPaddles.size(); j++)
				{
					pTmpUnit = mpPaddles[j];

					if (pTmpUnit == pUnitToBeDestroyed)
					{
						delete pTmpUnit;
						mpUnits.erase(mpUnits.begin() + i);
						mpPaddles.erase(mpPaddles.begin() + j);
						mPaddleDirections.erase(mPaddleDirections.begin() + j);
						mPaddleMoves.erase(mPaddleMoves.begin() + j);
					}
				}
			}

			else if (mpUnits[i]->mUnitType == GOAL_UNIT)
			{
				for (unsigned int j = 0; j < mpGoals.size(); j++)
				{
					pTmpUnit = mpGoals[j];

					if (pTmpUnit == pUnitToBeDestroyed)
					{
						delete pTmpUnit;
						mpUnits.erase(mpUnits.begin() + i);
						mpGoals.erase(mpGoals.begin() + j);
					}
				}
			}

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
			destroyUnit(pTmpUnit);
			break;
		}
	}
}

void UnitManager::destroyUnitsOffScreen(Vector2D bounds)
{
	//Check if units position is offscreen and fires offscreen event if so
	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		if (mpUnits[i]->mUnitType == GOAL_UNIT)
		{
			return;
		}

		Unit* pTmpUnit = mpUnits[i];

		if ((pTmpUnit->mPos.getX() > bounds.getX() || pTmpUnit->mPos.getX() < 0) ||
			(pTmpUnit->mPos.getY() > bounds.getY() || pTmpUnit->mPos.getY() < 0))
		{
			EventSystem::getInstance()->fireEvent(UnitOffscreenEvent(pTmpUnit->mPos));
			//destroyUnit(pTmpUnit);
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

void UnitManager::update(float elapsedTime, float totalElapsedTime)
{
	mScreenBounds = Game::getGameInstance()->getScreenDimensions();

	for (unsigned int i = 0; i < mpUnits.size(); i++)
	{
		mpUnits[i]->update(elapsedTime);
	}
	updatePaddles();
	updateBalls(totalElapsedTime);
	updateGoals(elapsedTime);
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

void UnitManager::updateBalls(float totalElapsedTime)
{
	for (unsigned int i = 0; i < mpBalls.size(); i++)
	{
		mpBalls[i]->setNormalToVelocity();

		//Check for collision with paddles
		Unit* collision = checkForBallCollsion(mpBalls[i], mpPaddles);

		if (collision != nullptr)
		{
			Vector2D paddleDirection = collision->mNormal;

			//Set ball velocity to new direction calculated with paddle direction and ball velocity
			mpBalls[i]->mVelocity = calcBounceVector(paddleDirection, mpBalls[i]->mVelocity);
			EventSystem::getInstance()->fireEvent((EventType)PADDLE_COLLISION);
		}

		//Check for collision with goals. If a collision occurs, score a point.
		Unit* collision2 = checkForBallCollsion(mpBalls[i], mpGoals);

		if (collision2 != nullptr)
		{
			ScoreEvent::Players scoringPlayer;

			if (collision2 == mpGoals[1])
			{
				scoringPlayer = ScoreEvent::PlayerOne;
			}
			else
			{
				scoringPlayer = ScoreEvent::PlayerTwo;
			}

			EventSystem::getInstance()->fireEvent(ScoreEvent(scoringPlayer));
			mTimeSinceGoal = totalElapsedTime;
		}
	}
}

void UnitManager::updatePaddles()
{
	for (unsigned int i = 0; i < mPaddleMoves.size(); i+=2)
	{
		if (mPaddleMoves[i])
		{
			//Move paddle
			movePaddle(mPaddleDirections[i], i);
		}
	}
}

//After given a vector2d, resets the ball(s) on screen 
void UnitManager::ballOffscreen(Vector2D side)
{
	for (Unit* ball : mpBalls)
	{
		pushBackUnit(side, *ball);
	}
}

void UnitManager::movePaddle(float deltaRotation, int paddleIndex)
{
	if ((unsigned int)paddleIndex < mpPaddles.size())
	{
		Unit* paddle1 = mpPaddles[paddleIndex];
		Unit* paddle2 = mpPaddles[paddleIndex + 1];

		//Use rotation to get position 
		float paddleDegree = paddle1->mRotation + deltaRotation;

		float xDirection = (float)cos(Unit::degreeToRadians(Unit::convertAngle(paddleDegree)));
		float yDirection = (float)sin(Unit::degreeToRadians(Unit::convertAngle(paddleDegree)));

		//set new position
		int paddleRadius = Game::getGameInstance()->getPaddleRadius();
		Vector2D newPos1(xDirection * paddleRadius + mScreenBounds.getX() / 2, yDirection * paddleRadius + mScreenBounds.getY() / 2);
		Vector2D newPos2(xDirection * (paddleRadius + 5) + mScreenBounds.getX() / 2, yDirection * (paddleRadius + 5) + mScreenBounds.getY() / 2);
		paddle1->mPos = newPos1;
		paddle2->mPos = newPos2;

		//set new normals for both paddles
		Vector2D newNorm = Vector2D::getVectorInOppositeDirection(Vector2D(xDirection, yDirection));
		newNorm.normalize();
		paddle1->mNormal = newNorm;
		paddle2->mNormal = Vector2D::getVectorInOppositeDirection(newNorm);

		//Set rotation
		paddle1->mRotation -= deltaRotation;
		paddle2->mRotation -= deltaRotation;
	}
}

void UnitManager::setBallSpeed(float speed)
{
	for (Unit* ball : mpBalls)
	{
		Vector2D temp = ball->mVelocity;
		temp.normalize();
		ball->mVelocity = temp * speed;
	}
}

void UnitManager::togglePaddleMove(int paddleIndex, bool right, bool moving)
{
	mPaddleMoves[paddleIndex] = moving;
	if (!moving)
	{
		mPaddleDirections[paddleIndex] = 0.0f;
		
	}
	else
	{
		if (right)
		{
			mPaddleDirections[paddleIndex] = 2.0f;
		}
		else
		{
			mPaddleDirections[paddleIndex] = -2.0f;
		}
	}
	
}

void UnitManager::updateGoals(float elapsedTime)
{
	int width = Game::getGameInstance()->getScreenDimensions().getX();
	int height = Game::getGameInstance()->getScreenDimensions().getY();

	int goalWidth = 0;
	int goalHeight = 0;

	for (unsigned int i = 0; i < mpGoals.size(); i++)
	{
		goalWidth = mpGoals[i]->mAnimations[mpGoals[i]->mCurrentAnimation].getCurrentSprite().getWidth();
		goalHeight = mpGoals[i]->mAnimations[mpGoals[i]->mCurrentAnimation].getCurrentSprite().getHeight();

		// Move left if the goal is at the top border
		if (mpGoals[i]->mPos.getY() == 0 && mpGoals[i]->mPos.getX() > 0)
		{
			mpGoals[i]->mVelocity = Vector2D(-1, 0);
		}

		//move right if the goal is at the bottom border
		else if (mpGoals[i]->mPos.getY() == height && mpGoals[i]->mPos.getX() < width)
		{
			mpGoals[i]->mVelocity = Vector2D(1, 0);
		}

		//move up if the goal is on the right border
		if (mpGoals[i]->mPos.getX() == width && mpGoals[i]->mPos.getY() > 0)
		{
			mpGoals[i]->mVelocity = Vector2D(0, -1);
		}

		//move down if the goal is on the left border
		if (mpGoals[i]->mPos.getX() == 0 && mpGoals[i]->mPos.getY() < height)
		{
			mpGoals[i]->mVelocity = Vector2D(0, 1);
		}
	}
}

Unit* UnitManager::checkForBallCollsion(Unit* ball, const std::vector<Unit*>& listToBeChecked)
{
	//Check if ball recently collided to prevent multiple collisions
	if (!ball->mJustCollided)
	{
		//Get bounds for ball
		std::vector<Vector2D> ballBounds = calcUnitBounds(ball);

		for (unsigned int i = 0; i < listToBeChecked.size(); i++)
		{
			if (listToBeChecked[i]->mUnitType == PADDLE_UNIT)
			{
				//get bounds for current paddle
				std::vector<Vector2D> paddleBounds = calcUnitBounds(listToBeChecked[i]);

				//check if bounds intersect using Separating Axis Theorem
				//https://github.com/winstxnhdw/2d-separating-axis-theorem/blob/master/main.cpp
				if (SATintersect(ballBounds, paddleBounds))
				{
					cout << "Collision\n";
					ball->mJustCollided = true;
					EventSystem::getInstance()->fireEvent(EmitParticleEvent(10, ball->mPos, listToBeChecked[i]->mNormal));
					EventSystem::getInstance()->fireEvent(EmitParticleEvent(10, ball->mPos, Vector2D::getVectorInOppositeDirection(ball->mNormal)));
					return listToBeChecked[i];
				}
			}

			else if (listToBeChecked[i]->mUnitType == GOAL_UNIT)
			{
				//get bounds for current goal
				std::vector<Vector2D> goalBounds = calcUnitBounds(listToBeChecked[i]);

				//check if bounds intersect using Separating Axis Theorem
				//https://github.com/winstxnhdw/2d-separating-axis-theorem/blob/master/main.cpp
				if (SATintersect(ballBounds, goalBounds))
				{
					cout << "Collision\n";
					ball->mJustCollided = true;
					EventSystem::getInstance()->fireEvent(EmitParticleEvent(10, ball->mPos, Vector2D::getVectorInOppositeDirection(ball->mNormal)));
					return listToBeChecked[i];
				}
			}
		}
	}

	return nullptr;
}

std::vector<Vector2D> UnitManager::calcUnitBounds(Unit* unit)
{
	std::vector<Vector2D> bounds;

	float unitAngle = -1.0f * Unit::degreeToRadians(unit->mRotation); // Multpilied by -1.0f to change roatation of points where (0,0) in bottom left to (0, 0) in top left
	Vector2D unitPosOffset = unit->calculateOffset();
	Vector2D unitCenteredPos = unit->mPos;

	Vector2D topRightPoint;
	topRightPoint.setX(unitCenteredPos.getX() + (unitPosOffset.getX() * sin(unitAngle)) + (unitPosOffset.getY() * cos(unitAngle)));
	topRightPoint.setY(unitCenteredPos.getY() + (unitPosOffset.getX() * cos(unitAngle)) + (unitPosOffset.getY() * sin(unitAngle)));
	bounds.push_back(topRightPoint);

	Vector2D topLeftPoint;
	topLeftPoint.setX(unitCenteredPos.getX() - (unitPosOffset.getX() * sin(unitAngle)) + (unitPosOffset.getY() * cos(unitAngle)));
	topLeftPoint.setY(unitCenteredPos.getY() + (unitPosOffset.getX() * cos(unitAngle)) + (unitPosOffset.getY() * sin(unitAngle)));
	bounds.push_back(topLeftPoint);

	Vector2D bottomLeftPoint;
	bottomLeftPoint.setX(unitCenteredPos.getX() - (unitPosOffset.getX() * sin(unitAngle)) - (unitPosOffset.getY() * cos(unitAngle)));
	bottomLeftPoint.setY(unitCenteredPos.getY() + (unitPosOffset.getX() * cos(unitAngle)) - (unitPosOffset.getY() * sin(unitAngle)));
	bounds.push_back(bottomLeftPoint);

	Vector2D bottomRightPoint;
	bottomRightPoint.setX(unitCenteredPos.getX() + (unitPosOffset.getX() * sin(unitAngle)) - (unitPosOffset.getY() * cos(unitAngle)));
	bottomRightPoint.setY(unitCenteredPos.getY() - (unitPosOffset.getX() * cos(unitAngle)) - (unitPosOffset.getY() * sin(unitAngle)));
	bounds.push_back(bottomRightPoint);

	return bounds;
}

bool UnitManager::SATintersect(const std::vector<Vector2D>& boundsA, const std::vector<Vector2D>& boundsB)
{
	std::vector<float> projectionsListA, projectionsListB;

	//Checks boundsA against boundsB
	for (unsigned int i = 0; i < boundsA.size(); i++)
	{
		Vector2D currentPoint = boundsA[i];
		Vector2D nextPoint = boundsA[(i + 1) % boundsA.size()];

		Vector2D projectionAxis = calcProjectionAxis(currentPoint, nextPoint);

		//compute projections using projection axis
		projectionsListA.clear();
		projectionsListB.clear();

		for (unsigned int j = 0; j < boundsA.size(); j++)
		{
			float projectionA = projectionAxis.dotProduct(boundsA[j]);
			float projectionB = projectionAxis.dotProduct(boundsB[j]);

			projectionsListA.push_back(projectionA);
			projectionsListB.push_back(projectionB);
		}

		//Checks to see if projections overlap
		if (!isOverlapping(projectionsListA, projectionsListB))
		{
			return false;
		}
	}

	//Chacks boundsB against boundsA
	for (unsigned int i = 0; i < boundsB.size(); i++)
	{
		Vector2D currentPoint = boundsB[i];
		Vector2D nextPoint = boundsB[(i + 1) % boundsB.size()];

		Vector2D projectionAxis = calcProjectionAxis(currentPoint, nextPoint);

		//compute projections using projection axis
		projectionsListA.clear();
		projectionsListB.clear();

		for (unsigned int j = 0; j < boundsB.size(); j++)
		{
			float projectionA = projectionAxis.dotProduct(boundsA[j]);
			float projectionB = projectionAxis.dotProduct(boundsB[j]);

			projectionsListA.push_back(projectionA);
			projectionsListB.push_back(projectionB);
		}

		//Checks to see if projections overlap
		if (!isOverlapping(projectionsListA, projectionsListB))
		{
			return false;
		}
	}

	//Return true if every projection overlaps
	return true;
}

Vector2D UnitManager::calcProjectionAxis(const Vector2D& currentPoint, const Vector2D& nextPoint)
{
	Vector2D normalizedAxis;
	normalizedAxis.setX(-1.0f * (nextPoint.getY() - currentPoint.getY()));
	normalizedAxis.setY(nextPoint.getX() - currentPoint.getX());

	normalizedAxis.normalize();

	return normalizedAxis;
}

bool UnitManager::isOverlapping(const std::vector<float>& projectionsListA, const std::vector<float>& projectionsListB)
{
	float maxProjectionA = *std::max_element(projectionsListA.begin(), projectionsListA.end());
	float minProjectionA = *std::min_element(projectionsListA.begin(), projectionsListA.end());
	float maxProjectionB = *std::max_element(projectionsListB.begin(), projectionsListB.end());
	float minProjectionB = *std::min_element(projectionsListB.begin(), projectionsListB.end());

	//True if projection overlaps but doesn't mean bounds intersect yet
	bool isOverlap = !(maxProjectionA < minProjectionB || maxProjectionB < minProjectionA);

	return isOverlap;
}

Vector2D UnitManager::calcBounceVector(Vector2D paddleVector, Vector2D ballVector)
{
	//split ball vector into u perpendicular to paddle vector and w parallel to it
	//https://stackoverflow.com/questions/573084/how-to-calculate-bounce-angle
	Vector2D u = paddleVector * (ballVector.dotProduct(paddleVector) / paddleVector.dotProduct(paddleVector));

	//If y axis is to mellow make it 1 so bounce will go away from object and not get stuck next to it
	if (u.getLength() < 1)
	{
		float scalar = 1 / u.getLength();

		u *= scalar;
	}

	Vector2D w = ballVector - u;

	Vector2D bounceVector = w - u;
	
	return bounceVector;
}

std::ostream& operator<<(std::ostream& out, const UnitManager* unitManager)
{
	for (unsigned int i = 0; i < unitManager->mpUnits.size(); i++)
	{
		out << unitManager->mpUnits[i];
		out << std::endl;
	}

	return out;
}

std::istream& operator>>(std::istream& in, UnitManager& unitManager)
{
	int unitTypeNum;
	in >> unitTypeNum;
	UnitType unitType = (UnitType)unitTypeNum;

	if (unitType == BALL_UNIT)
	{
		std::vector<Animation*> animations = Game::getGameInstance()->getGameAnimationList();

		Unit* newBall = unitManager.createAndAddBall(Vector2D(), Vector2D(), animations);

		in >> *newBall;
	}
	else if (unitType == PADDLE_UNIT)
	{
		if (unitManager.mpPaddles.size() < 2) //Make player 1 paddles
		{
			GraphicsBufferManager* gameBufferManager = Game::getGameInstance()->getGraphicsBufferManager();
			Sprite paddle1Sprite(gameBufferManager->getBuffer("paddle1Buffer"), Vector2D(0, 0), 20, 75);

			Unit* newPaddle = unitManager.createAndAddPaddle(Vector2D(), 0.0f, paddle1Sprite);

			in >> *newPaddle;
		}

		else if (unitManager.mpPaddles.size() < 4) //Make player 2 paddles
		{
			GraphicsBufferManager* gameBufferManager = Game::getGameInstance()->getGraphicsBufferManager();
			Sprite paddle2Sprite(gameBufferManager->getBuffer("paddle2Buffer"), Vector2D(0, 0), 20, 75);

			Unit* newPaddle = unitManager.createAndAddPaddle(Vector2D(), 0.0f, paddle2Sprite);

			in >> *newPaddle;
		}

		else //Make wall paddles
		{
			GraphicsBufferManager* gameBufferManager = Game::getGameInstance()->getGraphicsBufferManager();
			Sprite wallSprite(gameBufferManager->getBuffer("wallBuffer"), Vector2D(0, 0), 800, 20);

			Unit* newPaddle = unitManager.createAndAddPaddle(Vector2D(), 0.0f, wallSprite);

			in >> *newPaddle;
		}
	}
	else if (unitType == GOAL_UNIT)
	{
		std::vector<Animation*> animations = Game::getGameInstance()->getGameAnimationList();

		if (unitManager.mpGoals.size() < 1) //Make goal 1
		{
			Unit* newGoal = unitManager.createAndAddGoal(Vector2D(), Vector2D(), animations[2]);

			in >> *newGoal;
		}

		else // Make goal 2
		{
			Unit* newGoal = unitManager.createAndAddGoal(Vector2D(), Vector2D(), animations[3]);

			in >> *newGoal;
		}
	}

	return in;
}
