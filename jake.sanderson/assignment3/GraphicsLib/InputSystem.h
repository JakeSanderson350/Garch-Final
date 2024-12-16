#pragma once

#include "C:\Users\jake.sanderson\Desktop\Game Arch\shared\DeanLib\include\Trackable.h"
#include <allegro5/allegro.h>

#include <Vector2D.h>

enum KeyCodes
{
	F_KEY = ALLEGRO_KEY_F,
	M_KEY = ALLEGRO_KEY_M,
	S_KEY = ALLEGRO_KEY_S,
	ESC_KEY = ALLEGRO_KEY_ESCAPE,
	ONE_KEY = ALLEGRO_KEY_1,
	TWO_KEY = ALLEGRO_KEY_2,
	MOUSE_1 = 1
};

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	bool init();

	void cleanup();

	void update();

	bool isKeyPressed(int key);
	
	bool getMouseState(int button);
	Vector2D getMousePos();

private:
	ALLEGRO_KEYBOARD_STATE mKeyState;
	
	ALLEGRO_MOUSE_STATE mMouseState;
	Vector2D mMousePos;
};

