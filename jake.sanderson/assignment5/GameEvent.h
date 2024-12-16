#pragma once

#include <InterfaceEvent.h>

enum GameEventTypes
{
	QUIT_GAME_EVENT = NUM_INTERFACE_EVENTS,
	TOGGLE_PAUSE_UNIT_ANIMATION,
	TOGGLE_UNIT_ANIMATION,
	CHANGE_UNIT_CURRENT_ANIMATION,
	CHANGE_UNIT_ANIMATION_SPEED,
	SPAWN_UNIT,
	REMOVE_UNIT,
	NUM_GAME_EVENTS
};

class GameEvent : public Event
{
public:
	GameEvent(GameEventTypes eventType);
	~GameEvent();

private:
};

