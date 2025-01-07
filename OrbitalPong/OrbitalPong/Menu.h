#pragma once
#include <Trackable.h>
#include "Button.h"
#include "vector"
#include "UnitManager.h"
#include "HUD.h"
#include "ParticleSystem.h"

enum GameScene
{
	TITLE_SCREEN = 0,
	PLAY_SCREEN,
	PAUSE_SCREEN,
	SETTINGS_SCREEN,
	GAME_OVER_SCREEN
};

class Menu : public Trackable
{
public:
	Menu(GameScene menuType, Vector2D screenDimensions);
	~Menu();
	GameScene getScene() {return mMenuType;};
	void init();
	void cleanup();
	std::vector<Button*> getButtons() { return mpButtons; };
	ButtonType clickButtons(Vector2D clickLoc);
	void renderScene(GraphicsBuffer* destination, Font* mpGameFont);

private:
	GameScene mMenuType;
	Vector2D mScreenDimensions;
	std::vector<Button*> mpButtons;

};

