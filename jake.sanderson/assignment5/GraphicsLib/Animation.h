#pragma once

#include <Trackable.h>

#include "Sprite.h"
#include <vector>

class Animation : public Trackable
{
public:
	Animation();
	Animation(float fps, bool loop);
	Animation(float fps, bool loop, std::vector<Sprite> spriteList);
	Animation(Animation& animation);

	~Animation();

	void addSprite(Sprite spriteIn);

	void setSpeed(float fps);

	void update(float elapsedTime);

	Sprite getCurrentSprite();

private:
	std::vector<Sprite> mvSpriteList;
	unsigned int mCurrentSprite;

	float mAnimFPS;
	
	float mTimePerFrame;
	float mTimeUntilNextFrame;

	bool mLoop;
	bool mIsAnimating;

	const int MILLISECONDS_PER_SEC = 1000;
};

