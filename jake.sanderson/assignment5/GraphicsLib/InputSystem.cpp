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
	mKeyState = ALLEGRO_KEYBOARD_STATE();
	mMouseState = ALLEGRO_MOUSE_STATE();
	mpEventQueue = nullptr;
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

	mpEventQueue = al_create_event_queue();
	if (mpEventQueue == nullptr)
	{
		std::cout << "error - unable to create event queue" << std::endl;

		return false;
	}
	else
	{
		al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
		al_register_event_source(mpEventQueue, al_get_mouse_event_source());
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

void InputSystem::updateEventQueue()
{
	ALLEGRO_EVENT currentEvent;

	while (al_get_next_event(mpEventQueue, &currentEvent))
	{
		//Fire mouse events
		//When mouse moves
		if (currentEvent.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			Vector2D mousePos(currentEvent.mouse.x, currentEvent.mouse.y);

			EventSystem::getInstance()->fireEvent(MouseEvent(currentEvent.mouse.button, mousePos));

			std::cout << "Mouse location: " << mousePos << std::endl;
		}

		//When mouse button down
		else if (currentEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			Vector2D mousePos(currentEvent.mouse.x, currentEvent.mouse.y);

			EventSystem::getInstance()->fireEvent(MouseDownEvent(currentEvent.mouse.button, mousePos));

			std::cout << "Mouse " << currentEvent.mouse.button << " down at: " << mousePos << std::endl;
		}

		//When mouse button up
		else if (currentEvent.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			Vector2D mousePos(currentEvent.mouse.x, currentEvent.mouse.y);

			EventSystem::getInstance()->fireEvent(MouseUpEvent(currentEvent.mouse.button, mousePos));

			std::cout << "Mouse " << currentEvent.mouse.button << " up at: " << mousePos << std::endl;
		}

		//Fire keyboard events
		//When key down
		else if (currentEvent.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			EventSystem::getInstance()->fireEvent(KeyDownEvent(currentEvent.keyboard.keycode));

			std::cout << currentEvent.keyboard.keycode << " down" << std::endl;
		}

		//When key up
		else if (currentEvent.type == ALLEGRO_EVENT_KEY_UP)
		{
			EventSystem::getInstance()->fireEvent(KeyUpEvent(currentEvent.keyboard.keycode));

			std::cout << currentEvent.keyboard.keycode << " up" << std::endl;
		}
	}
}

bool InputSystem::isKeyPressed(int key)
{
	al_get_keyboard_state(&mKeyState);

	return al_key_down(&mKeyState, key);
}

bool InputSystem::getMouseState(int button)
{
	al_get_mouse_state(&mMouseState);

	return mMouseState.buttons & button;
}

Vector2D InputSystem::getMousePos()
{
	al_get_mouse_state(&mMouseState);
	mMousePos = Vector2D(mMouseState.x, mMouseState.y);

	return mMousePos;
}
