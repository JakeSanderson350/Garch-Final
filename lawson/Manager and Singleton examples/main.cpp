
#include <iostream>
#include <string>

#include <Trackable.h>
#include <MemoryTracker.h>

#include "WidgetManager.h"
#include "Widget.h"
#include "Singleton.h"
#include "UnitManager.h"
#include "Unit.h"

using namespace std;
int main()
{
	//Singleton::createInstance();
	Singleton* ptr = Singleton::getInstance();
	cout << ptr->getString() << " " << ptr->getInt() << endl;
	//Singleton::destroyInstance();

	/*UnitManager unitManager;

	Unit theUnit = unitManager.getUnit();
	//if( pUnit )
	theUnit.setAnimation();

	//Unit* pNewUnit = new Unit;

	*/
	WidgetManager* pWidgetManager = new WidgetManager;

	pWidgetManager->createAndManageWidget( "PI", 3.14f );
	pWidgetManager->createAndManageWidget( "Square Root of 2", 1.414f );
	Widget* pSine = pWidgetManager->createAndManageWidget( "sine of 45", 0.707f );
	pWidgetManager->createAndManageWidget( "tangent of 30", 0.577f );

	//cout << "PI " << pWidgetManager->getWidget("Pi")->getContents() << endl;
	Widget* pWidget = pWidgetManager->getWidget("PI");
	if (pWidget)
		cout << "PI " << pWidget->getContents() << endl;

	pWidgetManager->deleteWidget( pSine );
	pWidgetManager->deleteWidget("tangent of 30");
	pWidgetManager->deleteWidget("dean");

	delete pWidgetManager;
		
	//Singleton::cleanupInstance();
	
	MemoryTracker::getInstance()->reportAllocations(std::cout);
	system("pause");

	return 0;
}