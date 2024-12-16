#include "Singleton.h"
#include <cassert>

Singleton* Singleton::mpsInstance = NULL;

Singleton* Singleton::getInstance()
{
	//assert(mpsInstance);
	if (mpsInstance == NULL)
		mpsInstance = new Singleton;
	return mpsInstance;
}

/*void Singleton::destroyInstance()
{ 
	delete mpsInstance; 
	mpsInstance = NULL; 
};

void Singleton::createInstance()
{ 
	if (mpsInstance == NULL)
	{
		mpsInstance = new Singleton;
	}
}*/