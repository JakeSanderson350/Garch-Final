#include "Menu.h"

Menu::Menu(GameScene menuType, Vector2D screenDimensions)
{
	mMenuType = menuType;
	mScreenDimensions = screenDimensions;
}

Menu::~Menu()
{
	//Free pointers and empty vectors
	cleanup();
}

//Populates vectors with buttons depending on menu type
void Menu::init()
{
	switch (mMenuType)
	{
	case TITLE_SCREEN:
		mpButtons.push_back(new Button((ButtonType)START_BUTTON, "Play", new Color(255, 255, 255),Vector2D((int)(mScreenDimensions.getX()/3.0f), (int)(mScreenDimensions.getY() / 4)),300,50));
		mpButtons.push_back(new Button((ButtonType)SETTINGS_BUTTON, "Settings", new Color(255, 255, 255),Vector2D((int)(mScreenDimensions.getX() / 3.0f), (int)(2*mScreenDimensions.getY() / 4)),300,50));
		mpButtons.push_back(new Button((ButtonType)QUIT_BUTTON, "Quit", new Color(255, 255, 255),Vector2D((int)(mScreenDimensions.getX() / 3.0f), (int)(3 * mScreenDimensions.getY() / 4)),300,50));
		break;

	case PLAY_SCREEN:
		mpButtons.push_back(new Button((ButtonType)PAUSE_BUTTON, "||", new Color(255, 255, 255), Vector2D((int)(9*mScreenDimensions.getX() / 20), (int)(mScreenDimensions.getY() / 50)), 50, 50));
		break;

	case PAUSE_SCREEN:
		mpButtons.push_back(new Button((ButtonType)PAUSE_BUTTON, "||", new Color(255, 255, 255), Vector2D((int)(9 * mScreenDimensions.getX() / 20), (int)(mScreenDimensions.getY() / 50)), 50, 50));
		mpButtons.push_back(new Button((ButtonType)SAVE_BUTTON, "Save", new Color(255, 255, 255), Vector2D((int)(11 * mScreenDimensions.getX() / 30), (int)(6 * mScreenDimensions.getY() / 50)), 200, 50));
		mpButtons.push_back(new Button((ButtonType)QUIT_BUTTON, "Quit", new Color(255, 255, 255), Vector2D((int)(11 * mScreenDimensions.getX() / 30), (int)(16*mScreenDimensions.getY() / 50)), 200, 50));
		mpButtons.push_back(new Button((ButtonType)SETTINGS_BUTTON, "Settings", new Color(255, 255, 255), Vector2D((int)(9 * mScreenDimensions.getX() / 30), (int)(11*mScreenDimensions.getY() / 50)), 300, 50));
		break;

	case SETTINGS_SCREEN:
		mpButtons.push_back(new Button((ButtonType)LANGUAGE_BUTTON, "English", new Color(255, 255, 255), Vector2D((int)(9*mScreenDimensions.getX() / 30), (int)(4 * (mScreenDimensions.getY() / 20))), 300, 50));
		mpButtons.push_back(new Button((ButtonType)START_BUTTON, "Play", new Color(255, 255, 255), Vector2D((int)(11*mScreenDimensions.getX() / 30), (int)(15*(mScreenDimensions.getY() / 20))), 200, 50));
		mpButtons.push_back(new Button((ButtonType)DIFFICULTY_BUTTON, "Start Speed 1", new Color(255, 255, 255), Vector2D((int)(6*mScreenDimensions.getX() / 30), (int)(7 * (mScreenDimensions.getY() / 20))), 450, 50));
		mpButtons.push_back(new Button((ButtonType)LOAD_BUTTON, "Load", new Color(255, 255, 255), Vector2D((int)(11*mScreenDimensions.getX() / 30), (int)(10 * (mScreenDimensions.getY() / 20))), 200, 50));
		break;

	case GAME_OVER_SCREEN:
		mpButtons.push_back(new Button((ButtonType)START_BUTTON, "Play Again", new Color(255, 255, 255), Vector2D((int)(10 * mScreenDimensions.getX() / 30), (int)(5 * (mScreenDimensions.getY() / 20))), 250, 50));
		mpButtons.push_back(new Button((ButtonType)SETTINGS_BUTTON, "Settings", new Color(255, 255, 255), Vector2D((int)(11*mScreenDimensions.getX() / 30), (int)(10 * mScreenDimensions.getY() / 20)), 200, 50));
		mpButtons.push_back(new Button((ButtonType)QUIT_BUTTON, "Quit", new Color(255, 255, 255), Vector2D((int)(11*mScreenDimensions.getX() / 30), (int)(3 * mScreenDimensions.getY() / 4)), 200, 50));
		break;
	}
}

//Empties vectors and destroys objects
void Menu::cleanup()
{
	for (Button* dButton : mpButtons)
	{
		dButton->cleanup();
		delete dButton;
		dButton = nullptr;
	}

	mpButtons.clear();
}

ButtonType Menu::clickButtons(Vector2D clickLoc)
{
	for (Button* cButton : mpButtons)
	{
		if (cButton->isClicked(clickLoc))
		{
			return cButton->getButtonType();
		}
	}
	return NIL_BUTTON;
}

void Menu::renderScene(GraphicsBuffer* destination, Font* mpGameFont)
{
	for (Button* dButton : mpButtons)
	{
		dButton->drawButton(destination, mpGameFont);
	}
}
