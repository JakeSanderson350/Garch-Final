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
	MOUSE_CLICK_EVENT,
	CHANGE_UNIT_ANIMATION_SPEED,
	SPAWN_UNIT,
	REMOVE_UNIT,
	UNIT_OFFSCREEN,
	PLAY_SOUND_EVENT,
	MOVE_PADDLE_EVENT,
	STOP_PADDLE_EVENT,
	EMIT_PARTICLE_EVENT,
	GOTO_SETTINGS_EVENT,
	CHANGE_DIFFICULTY_EVENT,
	P1_VICTORY_EVENT,
	P2_VICTORY_EVENT,
	PADDLE_COLLISION,
	SCORE_EVENT,
	LOAD_GAME_EVENT,
	SAVE_GAME_EVENT,
	CREATE_BALL_EVENT,
	CREATE_PADDLE_EVENT,
	CREATE_GOAL_EVENT,
	NUM_GAME_EVENTS
};

class GameEvent : public Event
{
public:
	GameEvent(GameEventTypes eventType);
	~GameEvent();

private:
};

