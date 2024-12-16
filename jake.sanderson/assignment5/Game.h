#pragma once

#include <Trackable.h>

#include <vector>

#include "InputSystem.h"
#include "InputTranslator.h"
#include "GraphicsSystem.h"
#include "GraphicsBufferManager.h"
#include "UnitManager.h"

#include <EventListener.h>
#include <EventSystem.h>


class Game : public EventListener
{
public:
	static void createGameInstance();
	static void createGameInstance(unsigned int fps);
	static void destroyGameInstance();
	static Game* getGameInstance();

	bool init(unsigned int width, unsigned int height);

	void cleanup();

	void doLoop();

	void handleEvent(const Event& currentEvent);

	

private:
	static Game* mpsGame;

	InputSystem* mpInputSystem;
	InputTranslator* mpInputTranslator;

	GraphicsSystem* mpGraphicsSystem;

	GraphicsBufferManager* mpGraphicsBufferManager;
	UnitManager* mpUnitManager;

	std::vector<Animation*> mGameAnimationList;

	bool mIsRunning;
	bool mIsInitted;

	int mGameFPS;
	float mMSperFrame;

	const int MILLISECONDS_PER_SEC = 1000;

	Vector2D mScreenDimensions;

	Game();
	Game(unsigned int fps);

	~Game();

	void populateGraphicsBufferManager();
	void populateAnimationList();
	void getUserInput();
	void update();

	void spawnUnit();
};