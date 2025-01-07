#include "ScoreEvent.h"

ScoreEvent::ScoreEvent(Players scoringPlayer) : GameEvent(SCORE_EVENT)
{
	mScoringPlayer = scoringPlayer;
}

ScoreEvent::~ScoreEvent()
{

}

ScoreEvent::Players ScoreEvent::PlayerWhoScored() const
{
	return mScoringPlayer;
}