#pragma once

#include <Trackable.h>
#include <allegro5/allegro.h>

#include <Vector2D.h>

enum KeyCodes
{
	F_KEY = ALLEGRO_KEY_F,
	M_KEY = ALLEGRO_KEY_M,
	S_KEY = ALLEGRO_KEY_S,
	SPACE_KEY = ALLEGRO_KEY_SPACE,
	ESC_KEY = ALLEGRO_KEY_ESCAPE,
	ENTER_KEY = ALLEGRO_KEY_ENTER,
	ONE_KEY = ALLEGRO_KEY_1,
	TWO_KEY = ALLEGRO_KEY_2,

	MOUSE_LEFT = 1,
	MOUSE_RIGHT = 2,
	MOUSE_MIDDLE = 4
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

	bool isKeyPressed(int key);
	
	bool getMouseState(int button);
	Vector2D getMousePos();

private:
	ALLEGRO_KEYBOARD_STATE mKeyState;
	
	ALLEGRO_MOUSE_STATE mMouseState;
	Vector2D mMousePos;

	ALLEGRO_EVENT_QUEUE* mpEventQueue;
};

