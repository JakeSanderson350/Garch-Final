#pragma once

#include <Trackable.h>

#include <Vector2D.h>
#include "Font.h"

class GraphicsBuffer;

class HUD : public Trackable
{
public:
	HUD();
	~HUD();

	bool init(std::string fontFilename, unsigned int fontSize);

	void update(float elapsedTime, int score);

	void draw(GraphicsBuffer* destLoc);

	void resetElapsedTime();

private:
	Vector2D mDisplayDimensions;

	Font* mpFont;
	int mFontSize;

	int mGameScore;
	float mTotalElapsedTime;
	float mFPS;
};

