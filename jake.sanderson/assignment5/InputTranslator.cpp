#include "InputTranslator.h"

#include <EventSystem.h>
#include "InputSystem.h"

#include "InterfaceEvent.h"
#include "KeyDownEvent.h"
#include "KeyUpEvent.h"
#include "MouseDownEvent.h"
#include "MouseUpEvent.h"

#include "GameEvent.h"
#include "ChangeUnitAnimationSpeedEvent.h"
#include "ChangeUnitCurrentAnimationEvent.h"
#include "RemoveUnitEvent.h"
#include "SpawnUnitEvent.h"

InputTranslator::InputTranslator()
{
	EventSystem* pEventSystemInstance = EventSystem::getInstance();

	pEventSystemInstance->addListener((EventType)KEY_DOWN_EVENT, this);
	pEventSystemInstance->addListener((EventType)MOUSE_INPUT_DOWN_EVENT, this);
	pEventSystemInstance->addListener((EventType)MOUSE_INPUT_UP_EVENT, this);
}

InputTranslator::~InputTranslator()
{

}

void InputTranslator::handleEvent(const Event& currentEvent)
{
	std::cout << "input event handled" << std::endl;

	if (currentEvent.getType() == MOUSE_INPUT_DOWN_EVENT)
	{
		const MouseDownEvent& mouseEvent = static_cast<const MouseDownEvent&>(currentEvent);
		std::cout << "mouse event handled" << std::endl;

		switch (mouseEvent.getMouseButtonCode())
		{
		case MOUSE_LEFT:
			EventSystem::getInstance()->fireEvent(SpawnUnitEvent(mouseEvent.getMousePos()));

			std::cout << "Unit spawned at: " << mouseEvent.getMousePos() << std::endl;
			break;
		case MOUSE_RIGHT:
			EventSystem::getInstance()->fireEvent(RemoveUnitEvent(mouseEvent.getMousePos()));

			std::cout << "Unit deleted at: " << mouseEvent.getMousePos() << std::endl;
			break;
		}
	}

	if (currentEvent.getType() == KEY_DOWN_EVENT)
	{
		const KeyDownEvent& keyDownEvent = static_cast<const KeyDownEvent&>(currentEvent);

		switch (keyDownEvent.getKeyCode())
		{
		case F_KEY:
			EventSystem::getInstance()->fireEvent(ChangeUnitAnimationSpeedEvent(30));
			break;

		case M_KEY:
			EventSystem::getInstance()->fireEvent(ChangeUnitAnimationSpeedEvent(15));
			break;

		case S_KEY:
			EventSystem::getInstance()->fireEvent(ChangeUnitAnimationSpeedEvent(5));
			break;

		case SPACE_KEY:
			EventSystem::getInstance()->fireEvent((EventType)TOGGLE_PAUSE_UNIT_ANIMATION);
			break;

		case ENTER_KEY:
			EventSystem::getInstance()->fireEvent((EventType)TOGGLE_UNIT_ANIMATION);
			break;

		case ESC_KEY:
			EventSystem::getInstance()->fireEvent((EventType)QUIT_GAME_EVENT);
			break;
		}
	}
}
