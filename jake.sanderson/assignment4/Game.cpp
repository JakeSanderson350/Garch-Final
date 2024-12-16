#include "Game.h"

#include "Unit.h"
#include "GraphicsBuffer.h"

#include <PerformanceTracker.h>
#include <vector>

Game* Game::mpsGame = nullptr;

Game::Game()
{
	mGameFPS = 60;
	mMSperFrame = MILLISECONDS_PER_SEC / (float)60;

	mIsRunning = true;
	mIsInitted = false;

	mpInputSystem = nullptr;
	mpGraphicsSystem = nullptr;
	mpGraphicsBufferManager = nullptr;
	mpUnitManager = nullptr;
}

Game::Game(unsigned int fps)
{
	mGameFPS = fps;
	mMSperFrame = MILLISECONDS_PER_SEC / (float)fps;

	mIsRunning = true;
	mIsInitted = false;

	mpInputSystem = nullptr;
	mpGraphicsSystem = nullptr;
	mpGraphicsBufferManager = nullptr;
	mpUnitManager = nullptr;
}

Game::~Game()
{
	cleanup();
}

void Game::createGameInstance()
{
	//If game instance not made make a new one
	if (mpsGame == nullptr)
	{
		mpsGame = new Game();
	}
}

void Game::createGameInstance(unsigned int fps)
{
	//If game instance not made make a new one
	if (mpsGame == nullptr)
	{
		mpsGame = new Game(fps);
	}
}

void Game::destroyGameInstance()
{
	delete mpsGame;
	mpsGame = nullptr;
}

Game* Game::getGameInstance()
{
	//If game instance not made make a new one
	if (mpsGame == nullptr)
	{
		mpsGame = new Game();
	}

	//Returns game instance
	return mpsGame;
}

bool Game::init(unsigned int width, unsigned int height)
{
	//If game already initted cleanup
	if (mIsInitted)
	{
		cleanup();
	}

	//Initialize all game systems/managers
	//If any fail output error message and return false
	mpInputSystem = new InputSystem();
	mpGraphicsSystem = new GraphicsSystem();
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpUnitManager = new UnitManager();

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
	if (!mpGraphicsBufferManager->init())
	{
		std::cout << "Graphics Buffer Manager failed to initialize" << std::endl;
		return false;
	}
	if (!mpUnitManager->init())
	{
		std::cout << "Unit Manager failed to initialize" << std::endl;
		return false;
	}

	mIsInitted = true;
	
	return true;
}

void Game::cleanup()
{
	//Destroy all systems/managers
	mpInputSystem->cleanup();
	delete mpInputSystem;
	mpInputSystem = nullptr;

	mpGraphicsSystem->cleanup();
	delete mpGraphicsSystem;
	mpGraphicsSystem = nullptr;

	mpGraphicsBufferManager->cleanup();
	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = nullptr;

	mpUnitManager->cleanup();
	delete mpUnitManager;
	mpUnitManager = nullptr;

	//Delete all animations
	for (unsigned int i = 0; i < mGameAnimationList.size(); i++)
	{
		Animation* animationToBeDeleted = mGameAnimationList[i];
		delete animationToBeDeleted;
	}
	mGameAnimationList.clear();

	mIsInitted = false;
}

void Game::doLoop()
{
	//Make graphics buffers
	populateGraphicsBufferManager();

	//Make animations for units
	populateAnimationList();

	//Make timers
	PerformanceTracker gameTracker;
	Timer gameTimer;

	//Bounds for deletion
	Vector2D bounds = Vector2D((int)mpGraphicsSystem->getDisplayWidth(), (int)mpGraphicsSystem->getDisplayHeight());

	//Font for unit counter
	Font* font = new Font("..\\..\\shared\\assets\\cour.ttf", 36);

	while (mIsRunning)
	{
		//Start timers
		gameTracker.clearTracker("loop");
		gameTracker.startTracking("loop");

		gameTimer.start();

		//Get user input
		getUserInput();

		//Update unit
		mpUnitManager->update(mMSperFrame);

		//Delete units offscreen
		mpUnitManager->destroyUnitsOffScreen(bounds);

		//Take a little nap
		gameTimer.sleepUntilElapsed(mMSperFrame);

		//Print out elapsed time
		gameTracker.stopTracking("loop");
		std::cout << gameTracker.getElapsedTime("loop") << std::endl;

		//Draw screen
		mpGraphicsSystem->getBackBuffer()->draw(Vector2D(0, 0), *mpGraphicsBufferManager->getBuffer("woodsBuffer"));
		mpGraphicsSystem->getBackBuffer()->writeText(Vector2D(0, 0), *font, Color(255, 255, 255), "Units: " + std::to_string(mpUnitManager->getSize()));
		mpUnitManager->draw(mpGraphicsSystem->getBackBuffer());

		mpGraphicsSystem->flip();
	}

	delete font;
}

void Game::populateGraphicsBufferManager()
{
	//Strings of file names of background and sprites
	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
	const std::string SMURF_FILENAME = "smurf_sprites.png";
	const std::string FADVENTURER_FILENAME = "kenney_toon-characters\\Female person\\PNG\\Poses\\character_femalePerson_walk";
	const std::string WOODS_FILENAME = "woods.png";

	const unsigned int NUM_FEMALE_FRAMES = 8;

	//Add smurf spritesheet and woods background
	mpGraphicsBufferManager->createAndManageBuffer("smurfBuffer", ASSET_PATH + SMURF_FILENAME);
	mpGraphicsBufferManager->createAndManageBuffer("woodsBuffer", ASSET_PATH + WOODS_FILENAME);

	//Add female walk animation buffers
	for (unsigned int i = 0; i < NUM_FEMALE_FRAMES; i++)
	{
		mpGraphicsBufferManager->createAndManageBuffer("femaleWalk" + std::to_string(i) + "Buffer", ASSET_PATH + FADVENTURER_FILENAME + std::to_string(i) + ".png");
	}
}

void Game::populateAnimationList()
{
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
			Sprite spriteNew(mpGraphicsBufferManager->getBuffer("smurfBuffer"), Vector2D((int)(x * PIXEL_WIDTH), (int)(y * PIXEL_HEIGHT)), PIXEL_WIDTH, PIXEL_HEIGHT);
			smurfSprites.push_back(spriteNew);
		}
	}

	//Make Female walking sprite list
	const unsigned int NUM_FEMALE_FRAMES = 8;

	PIXEL_WIDTH = 96;
	PIXEL_HEIGHT = 128;

	std::vector<Sprite> femaleSprites;

	for (unsigned int i = 0; i < NUM_FEMALE_FRAMES; i++)
	{
		Sprite spriteNew(mpGraphicsBufferManager->getBuffer("femaleWalk" + std::to_string(i) + "Buffer"), Vector2D(0, 0), PIXEL_WIDTH, PIXEL_HEIGHT);
		femaleSprites.push_back(spriteNew);
	}

	//Make Animation pointers
	int animFPS = 15;
	Animation* smurfWalkAnim = new Animation(animFPS, true, smurfSprites);
	Animation* femaleWalkAnim = new Animation(animFPS, true, femaleSprites);

	//Add to animation list
	mGameAnimationList.push_back(smurfWalkAnim);
	mGameAnimationList.push_back(femaleWalkAnim);
}

void Game::getUserInput()
{
	//Updates keyboard and mouse states
	mpInputSystem->update();

	//User input logic:
	//If mouse button down place unit at mouse position
	//and make it move towards nearest screen edge
	if (mpInputSystem->getMouseState(MOUSE_LEFT))
	{
		int screenWidth = mpGraphicsSystem->getDisplayWidth();
		int screenHeight = mpGraphicsSystem->getDisplayHeight();

		//Unit placed top half
		if (mpInputSystem->getMousePos().getY() <= (screenHeight / 3))
		{
			//Placed top left
			if (mpInputSystem->getMousePos().getX() <= (screenWidth / 3))
			{
				mpUnitManager->createAndAddUnit(mpInputSystem->getMousePos(), Vector2D(-1.5f, -1.5f), mGameAnimationList);
			}
			//Placed top middle
			else if (mpInputSystem->getMousePos().getX() <= (2 * (screenWidth / 3)))
			{
				mpUnitManager->createAndAddUnit(mpInputSystem->getMousePos(), Vector2D(0.0f, -1.5f), mGameAnimationList);
			}
			//Placed top right
			else
			{
				mpUnitManager->createAndAddUnit(mpInputSystem->getMousePos(), Vector2D(1.5f, -1.5f), mGameAnimationList);
			}
		}
		//Unit placed middle screen
		else if (mpInputSystem->getMousePos().getY() <= (2 * (screenHeight / 3)))
		{
			if (mpInputSystem->getMousePos().getX() <= (screenWidth / 2))
			{
				mpUnitManager->createAndAddUnit(mpInputSystem->getMousePos(), Vector2D(-1.5f, 0.0f), mGameAnimationList);
			}
			else
			{
				mpUnitManager->createAndAddUnit(mpInputSystem->getMousePos(), Vector2D(1.5f, 0.0f), mGameAnimationList);
			}
		}
		//Unit placed bottom half
		else
		{
			//Placed bottom left
			if (mpInputSystem->getMousePos().getX() <= (screenWidth / 3))
			{
				mpUnitManager->createAndAddUnit(mpInputSystem->getMousePos(), Vector2D(-1.5f, 1.5f), mGameAnimationList);
			}
			//Placed bottom middle
			else if (mpInputSystem->getMousePos().getX() <= (2 * (screenWidth / 3)))
			{
				mpUnitManager->createAndAddUnit(mpInputSystem->getMousePos(), Vector2D(0.0f, 1.5f), mGameAnimationList);
			}
			//Placed bottom right
			else
			{
				mpUnitManager->createAndAddUnit(mpInputSystem->getMousePos(), Vector2D(1.5f, 1.5f), mGameAnimationList);
			}
		}
	}
	//If right mouse button down delete units on mouse position
	if (mpInputSystem->getMouseState(MOUSE_RIGHT))
	{
		mpUnitManager->destroyUnit(mpInputSystem->getMousePos());
	}

	//If f key down set animation to 30fps
	if (mpInputSystem->isKeyPressed(F_KEY))
	{
		mpUnitManager->getLastUnit()->setAnimation(0, 30);
	}
	//If m key down set animation to 15fps
	if (mpInputSystem->isKeyPressed(M_KEY))
	{
		mpUnitManager->getLastUnit()->setAnimation(0, 15);
	}
	//If s key down set animation to 5fps
	if (mpInputSystem->isKeyPressed(S_KEY))
	{
		mpUnitManager->getLastUnit()->setAnimation(0, 5);
	}

	//If spacebar down toggle animations on all units
	if (mpInputSystem->isKeyPressed(SPACE_KEY))
	{
		mpUnitManager->toggleAnimations();
	}
	//If enter key down switch last placed unit to female walking animation
	if (mpInputSystem->isKeyPressed(ENTER_KEY))
	{
		mpUnitManager->getLastUnit()->setAnimation(1, 15);
	}

	//If esc key down exit game loop
	if (mpInputSystem->isKeyPressed(ESC_KEY))
	{
		mIsRunning = false;
	}
}
