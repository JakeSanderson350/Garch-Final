#pragma once

#include "C:\Users\jake.sanderson\Desktop\Game Arch\shared\DeanLib\include\Trackable.h"

#include "Sprite.h"
#include <vector>

class Animation : public Trackable
{
public:
	Animation();
	Animation(float fps, bool loop);
	Animation(float fps, bool loop, std::vector<Sprite> spriteList);

	~Animation();

	void addSprite(Sprite spriteIn);

	void setSpeed(float fps);

	void update(float elapsedTime);

	Sprite getCurrentSprite();

private:
	std::vector<Sprite> mvSpriteList;
	int mCurrentSprite;

	float mAnimFPS;
	
	float mTimePerFrame;
	float mTimeUntilNextFrame;

	bool mLoop;

	const int MILLISECONDS_PER_SEC = 1000;
};

