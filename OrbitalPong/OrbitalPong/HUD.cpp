#include "HUD.h"

#include "GraphicsBuffer.h"
#include "Game.h"

HUD::HUD()
{
	mDisplayDimensions = Vector2D(0, 0);
	mpFont = nullptr;
	mFontSize = 12;
	mTotalElapsedTime = 0.0f;
	mGameScore[0] = 0;
	mGameScore[1] = 0;
}

HUD::~HUD()
{
	delete mpFont;
	mpFont = nullptr;
}

bool HUD::init(std::string fontFilename, unsigned int fontSize)
{
	mDisplayDimensions = Game::getGameInstance()->getScreenDimensions();

	mpFont = new Font(fontFilename, fontSize);
	mFontSize = fontSize;

	if (mpFont == nullptr)
	{
		return false;
	}
	return true;
}

void HUD::update(float elapsedTime, int p1Score, int p2Score)
{
	mGameScore[0] = p1Score;
	mGameScore[1] = p2Score;
	mTotalElapsedTime += elapsedTime;
	mFPS = MILLISECONDS_PER_SEC / elapsedTime;
}

void HUD::draw(GraphicsBuffer* destLoc)
{
	string scoreStr = Game::getGameInstance()->getValueFromLanguageTable("SCORE");

	destLoc->writeText(Vector2D(0, 0), *mpFont, Color(255, 255, 255), "P1 " + scoreStr + ": " + std::to_string(mGameScore[0]));
	destLoc->writeText(Vector2D(0, 50), *mpFont, Color(255, 255, 255), "P2 " + scoreStr + ": " + std::to_string(mGameScore[1]));

	destLoc->writeText(Vector2D(0, (int)(mDisplayDimensions.getY() - 50)), *mpFont, Color(255, 255, 255), "FPS: " + std::to_string(mFPS));
}

void HUD::draw(GraphicsBuffer* destLoc, float gameTime, int whoScored)
{
	string scoreStr = Game::getGameInstance()->getValueFromLanguageTable("SCORE");

	destLoc->writeText(Vector2D(0, 0), *mpFont, Color(255, 255, 255), "P1 " + scoreStr + ": " + std::to_string(mGameScore[0]));
	destLoc->writeText(Vector2D(0, 50), *mpFont, Color(255, 255, 255), "P2 " + scoreStr + ": " + std::to_string(mGameScore[1]));

	destLoc->writeText(Vector2D(0, (int)(mDisplayDimensions.getY() - 50)), *mpFont, Color(255, 255, 255), "FPS: " + std::to_string(mFPS));

	if (gameTime <= 5000)
	{
		if (whoScored == 1)
		{
			destLoc->writeText(Vector2D(250, 100), *mpFont, Color(255, 255, 255), Game::getGameInstance()->getValueFromLanguageTable("P1SCORE"));
		}
		else if(whoScored == 2)
		{
			destLoc->writeText(Vector2D(250, 100), *mpFont, Color(255, 255, 255), Game::getGameInstance()->getValueFromLanguageTable("P2SCORE"));
		}
	}
}

void HUD::resetElapsedTime()
{
	mTotalElapsedTime = 0.0f;
}
