#pragma once
#include "GameEvent.h"

class PlaySoundEvent : public GameEvent
{
public:
	PlaySoundEvent(string soundKey, bool isLoop = false);
	~PlaySoundEvent();

	string getSoundKey() const;
	bool getIsLoop() const;

private:
	string mSoundKey;
	bool mIsLoop;
};

