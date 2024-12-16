#include "SoundSystem.h"
#include <EventSystem.h>
#include "MessageEvent.h"

SoundSystem::SoundSystem()
{
	EventSystem::getInstance()->addListener((EventType)MESSAGE_EVENT, this);
}

void SoundSystem::handleEvent(const Event& theEvent)
{
	cout << endl << "SoundSystem: ";

	if (theEvent.getType() == MESSAGE_EVENT)
	{
		cout << "Ding" << endl;
	}
}
