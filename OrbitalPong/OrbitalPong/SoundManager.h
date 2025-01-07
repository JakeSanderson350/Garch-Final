#pragma once

#include <string>
#include <unordered_map>

#include <SDL.h>
#include <SDL_mixer.h>

#include <EventListener.h>
#include <EventSystem.h>

typedef std::string SoundKey;

class SoundManager : public EventListener
{
public:
	SoundManager();
	~SoundManager();

	bool init();

	void cleanup();

	SoundKey createAndManageSound(const SoundKey& key, const std::string filename);

	void deleteSound(const SoundKey& key);

	void playSample(const SoundKey& key, int loop);

	void handleEvent(const Event& currentEvent);

private:
	std::unordered_map <SoundKey, Mix_Chunk*> mMap;

	bool mIsInitted;

	bool initSoundSubsystem();
};

