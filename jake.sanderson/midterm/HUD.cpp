#include "HUD.h"

#include "GraphicsBuffer.h"
#include "Game.h"

HUD::HUD()
{
	mDisplayDimensions = Vector2D(0, 0);
	mpFont = nullptr;
	mFontSize = 12;
	mTotalElapsedTime = 0.0f;
	mGameScore = 0;
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

void HUD::update(float elapsedTime, int score)
{
	mGameScore = score;
	mTotalElapsedTime += elapsedTime;
	mFPS = MILLISECONDS_PER_SEC / elapsedTime;
}

void HUD::draw(GraphicsBuffer* destLoc)
{
	destLoc->writeText(Vector2D(0, 0), *mpFont, Color(255, 255, 255), "Score: " + std::to_string(mGameScore));
	destLoc->writeText(Vector2D(300, 0), *mpFont, Color(255, 255, 255), "Total Time: " + std::to_string(mTotalElapsedTime / MILLISECONDS_PER_SEC));


	destLoc->writeText(Vector2D(0, (int)(mDisplayDimensions.getY() - 50)), *mpFont, Color(255, 255, 255), "FPS: " + std::to_string(mFPS));
}

void HUD::resetElapsedTime()
{
	mTotalElapsedTime = 0.0f;
}
