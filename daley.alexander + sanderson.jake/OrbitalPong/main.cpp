#define SDL_MAIN_HANDLED
#include <iostream>
#include <cassert>
#include <string>
#include <random>
#include <ctime>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <GraphicsSystem.h>
#include <GraphicsBuffer.h>
#include <Sprite.h>
#include <Color.h>
#include <Font.h>

#include "Game.h"

#include <EventSystem.h>

using namespace std;

int main()
{
	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 600;

	bool worked;

	EventSystem::createInstance();
	EventSystem* pEventSystem = EventSystem::getInstance();

	Game::createGameInstance("GameValues.txt", 60);
	Game* pGame = Game::getGameInstance();

	pEventSystem->init();
	worked = pGame->init(WIDTH, HEIGHT);

	pGame->doLoop();

	Game::destroyGameInstance();
	pGame = nullptr;

	pEventSystem->destroyInstance();
	pEventSystem = nullptr;

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return worked;
}