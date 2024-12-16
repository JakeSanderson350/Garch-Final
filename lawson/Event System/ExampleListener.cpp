#include "ExampleListener.h"
#include <EventSystem.h>
#include "GameEvent.h"
#include "MoveEvent.h"
#include "MessageEvent.h"

ExampleListener::ExampleListener()
{
	EventSystem* pEventSystem = EventSystem::getInstance();
	pEventSystem->addListener( (EventType)MOVE_EVENT, this );
	pEventSystem->addListener( (EventType)MESSAGE_EVENT, this);
}

ExampleListener::~ExampleListener()
{
}

void ExampleListener::handleEvent(const Event &theEvent)
{
	cout << endl << "ExampleListener:";
	
	if( theEvent.getType() == MOVE_EVENT )
	{
		const MoveEvent& moveEvent = static_cast<const MoveEvent&>(theEvent);
		cout	<< "\tMove to: " << moveEvent.getLocation() << endl;
	}
	else if( theEvent.getType() == MESSAGE_EVENT)
	{
		const MessageEvent& messageEvent = static_cast<const MessageEvent&>(theEvent);
		cout	<< "\tMessage: " << messageEvent.getString() << endl;
	}
}