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

	void update(float elapsedTime, int p1Score, int p2Score);

	void draw(GraphicsBuffer* destLoc);
	void draw(GraphicsBuffer* destLoc, float gameTime, int whoScored);

	void resetElapsedTime();

private:
	Vector2D mDisplayDimensions;

	Font* mpFont;
	int mFontSize;

	int mGameScore[2];
	float mTotalElapsedTime;
	float mFPS;
};

