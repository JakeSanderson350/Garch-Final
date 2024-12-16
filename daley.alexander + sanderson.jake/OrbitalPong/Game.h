#pragma once
#include <Trackable.h>

#include <vector>

#include "InputSystem.h"
#include "InputTranslator.h"
#include "GraphicsSystem.h"
#include "GraphicsBufferManager.h"
#include "UnitManager.h"
#include "ParticleSystem.h"
#include "SoundManager.h"
#include "HUD.h"
#include "MenuManager.h"

#include <EventListener.h>
#include <EventSystem.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

const int MILLISECONDS_PER_SEC = 1000;
const std::string LANGUAGE_FILES[] = { "English.txt", "Spanish.txt", "Italian.txt" };


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
	std::string getValueFromLanguageTable(const std::string& key);
	int getPaddleRadius();

	//Getters for game load
	std::vector<Animation*> getGameAnimationList() { return mGameAnimationList; };
	GraphicsBufferManager* getGraphicsBufferManager() { return mpGraphicsBufferManager; };

private:
	static Game* mpsGame;

	InputSystem* mpInputSystem;
	InputTranslator* mpInputTranslator;

	GraphicsSystem* mpGraphicsSystem;

	GraphicsBufferManager* mpGraphicsBufferManager;
	UnitManager* mpUnitManager;
	ParticleSystem* mpParticleSystem;
	SoundManager* mpSoundManager;
	MenuManager* mpMenuManager;

	HUD* mpHUD;
	Font* mpGameFont;

	std::vector<Animation*> mGameAnimationList;

	std::map<std::string, std::string> mLanguageTable;
	int mLanguageIndex = 0;

	std::string mPaddleSound;
	std::string mGameOverSound;
	std::string mScoreSound;

	std::string mPaddleSoundFile;
	std::string mGameOverSoundFile;
	std::string mScoreSoundFile;

	bool mIsRunning;
	bool mIsInitted;
	bool p2Won = NULL;
	int mWhoScored = 0;

	int mGameFPS;
	float mMSperFrame;
	float mGameTimeElapsed;

	Vector2D mScreenDimensions;

	GameScene mCurrentGameScreen;

	//Game variables
	std::string mGameValuesFilename;

	int mAddedSpeed = 0;

	int mP1Score = 0;
	int mP2Score = 0;
	int mScoreInc = 1;

	int mStartingSpeed = 1;
	int mDifficultyIncrement = 2;
	int mMaxDifficulty = 5;
	int mMaxSpeed = 7;
	int mMaxScore = 5;
	int mPaddleRadius = 200;
	unsigned int mNumBalls = 1;
	int mAddSpeedIncrement = 1;
	float mTimeGameDifficultyIncrements = 10.0f;
	unsigned int GAME_WIDTH = 800;
	unsigned int GAME_HEIGHT = 600;

	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
	const std::string SAVE_FILENAME = "GameSave.txt";

	Game();
	Game(std::string gameValuesFilename,unsigned int fps);

	~Game();

	void saveGameState();
	void readGameValuesFromFile();
	void readGameValuesFromSaveFile();

	map<string, string> loadLanguage(const string& filename);
	void changeLanguage();

	void populateGraphicsBufferManager();
	void populateAnimationList();
	void populateSoundManager();
	void populateUnits();

	void updateGame();
	void renderGame();

	void incrementDifficulty(bool button);

	void resetGame();
};