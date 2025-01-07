#include "ChangeDifficultyEvent.h"

ChangeDifficultyEvent::ChangeDifficultyEvent(int difficulty) : GameEvent(CHANGE_DIFFICULTY_EVENT)
{
	mDifficulty = difficulty;
}

ChangeDifficultyEvent::~ChangeDifficultyEvent()
{

}
