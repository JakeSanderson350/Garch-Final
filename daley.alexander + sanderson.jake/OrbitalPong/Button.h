#pragma once
#include <Font.h>
#include <Color.h>
#include <Sprite.h>
#include <GraphicsBuffer.h>
#include <Vector2D.h>

enum ButtonType
{
	NIL_BUTTON = 0,
	START_BUTTON,
	SETTINGS_BUTTON,
	MENU_BUTTON,
	PAUSE_BUTTON,
	RESUME_BUTTON,
	LOAD_BUTTON,
	SAVE_BUTTON,
	LANGUAGE_BUTTON,
	DIFFICULTY_BUTTON,
	SOUND_TOGGLE_BUTTON,
	QUIT_BUTTON
};

class Button
{
public:
	Button(ButtonType buttonType);
	Button(ButtonType buttonType, std::string buttonText, Color* buttonColor);
	Button(ButtonType buttonType, std::string buttonText, Color* buttonColor, Vector2D position, int width, int height);
	~Button();

	void drawButton(GraphicsBuffer* dest, Font* mFont);
	void cleanup();
	void setText(std::string text) { mButtonText = text; };
	bool isClicked(Vector2D clickLoc);
	ButtonType getButtonType() { return mButtonType; };
	Vector2D getOffset() { return(Vector2D(mWidth / 2, 0)); };

private:
	Color* mButtonColor;
	std::string mButtonText;
	ButtonType mButtonType;
	int mWidth;
	int mHeight;
	Vector2D mPos;
	GraphicsBuffer* mpRectBuffer = nullptr;

};

