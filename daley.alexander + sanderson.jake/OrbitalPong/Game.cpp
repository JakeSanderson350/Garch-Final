#include "Game.h"

#include "Unit.h"
#include "GraphicsBuffer.h"

#include <PerformanceTracker.h>

#include <fstream>

#include "GameEvent.h"
#include "ChangeUnitAnimationSpeedEvent.h"
#include "ChangeUnitCurrentAnimationEvent.h"
#include "MouseClick.h"
#include "PlaySoundEvent.h"
#include "RemoveUnitEvent.h"
#include "SpawnUnitEvent.h"
#include "ChangeDifficultyEvent.h"
#include "UnitOffscreenEvent.h"

#include "MovePaddle.h"
#include "StopPaddle.h"

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
	mpParticleSystem = nullptr;
	mpSoundManager = nullptr;
	mpMenuManager = nullptr;
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
	mpParticleSystem = nullptr;
	mpSoundManager = nullptr;
	mpMenuManager = nullptr;
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
	srand((unsigned)time(NULL));

	//If game already initted cleanup
	if (mIsInitted)
	{
		cleanup();
	}

	//Set bound variables
	GAME_WIDTH = width;
	GAME_HEIGHT = height;

	//Initialize all game systems/managers
	//If any fail output error message and return false
	mpInputSystem = new InputSystem();
	mpInputTranslator = new InputTranslator();
	mpGraphicsSystem = new GraphicsSystem();
	mpGraphicsBufferManager = new GraphicsBufferManager();
	mpUnitManager = new UnitManager();
	mpParticleSystem = new ParticleSystem();
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
	if (!mpSoundManager->init())
	{
		std::cout << "Sound Manager failed to initialize" << std::endl;
		return false;
	}

	const std::string FONT_PATH = "..\\..\\shared\\assets\\cour.ttf";
	if (!mpHUD->init(FONT_PATH, 36))
	{
		std::cout << "HUD failed to initialize" << std::endl;
		return false;
	}

	mpGameFont = new Font(FONT_PATH, 36);

	mpMenuManager = new MenuManager(mScreenDimensions, mpGameFont);
	mpMenuManager->init();

	mLanguageTable = loadLanguage(LANGUAGE_FILES[mLanguageIndex]);
	changeLanguage();

	//Add event listeners
	EventSystem* pEventSystemInstance = EventSystem::getInstance();

	pEventSystemInstance->addListener((EventType)SPAWN_UNIT, this);
	pEventSystemInstance->addListener((EventType)UNIT_OFFSCREEN, this);
	pEventSystemInstance->addListener((EventType)MOUSE_CLICK_EVENT, this);
	pEventSystemInstance->addListener((EventType)START_GAME_EVENT, this);
	pEventSystemInstance->addListener((EventType)GAME_OVER_EVENT, this);
	pEventSystemInstance->addListener((EventType)TOGGLE_PAUSE_GAME_EVENT, this);
	pEventSystemInstance->addListener((EventType)MOVE_PADDLE_EVENT, this);
	pEventSystemInstance->addListener((EventType)STOP_PADDLE_EVENT, this);
	pEventSystemInstance->addListener((EventType)QUIT_GAME_EVENT, this);
	pEventSystemInstance->addListener((EventType)GOTO_SETTINGS_EVENT, this);
	pEventSystemInstance->addListener((EventType)SCORE_EVENT, this);
	pEventSystemInstance->addListener((EventType)CHANGE_DIFFICULTY_EVENT, this);
	pEventSystemInstance->addListener((EventType)P1_VICTORY_EVENT, this);
	pEventSystemInstance->addListener((EventType)P2_VICTORY_EVENT, this);
	pEventSystemInstance->addListener((EventType)PADDLE_COLLISION, this);
	pEventSystemInstance->addListener((EventType)LOAD_GAME_EVENT, this);
	pEventSystemInstance->addListener((EventType)SAVE_GAME_EVENT, this);

	mIsInitted = true;
	
	return true;
}

void Game::cleanup()
{
	//Save game
	saveGameState();

	//Destroy all systems/managers
	delete mpInputSystem;
	mpInputSystem = nullptr;

	delete mpInputTranslator;
	mpInputTranslator = nullptr;

	mpGraphicsBufferManager->cleanup();
	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = nullptr;

	mpUnitManager->cleanup();
	delete mpUnitManager;
	mpUnitManager = nullptr;

	mpParticleSystem->cleanup();
	delete mpParticleSystem;
	mpParticleSystem = nullptr;

	mpSoundManager->cleanup();
	delete mpSoundManager;
	mpSoundManager = nullptr;

	mpMenuManager->cleanup();
	delete mpMenuManager;
	mpMenuManager = nullptr;

	delete mpHUD;
	mpHUD = nullptr;

	delete mpGameFont;
	mpGameFont = nullptr;

	mpGraphicsSystem->cleanup();
	delete mpGraphicsSystem;
	mpGraphicsSystem = nullptr;

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

	//Populate units
	populateUnits();

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
			mpHUD->update(gameTracker.getElapsedTime("loop"), mP1Score, mP2Score);
		}

		//Draw screen
		if (mIsRunning)
		{
			renderGame();
		}
	}
}

void Game::handleEvent(const Event& currentEvent)
{
	EventType currentEventType = currentEvent.getType();

	if (currentEventType == SPAWN_UNIT)
	{
		const SpawnUnitEvent& spawnUnitEvent = static_cast<const SpawnUnitEvent&>(currentEvent);

		mpUnitManager->createAndAddBall(spawnUnitEvent.getSpawnPosition(), spawnUnitEvent.getSpawnVelocity(), mGameAnimationList);
	}

	else if (currentEventType == UNIT_OFFSCREEN)
	{
		const UnitOffscreenEvent& offscreenEvent = static_cast<const UnitOffscreenEvent&>(currentEvent);
		Vector2D tmp = offscreenEvent.getPosition();
		Vector2D offDir(0, 0);

		//4 way if statement to check which screen side the ball went off of
		if (tmp.getX() < 0)  //Left wall
		{
			offDir.setX(-(mStartingSpeed + mAddedSpeed));
		}
		else if (tmp.getX() > GAME_WIDTH)  //Right wall
		{
			offDir.setX(mStartingSpeed + mAddedSpeed);
		}

		if (tmp.getY() < 0)  //Top Wall
		{
			offDir.setY(-(mStartingSpeed + mAddedSpeed));
		}
		else if (tmp.getY() > GAME_HEIGHT)  //Bottom Wall
		{
			offDir.setY(mStartingSpeed + mAddedSpeed);
		}
		mpUnitManager->ballOffscreen(offDir);
	}

	else if (currentEventType == PADDLE_COLLISION)
	{
		EventSystem::getInstance()->fireEvent(PlaySoundEvent(mPaddleSound));
	}

	else if (currentEventType == MOUSE_CLICK_EVENT)
	{
		ButtonType bType;
		bType = mpMenuManager->getButtonClick(static_cast<const MouseClick&>(currentEvent).getPositionClicked());
		
		switch (bType)
		{
		case START_BUTTON:
			EventSystem::getInstance()->fireEvent((EventType)START_GAME_EVENT);
			break;
		case QUIT_BUTTON:
			EventSystem::getInstance()->fireEvent((EventType)QUIT_GAME_EVENT);
			break;
		case PAUSE_BUTTON:
			EventSystem::getInstance()->fireEvent((EventType)TOGGLE_PAUSE_GAME_EVENT);
			break;
		case SETTINGS_BUTTON:
			EventSystem::getInstance()->fireEvent((EventType)GOTO_SETTINGS_EVENT);
			break;
		case DIFFICULTY_BUTTON:
			if (mStartingSpeed >= 5)
			{
				EventSystem::getInstance()->fireEvent(ChangeDifficultyEvent(1));
				mpMenuManager->changeButtonText(DIFFICULTY_BUTTON, mLanguageTable["DIFFICULTY"] + '1');
			}
			else
			{
				EventSystem::getInstance()->fireEvent(ChangeDifficultyEvent(mStartingSpeed + 2));
				mpMenuManager->changeButtonText(DIFFICULTY_BUTTON, mLanguageTable["DIFFICULTY"] + to_string(mStartingSpeed));
			}
			break;
		case SAVE_BUTTON:
			saveGameState();
			break;
		case LOAD_BUTTON:
			readGameValuesFromSaveFile();
			EventSystem::getInstance()->fireEvent((EventType)START_GAME_EVENT);
			break;
		case LANGUAGE_BUTTON:
			mLanguageIndex = (mLanguageIndex + 1) % 3;

			mLanguageTable = loadLanguage(LANGUAGE_FILES[mLanguageIndex]);
			changeLanguage();

			break;
		}
	}

	else if (currentEventType == MOVE_PADDLE_EVENT)
	{
		if (mCurrentGameScreen == PLAY_SCREEN)
		{
			const MovePaddle& movePaddleEvent = static_cast<const MovePaddle&>(currentEvent);

			float deltaRotation = movePaddleEvent.getDeltaRotation();
			int paddleIndex = movePaddleEvent.getPaddleIndex();

			if (deltaRotation > 0)
			{
				mpUnitManager->togglePaddleMove(paddleIndex, true, true);
			}
			else
			{
				mpUnitManager->togglePaddleMove(paddleIndex, false, true);
			}
			
		}
	}

	else if (currentEventType == STOP_PADDLE_EVENT)
	{
		if (mCurrentGameScreen == PLAY_SCREEN)
		{
			const StopPaddle& stopPaddleEvent = static_cast<const StopPaddle&>(currentEvent);

			mpUnitManager->togglePaddleMove(stopPaddleEvent.getPaddleIndex(), false, false);
		}
	}

	else if (currentEventType == GOTO_SETTINGS_EVENT)
	{
		mpMenuManager->switchMenuIndex(3);
	}

	else if (currentEventType == START_GAME_EVENT)
	{
		mpMenuManager->switchMenuIndex(1);
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
		if (mpMenuManager->getActiveMenu() != 2)
		{
			mpMenuManager->switchMenuIndex(2);
			mpUnitManager->setAllUnitsAnimating(false);
		}
		else
		{
			mpMenuManager->switchMenuIndex(1);
			EventSystem::getInstance()->fireEvent((EventType)START_GAME_EVENT);
		}

	}

	else if (currentEventType == QUIT_GAME_EVENT)
	{
		if (mCurrentGameScreen == PAUSE_SCREEN || mCurrentGameScreen == GAME_OVER_SCREEN)
		{
			mIsRunning = false;
		}
		saveGameState();
		mIsRunning = false;
	}

	else if (currentEventType == SCORE_EVENT)
	{
		const ScoreEvent& scoreEvent = static_cast<const ScoreEvent&>(currentEvent);

		if (scoreEvent.PlayerWhoScored() == ScoreEvent::PlayerOne)
		{
			mP1Score += mScoreInc;
			mWhoScored = 1;
		}
		else if (scoreEvent.PlayerWhoScored() == ScoreEvent::PlayerTwo)
		{
			mP2Score += mScoreInc;
			mWhoScored = 2;
		}

		if (mP1Score >= mMaxScore)
		{
			EventSystem::getInstance()->fireEvent((EventType)P1_VICTORY_EVENT);
		}
		else if (mP2Score >= mMaxScore)
		{
			EventSystem::getInstance()->fireEvent((EventType)P2_VICTORY_EVENT);
		}
		else
		{
			resetGame();
			EventSystem::getInstance()->fireEvent(PlaySoundEvent(mScoreSound));
		}
	}

	else if (currentEventType == P1_VICTORY_EVENT)
	{
		p2Won = true;
		resetGame();
		mP1Score = 0;
		mP2Score = 0;
		mpMenuManager->switchMenuIndex(4);
		EventSystem::getInstance()->fireEvent(PlaySoundEvent(mGameOverSound));
	}

	else if (currentEventType == P2_VICTORY_EVENT)
	{
		p2Won = false;
		resetGame();
		mP1Score = 0;
		mP2Score = 0;
		mpMenuManager->switchMenuIndex(4);
		EventSystem::getInstance()->fireEvent(PlaySoundEvent(mGameOverSound));
	}

	else if (currentEventType == CHANGE_DIFFICULTY_EVENT)
	{
		const ChangeDifficultyEvent& changeDifficultyEvent = static_cast<const ChangeDifficultyEvent&>(currentEvent);
		mStartingSpeed = changeDifficultyEvent.getDifficulty();
		incrementDifficulty(true);
	}
}

Vector2D Game::getScreenDimensions()
{
	return mScreenDimensions;
}

std::string Game::getValueFromLanguageTable(const std::string& key)
{
	return mLanguageTable[key];
}

int Game::getPaddleRadius()
{
	return mPaddleRadius;
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

		if (tmpString == "Add Speed Increment:")
		{
			fin >> mAddSpeedIncrement;
		}

		else if (tmpString == "Time Game Difficulty Increments(ms):")
		{
			fin >> mTimeGameDifficultyIncrements;
		}

		else if (tmpString == "Time Game Difficulty Increments(seconds):")
		{
			fin >> mTimeGameDifficultyIncrements;
			mTimeGameDifficultyIncrements *= 1000;
		}

		else if (tmpString == "Game Score:")
		{
			fin >> mP1Score;
			fin >> mP2Score;
		}

		else if (tmpString == "Score Increment:")
		{
			fin >> mScoreInc;
		}

		else if (tmpString == "Default Starting Speed:")
		{
			fin >> mStartingSpeed;
		}

		else if (tmpString == "Difficulty Increment:")
		{
			fin >> mDifficultyIncrement;
		}

		else if (tmpString == "Max Difficulty:")
		{
			fin >> mMaxDifficulty;
		}

		else if (tmpString == "Max Speed:")
		{
			fin >> mMaxSpeed;
		}

		else if (tmpString == "Paddle Radius:")
		{
			fin >> mPaddleRadius;
		}

		else if (tmpString == "Ball Amount:")
		{
			fin >> mNumBalls;
		}

		else if (tmpString == "Paddle Sound File:")
		{
			fin >> mPaddleSoundFile;
			mPaddleSoundFile = ASSET_PATH + mPaddleSoundFile;
		}

		else if (tmpString == "Game Over Sound File:")
		{
			fin >> mGameOverSoundFile;
			mGameOverSoundFile = ASSET_PATH + mGameOverSoundFile;
		}

		else if (tmpString == "Score Sound File:")
		{
			fin >> mScoreSoundFile;
			mScoreSoundFile = ASSET_PATH + mScoreSoundFile;
		}

		else if (tmpString == "Play to:")
		{
			fin >> mMaxScore;
		}
	}
}

void Game::readGameValuesFromSaveFile()
{
	mpUnitManager->cleanup();

	ifstream fin;
	fin.open(SAVE_FILENAME, ios::in);

	if (fin.fail())
	{
		cout << "Failed to open save file";
		exit(1);
	}

	string tmpString;

	getline(fin, tmpString);

	while (tmpString != "Units:")
	{
		getline(fin, tmpString);

		if (tmpString == "Current Score:")
		{
			fin >> mP1Score;
			fin >> mP2Score;
		}
	}

	while (!fin.eof())
	{
		fin >> *mpUnitManager;
	}
}

void Game::saveGameState()
{
	ofstream fout;
	fout.open(SAVE_FILENAME, ios::out);

	if (fout.fail())
	{
		cout << "Failed to open save file";
		exit(1);
	}

	fout << "//////// Game Save Values \\\\\\\\\\\\\\\\" << endl << endl;

	fout << "Current Score:" << endl << mP1Score << " " << mP2Score << endl << endl;

	fout << "Units:" << endl;

	fout << mpUnitManager;

	std::cout << "Game Saved\n";
}

void Game::populateGraphicsBufferManager()
{
	//Strings of file names of background and sprites
	const std::string BALLS_FILENAME = "glowing-balls.png";

	//Add balls spritesheet
	mpGraphicsBufferManager->createAndManageBuffer("ballsBuffer", ASSET_PATH + BALLS_FILENAME);

	//Paddle buffer
	mpGraphicsBufferManager->createAndManageBuffer("wallBuffer", 800, 600, Color(200, 200, 200));

	mpGraphicsBufferManager->createAndManageBuffer("paddle1Buffer", 800, 600, Color(0, 0, 255));
	mpGraphicsBufferManager->createAndManageBuffer("paddle2Buffer", 800, 600, Color(255, 0, 0));

	//Add goal buffers
	mpGraphicsBufferManager->createAndManageBuffer("p1GoalBuffer", 200, 200, Color(200, 0, 0));
	mpGraphicsBufferManager->createAndManageBuffer("p2GoalBuffer", 200, 200, Color(0, 0, 200));

	//Make sprite for particle system and init it
	Sprite* particleSprite = new Sprite(mpGraphicsBufferManager->getBuffer("wallBuffer"), Vector2D(0, 0), 5, 5);
	mpParticleSystem->init(particleSprite);
	delete particleSprite;
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

	//Make player 1 goal sprite vector
	std::vector<Sprite> p1GoalSprites;

	Sprite spriteNew(mpGraphicsBufferManager->getBuffer("p1GoalBuffer"), Vector2D(0, 0), 75, 75);
	p1GoalSprites.push_back(spriteNew);

	//Make player 2 goal sprite vector
	std::vector<Sprite> p2GoalSprites;

	Sprite spriteNew2(mpGraphicsBufferManager->getBuffer("p2GoalBuffer"), Vector2D(0, 0), 75, 75);
	p2GoalSprites.push_back(spriteNew2);

	//Make Animation pointers
	int animFPS = 15;
	Animation* redBallAnim = new Animation(animFPS, true, redBallSprites);
	Animation* blueBallAnim = new Animation(animFPS, true, blueBallSprites);
	Animation* p1GoalAnim = new Animation(animFPS, true, p1GoalSprites);
	Animation* p2GoalAnim = new Animation(animFPS, true, p2GoalSprites);

	//Add to animation list
	mGameAnimationList.push_back(redBallAnim);
	mGameAnimationList.push_back(blueBallAnim);
	mGameAnimationList.push_back(p2GoalAnim);
	mGameAnimationList.push_back(p1GoalAnim);
}

void Game::populateSoundManager()
{
	mPaddleSound = mpSoundManager->createAndManageSound("RedOrbSound", mPaddleSoundFile);
	mGameOverSound = mpSoundManager->createAndManageSound("GameOverSound", mGameOverSoundFile);
	mScoreSound = mpSoundManager->createAndManageSound("ScoreSound", mScoreSoundFile);
}

void Game::populateUnits()
{
	//Make Ball
	for (unsigned int i = 0; i < mNumBalls; i++)
	{
		mpUnitManager->createAndAddBall(Vector2D(400, 300), Vector2D::getVectorInDirection(Unit::degreeToRadians(rand() % 361)), mGameAnimationList);
	}

	//Make Paddles
	Sprite paddle1Sprite(mpGraphicsBufferManager->getBuffer("paddle1Buffer"), Vector2D(0, 0), 20, 75);
	Sprite paddle2Sprite(mpGraphicsBufferManager->getBuffer("paddle2Buffer"), Vector2D(0, 0), 20, 75);
	mpUnitManager->createAndAddPaddle(Vector2D(400, 500), 0, paddle1Sprite);
	mpUnitManager->createAndAddPaddle(Vector2D(400, 505), 0, paddle1Sprite);
	mpUnitManager->createAndAddPaddle(Vector2D(400, 100), 180, paddle2Sprite);
	mpUnitManager->createAndAddPaddle(Vector2D(400, 95), 180, paddle2Sprite);

	//Make walls out of paddles
	Sprite wallsSprite(mpGraphicsBufferManager->getBuffer("wallBuffer"), Vector2D(0, 0), 800, 20);
	mpUnitManager->createAndAddPaddle(Vector2D(400, 0), 90, wallsSprite);//Top wall
	mpUnitManager->createAndAddPaddle(Vector2D(400, 600), 270, wallsSprite);//Bottom wall
	mpUnitManager->createAndAddPaddle(Vector2D(800, 300), 180, wallsSprite);//Right wall
	mpUnitManager->createAndAddPaddle(Vector2D(0, 300), 0, wallsSprite);//Left wall


	//Make Goals
	mpUnitManager->createAndAddGoal(Vector2D(400, 600), Vector2D(1, 0), mGameAnimationList[2]);
	mpUnitManager->createAndAddGoal(Vector2D(400, 0), Vector2D(-1, 0), mGameAnimationList[3]);
}

void Game::updateGame()
{
	if (mpMenuManager->getActiveMenu() == PLAY_SCREEN)
	{
		//Elapsed time
		mGameTimeElapsed += mMSperFrame;

		//Delete units offscreen
		mpUnitManager->destroyUnitsOffScreen(mScreenDimensions);

		//Update unit
		mpUnitManager->update(mMSperFrame, mGameTimeElapsed);
		mpParticleSystem->update();

		//Game Updates

		{
			//Just mGameTimeElapsed % mTimeGameDifficultyIncrements == 0 but with float precision
			bool isTenSeconds = ((mGameTimeElapsed - (float)((int)(mGameTimeElapsed / mTimeGameDifficultyIncrements) * mTimeGameDifficultyIncrements)) == 0.0f);

			if (isTenSeconds)
			{
				incrementDifficulty(false);
			}
		}

		//Update HUD
		mpHUD->update(mMSperFrame, mP1Score, mP2Score);
	}
}

void Game::renderGame()
{
	mpGraphicsSystem->clearRenderer();

	//Background
	mpGraphicsSystem->getBackBuffer()->setToColor(Color(0.0f, 0.0f, 0.0f));

	//mpMenuManager->renderMenu(mpGraphicsSystem->getBackBuffer(), mScreenDimensions, mpUnitManager, mpHUD, mpGameFont, mpParticleSystem);

	switch (mpMenuManager->getActiveMenu())
	{
	case TITLE_SCREEN:
		mpMenuManager->renderMenu(mpGraphicsSystem->getBackBuffer());
		mpGraphicsSystem->getBackBuffer()->writeText(Vector2D(mScreenDimensions.getX() / 2.0f, 10.0f), *mpGameFont, Color(255, 255, 255), mLanguageTable["WELCOME"], Font::Alignment::CENTER);
		break;

	case SETTINGS_SCREEN:
		mpMenuManager->renderMenu(mpGraphicsSystem->getBackBuffer());
		mpGraphicsSystem->getBackBuffer()->writeText(Vector2D(mScreenDimensions.getX() / 2.0f, 10.0f), *mpGameFont, Color(255, 255, 255), mLanguageTable["SETTINGS"], Font::Alignment::CENTER);
		break;

	case PLAY_SCREEN:
		mpMenuManager->renderMenu(mpGraphicsSystem->getBackBuffer());
		mpParticleSystem->draw(mpGraphicsSystem->getBackBuffer());
		mpUnitManager->draw(mpGraphicsSystem->getBackBuffer());
		mpHUD->draw(mpGraphicsSystem->getBackBuffer(), mGameTimeElapsed, mWhoScored);
		break;

	case PAUSE_SCREEN:
		mpUnitManager->draw(mpGraphicsSystem->getBackBuffer());
		mpMenuManager->renderMenu(mpGraphicsSystem->getBackBuffer());
		mpParticleSystem->draw(mpGraphicsSystem->getBackBuffer());
		mpHUD->draw(mpGraphicsSystem->getBackBuffer());

		break;

	case GAME_OVER_SCREEN:
		mpMenuManager->renderMenu(mpGraphicsSystem->getBackBuffer());
		mpParticleSystem->draw(mpGraphicsSystem->getBackBuffer());

		if (p2Won)
		{
			mpGraphicsSystem->getBackBuffer()->writeText(Vector2D(mScreenDimensions.getX() / 2.0f, 10.0f), *mpGameFont, Color(255, 255, 255), "P2 Wins!", Font::Alignment::CENTER);
		}
		else
		{
			mpGraphicsSystem->getBackBuffer()->writeText(Vector2D(mScreenDimensions.getX() / 2.0f, 10.0f), *mpGameFont, Color(255, 255, 255), "P1 Wins!", Font::Alignment::CENTER);
		}
		
		break;
	}

	mpGraphicsSystem->flip();
}

void Game::incrementDifficulty(bool button)
{
	//If not called by a difficulty changing button, add speed to the total ball speed
	if (!button)
	{
		mAddedSpeed += mAddSpeedIncrement;
	}

	//Check if the ball speed is above the maximum, and if it is, set the ball speed to the maximum allotted speed
	if (mAddedSpeed + mStartingSpeed < mMaxSpeed)
	{
		mpUnitManager->setBallSpeed(mStartingSpeed + mAddedSpeed);
	}
	else
	{
		mpUnitManager->setBallSpeed(mMaxSpeed);
	}
}

map<string, string> Game::loadLanguage(const string& filename)
{
	map<string, string> table;

	ifstream fileStream(filename);
	if (fileStream.good())
	{
		while (!fileStream.eof())
		{
			string key;
			string value;
			getline(fileStream, key);
			getline(fileStream, value);
			if (key != "")
			{
				table[key] = value;
			}
		}
	}

	return table;
}

void Game::changeLanguage()
{
	mpMenuManager->changeButtonText(START_BUTTON, mLanguageTable["PLAY"]);
	mpMenuManager->changeButtonText(SETTINGS_BUTTON, mLanguageTable["SETTINGS"]);
	mpMenuManager->changeButtonText(QUIT_BUTTON, mLanguageTable["QUIT"]);
	mpMenuManager->changeButtonText(SAVE_BUTTON, mLanguageTable["SAVE"]);
	mpMenuManager->changeButtonText(LANGUAGE_BUTTON, mLanguageTable["LANGUAGE"]);
	mpMenuManager->changeButtonText(DIFFICULTY_BUTTON, mLanguageTable["DIFFICULTY"] + to_string(mStartingSpeed));
	mpMenuManager->changeButtonText(LOAD_BUTTON, mLanguageTable["LOAD"]);
}

void Game::resetGame()
{
	mpUnitManager->cleanup();
	//readGameValuesFromFile();

	//Reset game specific values
	mGameTimeElapsed = 0.0f;
	mAddedSpeed = 0;
	mpHUD->resetElapsedTime();

	//Refill unit manager
	populateUnits();
}
