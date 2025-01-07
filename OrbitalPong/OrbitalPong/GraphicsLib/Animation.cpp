#include "Animation.h"

Animation::Animation()
{
	mCurrentSprite = 0;

	mAnimFPS = 60;
	mTimePerFrame = 16.7f;
	mTimeUntilNextFrame = 16.7f;

	mLoop = true;
	mIsAnimating = true;
}

Animation::Animation(float fps, bool loop)
{
	mCurrentSprite = 0;

	mAnimFPS = fps;
	mTimePerFrame = MILLISECONDS_PER_SEC / fps;
	mTimeUntilNextFrame = MILLISECONDS_PER_SEC / fps;

	mLoop = loop;
	mIsAnimating = true;
}

Animation::Animation(Sprite sprite) : Animation()
{
	mvSpriteList.push_back(sprite);

	mIsAnimating = false;
}

Animation::Animation(float fps, bool loop, std::vector<Sprite> spriteListIn) : Animation(fps, loop)
{
	for (unsigned int i = 0; i < spriteListIn.size(); i++)
	{
		mvSpriteList.push_back(spriteListIn[i]);
	}
}

Animation::Animation(Animation& animation) : Animation(animation.mAnimFPS, animation.mLoop, animation.mvSpriteList)
{
}

Animation::~Animation()
{
}

void Animation::addSprite(Sprite spriteIn)
{
	mvSpriteList.push_back(spriteIn);
}

void Animation::setSpeed(float fps)
{
	mAnimFPS = fps;
	mTimePerFrame = MILLISECONDS_PER_SEC / fps;
}

void Animation::update(float elapsedTime)
{
	if (mIsAnimating)
	{
		//Subtracts time passed from how long until the sprite switches
		mTimeUntilNextFrame -= elapsedTime;

		//When time until next sprite gets below zero switch the current sprite
		if (mTimeUntilNextFrame <= 0)
		{
			mCurrentSprite++;
			mTimeUntilNextFrame = mTimePerFrame;

			if (mCurrentSprite >= mvSpriteList.size() && mLoop)
			{
				mCurrentSprite = 0;
			}
			else if (mCurrentSprite >= mvSpriteList.size() && !mLoop)
			{
				mCurrentSprite = mvSpriteList.size() - 1;
				mIsAnimating = false;
			}
		}
	}
}

Sprite Animation::getCurrentSprite()
{
	return mvSpriteList[mCurrentSprite];
}
