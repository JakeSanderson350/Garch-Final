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
	if (currentEvent.getType() == MOUSE_INPUT_DOWN_EVENT)
	{
		const MouseDownEvent& mouseEvent = static_cast<const MouseDownEvent&>(currentEvent);

		switch (mouseEvent.getMouseButtonCode())
		{
		case MOUSE_LEFT:
			EventSystem::getInstance()->fireEvent(ChangeUnitCurrentAnimationEvent(mouseEvent.getMousePos()));
			break;
		}
	}

	if (currentEvent.getType() == KEY_DOWN_EVENT)
	{
		const KeyDownEvent& keyDownEvent = static_cast<const KeyDownEvent&>(currentEvent);

		switch (keyDownEvent.getKeyCode())
		{
		case SPACE_KEY:
			EventSystem::getInstance()->fireEvent((EventType)START_GAME_EVENT);
			break;

		case ESC_KEY:
			EventSystem::getInstance()->fireEvent((EventType)QUIT_GAME_EVENT);
			EventSystem::getInstance()->fireEvent((EventType)TOGGLE_PAUSE_GAME_EVENT);
			break;
		}
	}
}
