#pragma once

#include <assert.h>

class Game
{
public:
	static Game* getInstance(){ assert(mpGameInstance != nullptr); return mpGameInstance; };
	static void createInstance(){ mpGameInstance = new Game; };
	static void deleteInstance(){ delete mpGameInstance; };
private:
	Game();

	static Game* mpGameInstance;

};