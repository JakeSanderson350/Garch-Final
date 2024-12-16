#include "SoundManager.h"

#include "Event.h"
#include "PlaySoundEvent.h"

SoundManager::SoundManager()
{
	mIsInitted = false;
}

SoundManager::~SoundManager()
{
	cleanup();
}

bool SoundManager::initSoundSubsystem()
{
	//Add game event listeners?
	EventSystem* pEventSystemInstance = EventSystem::getInstance();

	pEventSystemInstance->addListener((EventType)PLAY_SOUND_EVENT, this);

	return Mix_OpenAudio(22050,AUDIO_S16SYS,2,1000) == 0;
}

bool SoundManager::init()
{
	if (!initSoundSubsystem())
	{
		std::cout << "ERROR - Sound subsystem not initted\n";
		return false;
	}

	mIsInitted = true;
	return true;
}

void SoundManager::cleanup()
{
	//Deletes every sample in map
	for (auto iter : mMap)
	{
		Mix_Chunk* pSampleToBeDeleted = iter.second;

		Mix_FreeChunk(pSampleToBeDeleted);
	}

	mMap.clear();

	mIsInitted = false;
}

SoundKey SoundManager::createAndManageSound(const SoundKey& key, const std::string filename)
{
	if (mIsInitted)
	{
		Mix_Chunk* pNewSound = nullptr;

		std::unordered_map<SoundKey, Mix_Chunk*>::iterator iter = mMap.find(key);

		//Checks if sound in map already
		if (iter == mMap.end())
		{
			//Makes new sound using filename
			pNewSound = Mix_LoadWAV(filename.c_str());

			mMap[key] = pNewSound;
		}

		return key;
	}
	else
	{
		std::cout << "ERROR - Sound subsystem not initted\n";
		return "";
	}
}

void SoundManager::deleteSound(const SoundKey& key)
{
	if (mIsInitted)
	{
		std::unordered_map<SoundKey, Mix_Chunk*>::iterator iter = mMap.find(key);

		//Deletes sound with matching key
		if (iter == mMap.end())
		{
			Mix_FreeChunk(iter->second);
			mMap.erase(iter);
		}
	}
	else
	{
		std::cout << "ERROR - Sound subsystem not initted\n";
		return;
	}
}

void SoundManager::playSample(const SoundKey& key, int loop)
{
	if (mIsInitted)
	{
		Mix_PlayChannel(2, mMap[key], loop);
	}
	else
	{
		std::cout << "ERROR - Sound subsystem not initted\n";
		return;
	}
}

void SoundManager::handleEvent(const Event& currentEvent)
{
	EventType currentEventType = currentEvent.getType();

	//ifelse for blue orb destroyed, red orb destroyed, orb switched, game over events
	if (currentEventType == PLAY_SOUND_EVENT)
	{
		const PlaySoundEvent& playSoundEvent = static_cast<const PlaySoundEvent&>(currentEvent);

		playSample(playSoundEvent.getSoundKey(), playSoundEvent.getIsLoop());
	}
}
