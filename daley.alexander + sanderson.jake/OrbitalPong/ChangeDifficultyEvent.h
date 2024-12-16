#pragma once
#include "GameEvent.h"

class ChangeDifficultyEvent : public GameEvent
{
public:
	ChangeDifficultyEvent(int difficulty);
	~ChangeDifficultyEvent();
	int getDifficulty() const { return mDifficulty; };

private:
	int mDifficulty;

};

