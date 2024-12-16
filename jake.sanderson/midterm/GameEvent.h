#pragma once

#include "GraphicsLib\InterfaceEvent.h"

enum GameEventTypes
{
	START_GAME_EVENT = NUM_INTERFACE_EVENTS,
	QUIT_GAME_EVENT,
	GAME_OVER_EVENT,
	TOGGLE_PAUSE_GAME_EVENT,
	TOGGLE_PAUSE_UNIT_ANIMATION,
	TOGGLE_UNIT_ANIMATION,
	CHANGE_UNIT_CURRENT_ANIMATION,
	CHANGE_UNIT_ANIMATION_SPEED,
	SPAWN_UNIT,
	REMOVE_UNIT,
	UNIT_OFFSCREEN,
	PLAY_SOUND_EVENT,
	NUM_GAME_EVENTS
};

class GameEvent : public Event
{
public:
	GameEvent(GameEventTypes eventType);
	~GameEvent();

private:
};
