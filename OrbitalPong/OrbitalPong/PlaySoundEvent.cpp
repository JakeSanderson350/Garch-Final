#include "PlaySoundEvent.h"

PlaySoundEvent::PlaySoundEvent(string soundKey, bool isLoop) : GameEvent(PLAY_SOUND_EVENT)
{
	mSoundKey = soundKey;
	mIsLoop = isLoop;
}

PlaySoundEvent::~PlaySoundEvent()
{

}

string PlaySoundEvent::getSoundKey() const
{
	return mSoundKey;
}

bool PlaySoundEvent::getIsLoop() const
{
	return mIsLoop;
}
