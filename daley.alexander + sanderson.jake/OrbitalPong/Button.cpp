#include "Button.h"

Button::Button(ButtonType buttonType)
{
	mButtonType = buttonType;
	mButtonText = "";
	mButtonColor = new Color(0, 0, 0);
	mPos = Vector2D(0, 0);
	mWidth = 10;
	mHeight = 10;
	mpRectBuffer = new GraphicsBuffer(mWidth, mHeight, *mButtonColor);
}

Button::Button(ButtonType buttonType, std::string buttonText, Color* buttonColor)
{
	mButtonType = buttonType;
	mButtonText = buttonText;
	mButtonColor = buttonColor;
	mPos = Vector2D(0, 0);
	mWidth = 10;
	mHeight = 10;
	mpRectBuffer = new GraphicsBuffer(mWidth, mHeight, *mButtonColor);
}

Button::Button(ButtonType buttonType, std::string buttonText, Color* buttonColor, Vector2D position, int width, int height)
{
	mButtonType = buttonType;
	mButtonText = buttonText;
	mButtonColor = buttonColor;
	mPos = position;
	mWidth = width;
	mHeight = height;
	mpRectBuffer = new GraphicsBuffer(mWidth, mHeight, *mButtonColor);
}

Button::~Button()
{
	cleanup();
}

void Button::drawButton(GraphicsBuffer* dest, Font* mFont)
{
	Sprite* buttonSprite = new Sprite(mpRectBuffer, Vector2D(0,0), mWidth, mHeight);  //Make new rectangle sprite for button
	buttonSprite->getBuffer()->setToColor(*mButtonColor);
	dest->draw(mPos, *buttonSprite, 0.0, 1.0);
	dest->writeText(mPos + getOffset(), *mFont, Color(0, 0, 0), mButtonText, Font::CENTER);
	delete buttonSprite;
	buttonSprite = nullptr;
}

bool Button::isClicked(Vector2D clickLoc)
{
	if ((clickLoc.getX() >= mPos.getX()) && (clickLoc.getX() <= mPos.getX() + mWidth))
	{
		if ((clickLoc.getY() >= mPos.getY()) && (clickLoc.getY() <= mPos.getY() + mHeight))
		{
			return true;
		}
	}
	return false;
}

void Button::cleanup()
{
	delete mButtonColor;
	mButtonColor = nullptr;
	delete mpRectBuffer;
	mpRectBuffer = nullptr;
}
