#pragma once

#include "GameEvent.h"

class ScoreEvent : public GameEvent
{
public:
	enum Players
	{
		PlayerOne = 1,
		PlayerTwo = 2
	};

	ScoreEvent(Players scoringPlayer);
	~ScoreEvent();

	Players PlayerWhoScored() const;

private:
	Players mScoringPlayer;
};

