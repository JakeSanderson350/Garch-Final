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
#include "MouseClick.h"
#include "ChangeDifficultyEvent.h"
#include "RemoveUnitEvent.h"
#include "MovePaddle.h"
#include "StopPaddle.h"
#include "SpawnUnitEvent.h"

InputTranslator::InputTranslator()
{
	EventSystem* pEventSystemInstance = EventSystem::getInstance();

	pEventSystemInstance->addListener((EventType)KEY_DOWN_EVENT, this);
	pEventSystemInstance->addListener((EventType)KEY_UP_EVENT, this);
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
			EventSystem::getInstance()->fireEvent(MouseClick(mouseEvent.getMousePos()));
			break;
		}
	}

	if (currentEvent.getType() == KEY_DOWN_EVENT)
	{
		const KeyDownEvent& keyDownEvent = static_cast<const KeyDownEvent&>(currentEvent);

		switch (keyDownEvent.getKeyCode())
		{
		case A_KEY:
			EventSystem::getInstance()->fireEvent(MovePaddle(2.0f, 2));  //Move first player paddle left
			break;

		case D_KEY:
			EventSystem::getInstance()->fireEvent(MovePaddle(-2.0f, 2));  //Move first player paddle right
			break;

		case LEFT_KEY:
			EventSystem::getInstance()->fireEvent(MovePaddle(2.0f, 0));  //Move second player paddle left
			break;

		case RIGHT_KEY:
			EventSystem::getInstance()->fireEvent(MovePaddle(-2.0f, 0));  //Move second player paddle right
			break;
		}
	}

	if (currentEvent.getType() == KEY_UP_EVENT)
	{
		const KeyUpEvent& keyUpEvent = static_cast<const KeyUpEvent &>(currentEvent);
		switch (keyUpEvent.getKeyCode())
		{
		case A_KEY:
			EventSystem::getInstance()->fireEvent(StopPaddle(2));  //Stop player 1 paddle from moving
			break;
		case D_KEY:
			EventSystem::getInstance()->fireEvent(StopPaddle(2));  //Stop player 1 paddle from moving
			break;
		case LEFT_KEY:
			EventSystem::getInstance()->fireEvent(StopPaddle(0));  //Stop player 2 paddle from moving
			break;
		case RIGHT_KEY:
			EventSystem::getInstance()->fireEvent(StopPaddle(0));  //Stop player 2 paddle from moving
			break;
		}
	}
}
