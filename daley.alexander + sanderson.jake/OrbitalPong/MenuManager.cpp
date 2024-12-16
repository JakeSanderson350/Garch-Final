#include "MenuManager.h"

MenuManager::MenuManager(Vector2D screen, Font* menuFont)
{
	mCurrentMenuIndex = 0;
	mScreenDimensions = screen;

	mpMenuFont = menuFont;
}

MenuManager::~MenuManager()
{
	cleanup();
}

void MenuManager::init()
{
	//populate menu array
	mpMenus.push_back(new Menu((GameScene)TITLE_SCREEN, mScreenDimensions));
	mpMenus.push_back(new Menu((GameScene)PLAY_SCREEN, mScreenDimensions));
	mpMenus.push_back(new Menu((GameScene)PAUSE_SCREEN, mScreenDimensions));
	mpMenus.push_back(new Menu((GameScene)SETTINGS_SCREEN, mScreenDimensions));
	mpMenus.push_back(new Menu((GameScene)GAME_OVER_SCREEN, mScreenDimensions));

	//init all menus
	for (Menu* iMenu : mpMenus)
	{
		iMenu->init();
	}
}

void MenuManager::cleanup()
{
	for (Menu* dMenu : mpMenus)
	{
		dMenu->cleanup();
		delete dMenu;
		dMenu = nullptr;
	}

	mpMenus.clear();
}

void MenuManager::renderMenu(GraphicsBuffer* destination)
{
	mpMenus[mCurrentMenuIndex]->renderScene(destination, mpMenuFont);
}

ButtonType MenuManager::getButtonClick(Vector2D buttonClick)
{
	return(mpMenus[mCurrentMenuIndex]->clickButtons(buttonClick));
}

void MenuManager::changeButtonText(ButtonType buttonType, string text)
{
	for (unsigned int i = 0; i < mpMenus.size(); i++)
	{
		for (Button* b : mpMenus[i]->getButtons())
		{
			if (b->getButtonType() == buttonType)
			{
				b->setText(text);
			}
		}
	}
}