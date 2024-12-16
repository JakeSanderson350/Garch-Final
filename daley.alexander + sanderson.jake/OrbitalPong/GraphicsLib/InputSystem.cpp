#include "InputSystem.h"

#include <EventSystem.h>
#include "InterfaceEvent.h"
#include "KeyDownEvent.h"
#include "KeyUpEvent.h"
#include "MouseEvent.h"
#include "MouseDownEvent.h"
#include "MouseUpEvent.h"

InputSystem::InputSystem()
{
	//mKeyState = ALLEGRO_KEYBOARD_STATE();
	//mMouseState = ALLEGRO_MOUSE_STATE();
	//mpEventQueue = nullptr;
}

InputSystem::~InputSystem()
{
	cleanup();
}

bool InputSystem::init()
{
	update();

	return true;
}

void InputSystem::cleanup()
{

}

void InputSystem::update()
{
	SDL_GetKeyboardState(&mKeyState);
	int x, y;
	SDL_GetMouseState(&x, &y);
	mMousePos = Vector2D(x, y);
}

void InputSystem::updateEventQueue()
{

	SDL_Event currEvent;
	while (SDL_PollEvent(&currEvent) != 0)
	{
		//Fire mouse events
		//When mouse moves
		if (currEvent.type == SDL_MOUSEMOTION)
		{
			Vector2D mousePos(currEvent.motion.x, currEvent.motion.y);

			EventSystem::getInstance()->fireEvent(MouseEvent(currEvent.button.button, mousePos));

			//std::cout << "Mouse location: " << mousePos << std::endl;
		}

		//When mouse button down
		else if (currEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			Vector2D mousePos(currEvent.button.x, currEvent.button.y);

			EventSystem::getInstance()->fireEvent(MouseDownEvent(currEvent.button.button, mousePos));

			std::cout << "Mouse " << currEvent.button.button << " down at: " << mousePos << std::endl;
		}

		//When mouse button up
		else if (currEvent.type == SDL_MOUSEBUTTONUP)
		{
			Vector2D mousePos(currEvent.button.x, currEvent.button.y);

			EventSystem::getInstance()->fireEvent(MouseUpEvent(currEvent.button.button, mousePos));

			std::cout << "Mouse " << currEvent.button.button << " up at: " << mousePos << std::endl;
		}

		//Fire keyboard events
		//When key down
		if (currEvent.type == SDL_KEYDOWN)
		{
			EventSystem::getInstance()->fireEvent(KeyDownEvent(currEvent.key.keysym.sym));

			std::cout << currEvent.key.keysym.sym << " down" << std::endl;
		}

		//When key up
		else if (currEvent.type == SDL_KEYUP)
		{
			EventSystem::getInstance()->fireEvent(KeyUpEvent(currEvent.key.keysym.sym));

			std::cout << currEvent.key.keysym.sym << " up" << std::endl;
		}
	}

	// SDL Input Event Handling
	/*
	SDL_Event currEvent;
	while (SDL_PollEvent(&currEvent) != 0)
	{
		if (currEvent.type == SDL_KEYDOWN)
		{
			std::cout << currentEvent.keyboard.keycode << " is down" << std::endl;
		}
	}*/
}

/*bool InputSystem::isKeyPressed(int key)
{
	al_get_keyboard_state(&mKeyState);

	return al_key_down(&mKeyState, key);
}*/

int InputSystem::getKeyState()
{
	SDL_GetKeyboardState(&mKeyState);
	return mKeyState;
}

/*bool InputSystem::getMouseState(int button)
{
	al_get_mouse_state(&mMouseState);

	return mMouseState.buttons & button;
}*/

Vector2D InputSystem::getMousePos()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	mMousePos = Vector2D(x, y);

	return mMousePos;
}
