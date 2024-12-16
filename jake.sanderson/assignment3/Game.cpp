#include "Game.h"

#include "Unit.h"
#include "GraphicsBuffer.h"

#include <PerformanceTracker.h>
#include <vector>

//Create global Game object
Game* gpGame;

Game::Game()
{
	mpInputSystem = new InputSystem();
	mpGraphicsSystem = new GraphicsSystem();

	mGameFPS = 60;
	mMSperFrame = MILLISECONDS_PER_SEC / (float)60;

	mIsRunning = true;
}

Game::Game(unsigned int fps)
{
	mpInputSystem = new InputSystem();
	mpGraphicsSystem = new GraphicsSystem();

	mGameFPS = fps;
	mMSperFrame = MILLISECONDS_PER_SEC / (float)fps;

	mIsRunning = true;
}

Game::~Game()
{
	cleanup();
}

bool Game::init(unsigned int width, unsigned int height)
{
	if (!mpGraphicsSystem->init(width, height))
	{
		std::cout << "Graphics System failed to initialize" << std::endl;
		return false;
	}
	if (!mpInputSystem->init())
	{
		std::cout << "Input System failed to initialize" << std::endl;
		return false;
	}
	
	return true;
}

void Game::cleanup()
{
	mpInputSystem->cleanup();
	delete mpInputSystem;
	mpInputSystem = nullptr;

	mpGraphicsSystem->cleanup();
	delete mpGraphicsSystem;
	mpGraphicsSystem = nullptr;
}

void Game::doLoop()
{
	//Strings of file names of background and sprites
	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
	const std::string SMURF_FILENAME = "smurf_sprites.png";
	const std::string FADVENTURER_FILENAME = "kenney_toon-characters\\Female person\\PNG\\Poses\\character_femalePerson_walk";
	const std::string WOODS_FILENAME = "woods.png";

	//Make Graphics buffers
	GraphicsBuffer* pSmurfBuffer = new GraphicsBuffer(ASSET_PATH + SMURF_FILENAME);
	GraphicsBuffer* pWoodsBuffer = new GraphicsBuffer(ASSET_PATH + WOODS_FILENAME);

	//Make Smurf sprite vector
	unsigned int PIXEL_WIDTH = 60;
	unsigned int PIXEL_HEIGHT = 60;
	unsigned int SPRITES_ACROSS = 4;
	unsigned int SPRITES_DOWN = 4;

	std::vector<Sprite> smurfSprites;

	for (unsigned int x = 0; x < SPRITES_ACROSS; x++)
	{
		for (unsigned int y = 0; y < SPRITES_DOWN; y++)
		{
			Sprite spriteNew(pSmurfBuffer, Vector2D((int)(x * PIXEL_WIDTH), (int)(y * PIXEL_HEIGHT)), PIXEL_WIDTH, PIXEL_HEIGHT);
			smurfSprites.push_back(spriteNew);
		}
	}

	//Make female character sprite vector:
	//Make buffers for each png in file
	const unsigned int NUM_FEMALE_FRAMES = 8;

	std::vector<GraphicsBuffer*> femaleWalkBuffers;

	for (unsigned int i = 0; i < NUM_FEMALE_FRAMES; i++)
	{
		femaleWalkBuffers.push_back(new GraphicsBuffer(ASSET_PATH + FADVENTURER_FILENAME + std::to_string(i) + ".png"));
	}

	//Make sprite list
	PIXEL_WIDTH = 96;
	PIXEL_HEIGHT = 128;

	std::vector<Sprite> femaleSprites;

	for (unsigned int i = 0; i < NUM_FEMALE_FRAMES; i++)
	{
		Sprite spriteNew(femaleWalkBuffers[i], Vector2D(0, 0), PIXEL_WIDTH, PIXEL_HEIGHT);
		femaleSprites.push_back(spriteNew);
	}

	//Make Animation pointers
	const int NUM_ANIM = 2;
	int animFPS = 15;
	Animation* smurfWalkAnim = new Animation(animFPS, false, smurfSprites);
	Animation* femaleWalkAnim = new Animation(animFPS, true, femaleSprites);

	std::vector<Animation*> gameAnimList;
	gameAnimList.push_back(smurfWalkAnim);
	gameAnimList.push_back(femaleWalkAnim);

	//Index for current aimation being used
	int currAnimIndex = 0;

	//Make unit
	Unit gameUnit(Vector2D((int)(mpGraphicsSystem->getDisplayWidth() / 2), (int)(mpGraphicsSystem->getDisplayHeight() / 2)), 1.0, gameAnimList);

	//Make timers
	PerformanceTracker gameTracker;
	Timer gameTimer;

	while (mIsRunning)
	{
		//Start timers
		gameTracker.clearTracker("loop");
		gameTracker.startTracking("loop");

		gameTimer.start();

		//Get user input
		mpInputSystem->update();

		//User input logic:
		//If mouse button down move unit to mouse position
		if (mpInputSystem->getMouseState(MOUSE_1))
		{
			gameUnit.setPostition(mpInputSystem->getMousePos());
		}

		//If f key down set animation to 30fps
		if (mpInputSystem->isKeyPressed(F_KEY))
		{
			animFPS = 30;

			gameUnit.setAnimation(currAnimIndex, animFPS);
		}
		//If m key down set animation to 15fps
		if (mpInputSystem->isKeyPressed(M_KEY))
		{
			animFPS = 15;

			gameUnit.setAnimation(currAnimIndex, animFPS);
		}
		//If s key down set animation to 5fps
		if (mpInputSystem->isKeyPressed(S_KEY))
		{
			animFPS = 5;

			gameUnit.setAnimation(currAnimIndex, animFPS);
		}

		//If 1 key down switch to smurf animation
		if (mpInputSystem->isKeyPressed(ONE_KEY))
		{
			currAnimIndex = 0;

			gameUnit.setAnimation(currAnimIndex, animFPS);
		}
		//If 2 key down switch to smurf animation
		if (mpInputSystem->isKeyPressed(TWO_KEY))
		{
			currAnimIndex = 1;

			gameUnit.setAnimation(currAnimIndex, animFPS);
		}

		//If esc key down exit game loop
		if (mpInputSystem->isKeyPressed(ESC_KEY))
		{
			mIsRunning = false;
		}

		//Update unit
		gameUnit.update(mMSperFrame);

		//Take a little nap
		gameTimer.sleepUntilElapsed(mMSperFrame);

		//Print out elapsed time
		gameTracker.stopTracking("loop");
		std::cout << gameTracker.getElapsedTime("loop") << std::endl;

		//Draw screen
		mpGraphicsSystem->getBackBuffer()->draw(Vector2D(0, 0), *pWoodsBuffer);
		gameUnit.draw(mpGraphicsSystem->getBackBuffer());

		mpGraphicsSystem->flip();
	}

	//Delete everything
	delete pSmurfBuffer;
	pSmurfBuffer = nullptr;

	delete pWoodsBuffer;
	pWoodsBuffer = nullptr;

	for (unsigned int i = 0; i < NUM_FEMALE_FRAMES; i++)
	{
		delete femaleWalkBuffers[i];
	}
	femaleWalkBuffers.clear();

	for (unsigned int i = 0; i < NUM_ANIM; i++)
	{
		delete gameAnimList[i];
	}
	gameAnimList.clear();
}
