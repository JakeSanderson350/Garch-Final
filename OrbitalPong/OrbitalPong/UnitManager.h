#pragma once

#include <Trackable.h>
#include "Unit.h"

#include <EventSystem.h>
#include "UnitOffscreenEvent.h"
#include "EmitParticleEvent.h"
#include "ScoreEvent.h"
#include "GameEvent.h"

#include <vector>

class Animation;

class UnitManager :public Trackable
{
public:
	UnitManager();
	~UnitManager();

	bool init();

	void cleanup();

	Unit* createAndAddUnit(Vector2D position, Vector2D velocity, Sprite sprite);
	Unit* createAndAddUnit(Vector2D position, Vector2D velocity, Animation* animation);
	Unit* createAndAddUnit(Vector2D position, Vector2D velocity, std::vector<Animation*> animations);

	//Game Specific units
	Unit* createAndAddBall(Vector2D position, Vector2D velocity, std::vector<Animation*> animations);
	Unit* createAndAddPaddle(Vector2D position, float rotation, Sprite sprite);
	Unit* createAndAddGoal(Vector2D position, Vector2D velocity, Animation* animation);

	void ballOffscreen(Vector2D side);
	void movePaddle(float deltaRotation, int paddleIndex);
	void setBallSpeed(float speed);
	void destroyUnit(Unit* pUnit);
	void destroyUnit(Vector2D position);
	void destroyUnitsOffScreen(Vector2D bounds);

	void setAllUnitsAnimating(bool isAnimating);
	void toggleCurrentAnimation(Unit* pUnit);
	void togglePaddleMove(int paddleIndex, bool right, bool moving);

	void update(float elapsedTime, float totalElapsedTime);

	void draw(GraphicsBuffer* destLoc);

	Unit* getLastUnit();
	Unit* getUnit(Vector2D position);

	int getSize();

	friend std::ostream& operator<<(std::ostream& out, const UnitManager* unitManager);
	friend std::istream& operator>>(std::istream& in, UnitManager& unitManager);

private:
	std::vector<Unit*> mpUnits;
	
	//Game Specific units
	std::vector<Unit*> mpBalls;

	std::vector<Unit*> mpPaddles;
	std::vector<bool> mPaddleMoves;
	std::vector<float> mPaddleDirections;

	std::vector<Unit*> mpGoals;
	float mScoreCooldown = 2000;	//milliseconds

	Vector2D mScreenBounds;

	//Game specific update
	void updateBalls(float totalElapsedTime);
	void updateGoals(float elapsedTime);
	void updatePaddles();

	//Ball update
	Unit* checkForBallCollsion(Unit* ball, const std::vector<Unit*>& listToBeChecked);
		std::vector<Vector2D> calcUnitBounds(Unit* unit);
		bool SATintersect(const std::vector<Vector2D>& boundsA, const std::vector<Vector2D>& boundsB);
		Vector2D calcProjectionAxis(const Vector2D& currentPoint, const Vector2D& nextPoint);
		bool isOverlapping(const std::vector<float>& projectionsListA, const std::vector<float>& projectionsListB);

	Vector2D calcBounceVector(Vector2D paddleVector, Vector2D ballVector);

	//Timing
	float mTimeSinceGoal = -1 * mScoreCooldown;	//For counting the milliseconds since a goal was scored. Starts negative so the cooldown doesn't take effect until a goal is scored.
};

