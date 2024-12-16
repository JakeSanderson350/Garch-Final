#include "Game.h"

#include "Unit.h"
#include "GraphicsBuffer.h"

#include <PerformanceTracker.h>

#include <fstream>

#include "GameEvent.h"
#include "ChangeUnitAnimationSpeedEvent.h"
#include "ChangeUnitCurrentAnimationEvent.h"
#include "PlaySoundEvent.h"
#include "RemoveUnitEvent.h"
#include "SpawnUnitEvent.h"
#include "UnitOffscreenEvent.h"

Game* Game::mpsGame = nullptr;

Game::Game()
{
	mGameFPS = 60;
	mMSperFrame = MILLISECONDS_PER_SEC / (float)60;
	mGameTimeElapsed = 0.0f;

	mIsRunning = true;
	mIsInitted = false;

	mpInputSystem = nullptr;
	mpInputTranslator = nullptr;
	mpGraphicsSystem = nullptr;
	mpGraphicsBufferManager = nullptr;
	mpUnitManager = nullptr;
	mpSoundManager = nullptr;
	mpHUD = nullptr;
	mpGameFont = nullptr;

	mCurrentGameScreen = TITLE_SCREEN;
}

Game::Game(std::string gameValuesFilename, unsigned int fps)
{
	mGameFPS = fps;
	mMSperFrame = MILLISECONDS_PER_SEC / (float)fps;
	mGameTimeElapsed = 0.0f;

	mIsRunning = true;
	mIsInitted = false;

	mpInputSystem = nullptr;
	mpInputTranslator = nullptr;
	mpGraphicsSystem = nullptr;
	mpGraphicsBufferManager = nullptr;
	mpUnitManager = nullptr;
	mpSoundManager = nullptr;
	mpHUD = nullptr;
	mpGameFont = nullptr;

	mGameValuesFilename = gameValuesFilename;

	mCurrentGameScreen = TITLE_SCREEN;
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

void Game::createGameInstance(std::string gameValuesFilename, unsigned int fps)
{
	//If game instance not made make a new one
	if (mpsGame == nullptr)
	{
		mpsGame = new Game(gameValuesFilename, fps);
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
	mpInputTranslator = new InputTranslator();
	mpGraphicsSystem = new GraphicsSystem();
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpUnitManager = new UnitManager();
	mpSoundManager = new SoundManager();
	mpHUD = new HUD();

	if (!mpGraphicsSystem->init(width, height))
	{
		std::cout << "Graphics System failed to initialize" << std::endl;
		return false;
	}
	mScreenDimensions = Vector2D((int)mpGraphicsSystem->getDisplayWidth(), (int)mpGraphicsSystem->getDisplayHeight());
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
	if (!mpSoundManager->init(2))
	{
		std::cout << "Sound Manager failed to initialize" << std::endl;
		return false;
	}

	const std::string FONT_PATH = "..\\..\\shared\\assets\\\\cour.ttf";
	if (!mpHUD->init(FONT_PATH, 36))
	{
		std::cout << "HUD failed to initialize" << std::endl;
		return false;
	}

	mpGameFont = new Font(FONT_PATH, 36);

	//Add event listeners
	EventSystem* pEventSystemInstance = EventSystem::getInstance();

	pEventSystemInstance->addListener((EventType)SPAWN_UNIT, this);
	pEventSystemInstance->addListener((EventType)UNIT_OFFSCREEN, this);
	pEventSystemInstance->addListener((EventType)CHANGE_UNIT_CURRENT_ANIMATION, this);
	pEventSystemInstance->addListener((EventType)START_GAME_EVENT, this);
	pEventSystemInstance->addListener((EventType)GAME_OVER_EVENT, this);
	pEventSystemInstance->addListener((EventType)TOGGLE_PAUSE_GAME_EVENT, this);
	pEventSystemInstance->addListener((EventType)QUIT_GAME_EVENT, this);

	mIsInitted = true;
	
	return true;
}

void Game::cleanup()
{
	//Destroy all systems/managers
	delete mpInputSystem;
	mpInputSystem = nullptr;

	delete mpInputTranslator;
	mpInputTranslator = nullptr;

	mpGraphicsSystem->cleanup();
	delete mpGraphicsSystem;
	mpGraphicsSystem = nullptr;

	mpGraphicsBufferManager->cleanup();
	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = nullptr;

	mpUnitManager->cleanup();
	delete mpUnitManager;
	mpUnitManager = nullptr;

	mpSoundManager->cleanup();
	delete mpSoundManager;
	mpSoundManager = nullptr;

	delete mpHUD;
	mpHUD = nullptr;

	delete mpGameFont;
	mpGameFont = nullptr;

	//Delete all animations
	for (unsigned int i = 0; i < mGameAnimationList.size(); i++)
	{
		Animation* animationToBeDeleted = mGameAnimationList[i];
		delete animationToBeDeleted;
	}
	mGameAnimationList.clear();

	mGameTimeElapsed = 0.0f;

	mIsInitted = false;
}

void Game::doLoop()
{
	//Read Data from file
	readGameValuesFromFile();

	//Make graphics buffers
	populateGraphicsBufferManager();

	//Make animations for units
	populateAnimationList();

	//Make Sounds
	populateSoundManager();

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
		mpInputSystem->updateEventQueue();

		updateGame();

		//Take a little nap
		gameTimer.sleepUntilElapsed(mMSperFrame);

		//Print out elapsed time
		gameTracker.stopTracking("loop");
		//std::cout << gameTracker.getElapsedTime("loop") << std::endl;

		//HUD updated here to get more accurate FPS counter
		if (mCurrentGameScreen == PLAY_SCREEN)
		{
			mpHUD->update(gameTracker.getElapsedTime("loop"), mScore);
		}

		//Draw screen
		renderGame();
	}
}

void Game::handleEvent(const Event& currentEvent)
{
	EventType currentEventType = currentEvent.getType();

	if (currentEventType == SPAWN_UNIT)
	{
		const SpawnUnitEvent& spawnUnitEvent = static_cast<const SpawnUnitEvent&>(currentEvent);

		mpUnitManager->createAndAddUnit(spawnUnitEvent.getSpawnPosition(), spawnUnitEvent.getSpawnVelocity(), mGameAnimationList);
	}

	else if (currentEventType == UNIT_OFFSCREEN)
	{
		const UnitOffscreenEvent& unitOffscreenEvent = static_cast<const UnitOffscreenEvent&>(currentEvent);

		int tmpScore = mScore;

		if (unitOffscreenEvent.isUnitBlue())
		{
			mScore += mScoreInc;

			EventSystem::getInstance()->fireEvent(PlaySoundEvent(mBlueOrbSound));
		}
		else
		{
			mScore += mScoreDec;

			EventSystem::getInstance()->fireEvent(PlaySoundEvent(mRedOrbSound));
		}

		if (mScore > mHighScore && mScore > tmpScore)
		{
			mHighScore = mScore;
		}
		else if (mScore <= 0)
		{
			EventSystem::getInstance()->fireEvent((EventType)GAME_OVER_EVENT);
		}
	}

	else if (currentEventType == CHANGE_UNIT_CURRENT_ANIMATION)
	{
		if (mCurrentGameScreen == PLAY_SCREEN)
		{
			const ChangeUnitCurrentAnimationEvent& currentAnimationEvent = static_cast<const ChangeUnitCurrentAnimationEvent&>(currentEvent);

			Unit* unitClicked = mpUnitManager->getUnit(currentAnimationEvent.getPositionClicked());

			if (unitClicked != nullptr)
			{
				mpUnitManager->toggleCurrentAnimation(unitClicked);

				EventSystem::getInstance()->fireEvent(PlaySoundEvent(mOrbSwitchSound));
			}
		}
	}

	else if (currentEventType == START_GAME_EVENT)
	{
		if (mCurrentGameScreen == TITLE_SCREEN || mCurrentGameScreen == PAUSE_SCREEN)
		{
			mCurrentGameScreen = PLAY_SCREEN;

			mpUnitManager->setAllUnitsAnimating(true);
		}

		else if (mCurrentGameScreen == GAME_OVER_SCREEN)
		{
			mCurrentGameScreen = PLAY_SCREEN;

			resetGame();

			mpUnitManager->setAllUnitsAnimating(true);
		}
	}

	else if (currentEventType == GAME_OVER_EVENT)
	{
		if (mCurrentGameScreen == PLAY_SCREEN)
		{
			mCurrentGameScreen = GAME_OVER_SCREEN;

			EventSystem::getInstance()->fireEvent(PlaySoundEvent(mGameOverSound));
		}
	}

	else if (currentEventType == TOGGLE_PAUSE_GAME_EVENT)
	{
		if (mCurrentGameScreen == PLAY_SCREEN)
		{
			mCurrentGameScreen = PAUSE_SCREEN;

			mpUnitManager->setAllUnitsAnimating(false);
		}
	}

	else if (currentEventType == QUIT_GAME_EVENT)
	{
		if (mCurrentGameScreen == PAUSE_SCREEN || mCurrentGameScreen == GAME_OVER_SCREEN)
		{
			mIsRunning = false;
		}
	}
}

Vector2D Game::getScreenDimensions()
{
	return mScreenDimensions;
}

void Game::readGameValuesFromFile()
{
	ifstream fin;
	fin.open(mGameValuesFilename, ios::in);

	if (fin.fail())
	{
		cout << "Failed to open file";
		exit(1);
	}

	string tmpString;

	getline(fin, tmpString);

	while (!fin.eof())
	{
		getline(fin, tmpString);

		if (tmpString == "Orb Low Speed:")
		{
			fin >> mLowSpeed;
		}

		else if (tmpString == "Orb High Speed:")
		{
			fin >> mHighSpeed;
		}

		else if (tmpString == "Orb Starting Added Speed:")
		{
			fin >> mAddedSpeed;
		}

		else if (tmpString == "Orb Add Speed Increment:")
		{
			fin >> mAddSpeedIncrement;
		}

		else if (tmpString == "Orb Starting Spawn Chance:")
		{
			fin >> mSpawnChance;
		}

		else if (tmpString == "Orb Spawn Chance Increment:")
		{
			fin >> mSpawnChanceIncrement;
		}

		else if (tmpString == "Starting Score:")
		{
			fin >> mScore;
		}

		else if (tmpString == "Score Increment:")
		{
			fin >> mScoreInc;
		}

		else if (tmpString == "Score Decrement:")
		{
			fin >> mScoreDec;
		}

		else if (tmpString == "Time Game Difficulty Increments(ms):")
		{
			fin >> mTimeGameDifficultyIncrements;
		}

		else if (tmpString == "Blue Orb Sound File:")
		{
			fin >> mBlueOrbSoundFile;
			mBlueOrbSoundFile = ASSET_PATH + mBlueOrbSoundFile;
		}

		else if (tmpString == "Red Orb Sound File:")
		{
			fin >> mRedOrbSoundFile;
			mRedOrbSoundFile = ASSET_PATH + mRedOrbSoundFile;
		}

		else if (tmpString == "Game Over Sound File:")
		{
			fin >> mGameOverSoundFile;
			mGameOverSoundFile = ASSET_PATH + mGameOverSoundFile;
		}

		else if (tmpString == "Orb Switch Sound File:")
		{
			fin >> mOrbSwitchSoundFile;
			mOrbSwitchSoundFile = ASSET_PATH + mOrbSwitchSoundFile;
		}
	}
}

void Game::populateGraphicsBufferManager()
{
	//Strings of file names of background and sprites
	const std::string BALLS_FILENAME = "glowing-balls.png";

	//Add balls spritesheet
	mpGraphicsBufferManager->createAndManageBuffer("ballsBuffer", ASSET_PATH + BALLS_FILENAME);
}

void Game::populateAnimationList()
{
	//Make ball sprite vector
	unsigned int PIXEL_WIDTH = 32;
	unsigned int PIXEL_HEIGHT = 32;
	unsigned int SPRITES_ACROSS = 6;
	unsigned int SPRITES_DOWN = 2;

	//Make red ball sprite vector
	std::vector<Sprite> redBallSprites;

	for (unsigned int x = 0; x < SPRITES_ACROSS; x++)
	{
		for (unsigned int y = 0; y < SPRITES_DOWN; y++)
		{
			Sprite spriteNew(mpGraphicsBufferManager->getBuffer("ballsBuffer"), Vector2D((int)(x * PIXEL_WIDTH), (int)(y * PIXEL_HEIGHT) + 192), PIXEL_WIDTH, PIXEL_HEIGHT);
			redBallSprites.push_back(spriteNew);
		}
	}

	//Make blue ball sprite vector
	std::vector<Sprite> blueBallSprites;

	for (unsigned int x = 0; x < SPRITES_ACROSS; x++)
	{
		for (unsigned int y = 0; y < SPRITES_DOWN; y++)
		{
			Sprite spriteNew(mpGraphicsBufferManager->getBuffer("ballsBuffer"), Vector2D((int)(x * PIXEL_WIDTH) + 192, (int)(y * PIXEL_HEIGHT) + 192), PIXEL_WIDTH, PIXEL_HEIGHT);
			blueBallSprites.push_back(spriteNew);
		}
	}
	

	//Make Animation pointers
	int animFPS = 15;
	Animation* redBallAnim = new Animation(animFPS, true, redBallSprites);
	Animation* blueBallAnim = new Animation(animFPS, true, blueBallSprites);

	//Add to animation list
	mGameAnimationList.push_back(redBallAnim);
	mGameAnimationList.push_back(blueBallAnim);
}

void Game::populateSoundManager()
{
	mBlueOrbSound = mpSoundManager->createAndManageSound("BlueOrbSound", mBlueOrbSoundFile);
	mRedOrbSound = mpSoundManager->createAndManageSound("RedOrbSound", mRedOrbSoundFile);
	mGameOverSound = mpSoundManager->createAndManageSound("GameOverSound", mGameOverSoundFile);
	mOrbSwitchSound = mpSoundManager->createAndManageSound("OrbSwitchSound", mOrbSwitchSoundFile);
}

void Game::updateGame()
{
	if (mCurrentGameScreen == PLAY_SCREEN)
	{
		//Elapsed time
		mGameTimeElapsed += mMSperFrame;

		//Update unit
		mpUnitManager->update(mMSperFrame);

		//Delete units offscreen
		mpUnitManager->destroyUnitsOffScreen(mScreenDimensions);

		//Game Updates
		spawnUnit();

		{
			//Just mGameTimeElapsed % mTimeGameDifficultyIncrements == 0 but with float precision
			bool isTenSeconds = ((mGameTimeElapsed - (float)((int)(mGameTimeElapsed / mTimeGameDifficultyIncrements) * mTimeGameDifficultyIncrements)) == 0.0f);

			if (isTenSeconds)
			{
				incrementDifficulty();
			}
		}

		//Update HUD
		//mpHUD->update(mMSperFrame, mScore);
	}
}

void Game::renderGame()
{
	//Background
	mpGraphicsSystem->getBackBuffer()->setToColor(Color(0.0f, 0.0f, 0.0f));

	//Units and HUD
	mpUnitManager->draw(mpGraphicsSystem->getBackBuffer());
	mpHUD->draw(mpGraphicsSystem->getBackBuffer());

	switch (mCurrentGameScreen)
	{
	case TITLE_SCREEN:
		mpGraphicsSystem->getBackBuffer()->writeText(Vector2D(mScreenDimensions.getX() / 2.0f, mScreenDimensions.getY() / 2.0f), *mpGameFont, Color(255, 255, 255), "Click Space to Play", Font::Alignment::CENTER);
		break;

	case PLAY_SCREEN:
		mpUnitManager->draw(mpGraphicsSystem->getBackBuffer());
		mpHUD->draw(mpGraphicsSystem->getBackBuffer());
		break;

	case PAUSE_SCREEN:
		mpUnitManager->draw(mpGraphicsSystem->getBackBuffer());
		mpHUD->draw(mpGraphicsSystem->getBackBuffer());

		mpGraphicsSystem->getBackBuffer()->writeText(Vector2D(mScreenDimensions.getX() / 2.0f, mScreenDimensions.getY() / 2.0f), *mpGameFont, Color(255, 255, 255), "Game Paused", Font::Alignment::CENTER);
		mpGraphicsSystem->getBackBuffer()->writeText(Vector2D(mScreenDimensions.getX() / 2.0f, (mScreenDimensions.getY() / 2.0f) + 50.0f), *mpGameFont, Color(255, 255, 255), "Click Space to Resume", Font::Alignment::CENTER);
		mpGraphicsSystem->getBackBuffer()->writeText(Vector2D(mScreenDimensions.getX() / 2.0f, (mScreenDimensions.getY() / 2.0f) + 100.0f), *mpGameFont, Color(255, 255, 255), "Or Esc To Exit", Font::Alignment::CENTER);		break;

	case GAME_OVER_SCREEN:
		mpUnitManager->draw(mpGraphicsSystem->getBackBuffer());
		mpHUD->draw(mpGraphicsSystem->getBackBuffer());

		mpGraphicsSystem->getBackBuffer()->writeText(Vector2D(mScreenDimensions.getX() / 2.0f, mScreenDimensions.getY() / 2.0f), *mpGameFont, Color(255, 255, 255), "Game Over! Highscore = " + to_string(mHighScore), Font::Alignment::CENTER);
		mpGraphicsSystem->getBackBuffer()->writeText(Vector2D(mScreenDimensions.getX() / 2.0f, (mScreenDimensions.getY() / 2.0f) + 50.0f), *mpGameFont, Color(255, 255, 255), "Click Space to Play Again", Font::Alignment::CENTER);
		mpGraphicsSystem->getBackBuffer()->writeText(Vector2D(mScreenDimensions.getX() / 2.0f, (mScreenDimensions.getY() / 2.0f) + 100.0f), *mpGameFont, Color(255, 255, 255), "Or Esc To Exit", Font::Alignment::CENTER);

		break;
	}

	mpGraphicsSystem->flip();
}

void Game::spawnUnit()
{
	//Makes nothing spawn?
	//srand(time(NULL));

	int spawnChance = (rand() % 100) + 1; // range between 1 to 100

	if (spawnChance <= mSpawnChance)
	{
		//Orb Position
		int xPosition = (rand() % ((2 * ((int)mScreenDimensions.getX() / 3)) - ((int)mScreenDimensions.getX()) + 1)) + ((int)mScreenDimensions.getX() / 3); //range between 1st third of screen to 2nd third of screen
		int yPosition = (rand() % ((2 * ((int)mScreenDimensions.getY() / 3)) - ((int)mScreenDimensions.getY()) + 1)) + ((int)mScreenDimensions.getY() / 3); //range between 1st third of screen to 2nd third of screen

		Vector2D orbPosition(xPosition, yPosition);

		//Orb Velocity
		float xDirection = (rand() % 201) - 100; //range between -100 to 100
		float yDirection = (rand() % 201) - 100; //range between -100 to 100

		//Makes sure velocity isn't (0,0)
		if (xDirection == 0.0f && yDirection == 0.0f)
		{
			xDirection = 1.0f;
		}

		//Normalize direction
		Vector2D orbDirection(xDirection, yDirection);
		orbDirection.normalize();

		//Get speed relative to framerate
		float orbSpeed = (rand() % (mHighSpeed - mLowSpeed + 1)) + mLowSpeed; //range between mLowSpeed to mHighSpeed
		orbSpeed += mAddedSpeed;
		orbSpeed /= mGameFPS;

		Vector2D orbVelocity = orbDirection * orbSpeed;

		//Add new unit
		//mpUnitManager->createAndAddUnit(orbPosition, orbVelocity, mGameAnimationList);
		EventSystem::getInstance()->fireEvent(SpawnUnitEvent(orbPosition, orbVelocity));
	}
}

void Game::incrementDifficulty()
{
	//Speed
	mAddedSpeed += mAddSpeedIncrement;
	cout << "Added Speed = " << mAddedSpeed;

	//Spawn Chance
	mSpawnChance += mSpawnChanceIncrement;
	cout << " Spawn Chance = " << mSpawnChance << endl;
}

void Game::resetGame()
{
	mpUnitManager->cleanup();

	readGameValuesFromFile();

	mGameTimeElapsed = 0.0f;
	mpHUD->resetElapsedTime();
}