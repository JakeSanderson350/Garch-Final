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

using namespace std;

int main()
{
	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 600;

	bool worked;

	gpGame = new Game(60);

	worked = gpGame->init(WIDTH, HEIGHT);

	gpGame->doLoop();

	delete gpGame;
	gpGame = nullptr;

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return worked;
}