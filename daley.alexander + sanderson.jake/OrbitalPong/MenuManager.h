#pragma once
#include "Menu.h"
#include <Trackable.h>
#include <Vector2D.h>
#include "HUD.h"
#include "Unitmanager.h"

class MenuManager : public Trackable
{
public:
	MenuManager(Vector2D screen, Font* menuFont);
	~MenuManager();

	GameScene getActiveMenu() { return mpMenus[mCurrentMenuIndex]->getScene(); };
	void init();
	void cleanup();
	void renderMenu(GraphicsBuffer* destination);
	void switchMenuIndex(int newIndex) { mCurrentMenuIndex = newIndex; };
	void changeButtonText(ButtonType buttonType, string text);
	ButtonType getButtonClick(Vector2D buttonClick);

private:
	std::vector<Menu*> mpMenus;
	Vector2D mScreenDimensions;
	int mCurrentMenuIndex;

	Font* mpMenuFont;
};

