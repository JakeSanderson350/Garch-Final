#pragma once

#include <Trackable.h>
#include <SDL.h>
#include <allegro5/allegro.h>
#include <SDL.h>

#include <Vector2D.h>

enum KeyCodes
{
	A_KEY = SDLK_a,
	D_KEY = SDLK_d,

	SPACE_KEY = SDLK_SPACE,
	ESC_KEY = SDLK_ESCAPE,
	ENTER_KEY = SDLK_KP_ENTER,

	LEFT_KEY = SDLK_LEFT,
	RIGHT_KEY = SDLK_RIGHT,

	ONE_KEY = SDLK_1,
	TWO_KEY = SDLK_2,

	MOUSE_LEFT = SDL_BUTTON_LEFT,
	MOUSE_RIGHT = SDL_BUTTON_RIGHT,
	MOUSE_MIDDLE = SDL_BUTTON_MIDDLE
};

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	bool init();

	void cleanup();

	void update();
	void updateEventQueue();

	//bool isKeyPressed(int key);
	int getKeyState();
	
	//bool getMouseState(int button);
	//int getMouseState();
	Vector2D getMousePos();

private:
	//ALLEGRO_KEYBOARD_STATE mKeyState;
	int mKeyState;
	
	//ALLEGRO_MOUSE_STATE mMouseState;
	Vector2D mMousePos;

	//ALLEGRO_EVENT_QUEUE* mpEventQueue;
};

