#pragma once

#include <Trackable.h>

#include <vector>

#include "InputSystem.h"
#include "GraphicsSystem.h"
#include "GraphicsBufferManager.h"
#include "UnitManager.h"


class Game : public Trackable
{
public:
	static void createGameInstance();
	static void createGameInstance(unsigned int fps);
	static void destroyGameInstance();
	static Game* getGameInstance();

	bool init(unsigned int width, unsigned int height);

	void cleanup();

	void doLoop();

private:
	static Game* mpsGame;

	InputSystem* mpInputSystem;
	GraphicsSystem* mpGraphicsSystem;

	GraphicsBufferManager* mpGraphicsBufferManager;
	UnitManager* mpUnitManager;

	std::vector<Animation*> mGameAnimationList;

	bool mIsRunning;
	bool mIsInitted;

	int mGameFPS;
	float mMSperFrame;

	const int MILLISECONDS_PER_SEC = 1000;

	Game();
	Game(unsigned int fps);

	~Game();

	void populateGraphicsBufferManager();
	void populateAnimationList();
	void getUserInput();
};