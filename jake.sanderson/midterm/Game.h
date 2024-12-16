#pragma once

#include <Trackable.h>

#include <vector>

#include "InputSystem.h"
#include "InputTranslator.h"
#include "GraphicsSystem.h"
#include "GraphicsBufferManager.h"
#include "UnitManager.h"
#include "SoundManager.h"
#include "HUD.h"

#include <EventListener.h>
#include <EventSystem.h>

const int MILLISECONDS_PER_SEC = 1000;

enum GameScene
{
	TITLE_SCREEN = 0,
	PLAY_SCREEN,
	PAUSE_SCREEN,
	GAME_OVER_SCREEN
};

class Game : public EventListener
{
public:
	static void createGameInstance();
	static void createGameInstance(std::string gameValuesFilename,unsigned int fps);
	static void destroyGameInstance();
	static Game* getGameInstance();

	bool init(unsigned int width, unsigned int height);

	void cleanup();

	void doLoop();

	void handleEvent(const Event& currentEvent);

	Vector2D getScreenDimensions();

private:
	static Game* mpsGame;

	InputSystem* mpInputSystem;
	InputTranslator* mpInputTranslator;

	GraphicsSystem* mpGraphicsSystem;

	GraphicsBufferManager* mpGraphicsBufferManager;
	UnitManager* mpUnitManager;
	SoundManager* mpSoundManager;

	HUD* mpHUD;
	Font* mpGameFont;

	std::vector<Animation*> mGameAnimationList;

	std::string mBlueOrbSound;
	std::string mRedOrbSound;
	std::string mGameOverSound;
	std::string mOrbSwitchSound;

	bool mIsRunning;
	bool mIsInitted;

	int mGameFPS;
	float mMSperFrame;
	float mGameTimeElapsed;

	Vector2D mScreenDimensions;

	GameScene mCurrentGameScreen;

	//Game variables
	std::string mGameValuesFilename;

	int mLowSpeed = 5;
	int mHighSpeed = 15;
	int mAddedSpeed = 0;
	int mAddSpeedIncrement = 2;

	int mSpawnChance = 2;
	int mSpawnChanceIncrement = 2;

	int mScore = 10;
	int mHighScore;
	int mScoreInc = 1;
	int mScoreDec = -5;

	float mTimeGameDifficultyIncrements = 10000.0f;

	std::string mBlueOrbSoundFile;
	std::string mRedOrbSoundFile;
	std::string mGameOverSoundFile;
	std::string mOrbSwitchSoundFile;;

	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";

	Game();
	Game(std::string gameValuesFilename,unsigned int fps);

	~Game();

	void readGameValuesFromFile();
	void populateGraphicsBufferManager();
	void populateAnimationList();
	void populateSoundManager();

	void updateGame();
	void renderGame();

	void spawnUnit();
	void incrementDifficulty();

	void resetGame();
};