#pragma once

#include "C:\Users\jake.sanderson\Desktop\Game Arch\shared\DeanLib\include\Trackable.h"

#include "InputSystem.h"
#include "GraphicsSystem.h"


class Game : public Trackable
{
public:
	Game();
	Game(unsigned int fps);

	~Game();

	bool init(unsigned int width, unsigned int height);

	void cleanup();

	void doLoop();

private:
	InputSystem* mpInputSystem;
	GraphicsSystem* mpGraphicsSystem;

	bool mIsRunning;

	int mGameFPS;
	float mMSperFrame;

	const int MILLISECONDS_PER_SEC = 1000;
};

//create uninitialized global Game variable
extern Game* gpGame;