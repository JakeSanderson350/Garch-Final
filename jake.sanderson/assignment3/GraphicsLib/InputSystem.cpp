#include "InputSystem.h"

InputSystem::InputSystem()
{
	mKeyState = ALLEGRO_KEYBOARD_STATE();
	mMouseState = ALLEGRO_MOUSE_STATE();
}

InputSystem::~InputSystem()
{
	cleanup();
}

bool InputSystem::init()
{
	if (!al_install_keyboard())
	{
		return false;
	}

	if (!al_install_mouse())
	{
		return false;
	}

	update();

	return true;
}

void InputSystem::cleanup()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();
}

void InputSystem::update()
{
	al_get_keyboard_state(&mKeyState);
	al_get_mouse_state(&mMouseState);
	mMousePos = Vector2D(mMouseState.x, mMouseState.y);
}

bool InputSystem::isKeyPressed(int key)
{
	return al_key_down(&mKeyState, key);
}

bool InputSystem::getMouseState(int button)
{
	return mMouseState.buttons & button;
}

Vector2D InputSystem::getMousePos()
{
	mMousePos = Vector2D(mMouseState.x, mMouseState.y);
	return mMousePos;
}
