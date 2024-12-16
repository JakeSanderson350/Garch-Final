#pragma once

#include <string>
#include <unordered_map>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <EventListener.h>
#include <EventSystem.h>

typedef std::string SoundKey;

class SoundManager : public EventListener
{
public:
	SoundManager();
	~SoundManager();

	bool init(int numSamplesToReserve);

	void cleanup();

	SoundKey createAndManageSound(const SoundKey& key, const std::string filename);

	void deleteSound(const SoundKey& key);

	void playSample(const SoundKey& key, bool loop = false);

	void handleEvent(const Event& currentEvent);

private:
	std::unordered_map <SoundKey, ALLEGRO_SAMPLE*> mMap;

	bool mIsInitted;

	bool initSoundSubsystem(int numSamplesToReserve);
};

