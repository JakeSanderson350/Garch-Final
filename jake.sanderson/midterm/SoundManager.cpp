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

bool SoundManager::initSoundSubsystem(int numSamplesToReserve)
{
	//Add game event listeners?
	EventSystem* pEventSystemInstance = EventSystem::getInstance();

	pEventSystemInstance->addListener((EventType)PLAY_SOUND_EVENT, this);

	return al_install_audio() && al_init_acodec_addon() && al_reserve_samples(numSamplesToReserve);
}

bool SoundManager::init(int numSamplesToReserve)
{
	if (!initSoundSubsystem(numSamplesToReserve))
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
		ALLEGRO_SAMPLE* pSampleToBeDeleted = iter.second;

		al_destroy_sample(pSampleToBeDeleted);
	}

	mMap.clear();

	mIsInitted = false;
}

SoundKey SoundManager::createAndManageSound(const SoundKey& key, const std::string filename)
{
	if (mIsInitted)
	{
		ALLEGRO_SAMPLE* pNewSound = nullptr;

		std::unordered_map<SoundKey, ALLEGRO_SAMPLE*>::iterator iter = mMap.find(key);

		//Checks if sound in map already
		if (iter == mMap.end())
		{
			//Makes new sound using filename
			pNewSound = al_load_sample(filename.c_str());

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
		std::unordered_map<SoundKey, ALLEGRO_SAMPLE*>::iterator iter = mMap.find(key);

		//Deletes sound with matching key
		if (iter == mMap.end())
		{
			al_destroy_sample(iter->second);
			mMap.erase(iter);
		}
	}
	else
	{
		std::cout << "ERROR - Sound subsystem not initted\n";
		return;
	}
}

void SoundManager::playSample(const SoundKey& key, bool loop)
{
	if (mIsInitted)
	{
		if (loop)
		{
			al_play_sample(mMap[key], 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.0f, ALLEGRO_PLAYMODE_LOOP, NULL);
		}
		else
		{
			al_play_sample(mMap[key], 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
		}
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
