#pragma once

#include <Trackable.h>
#include <Vector2D.h>

#include <SDL.h>

#include "Color.h"
#include "Font.h"

class GraphicsBuffer;
class Sprite;

class GraphicsSystem :public Trackable
{
public:
	GraphicsSystem();//should not call init
	~GraphicsSystem();//should call cleanup

	//make sure initting multiple times in a row doesn't fail
	bool init(unsigned int width, unsigned int height);//make sure initting multiple times in a row doesn't fail
	
	//make sure calling cleanup never fails
	void cleanup();

	unsigned int getDisplayWidth() const { return mWidth; };
	unsigned int getDisplayHeight() const { return mHeight; };
	
	static GraphicsBuffer* getBackBuffer() { return mpBackBuffer; };
	static SDL_Renderer* getRenderer() { return mpRenderer; };

	void clearRenderer();
	void flip();//flip the display

private:
	SDL_Window* mpWindow = nullptr;
	static SDL_Renderer* mpRenderer;
	SDL_Texture* mpTexture = nullptr;
	static GraphicsBuffer* mpBackBuffer;

	unsigned int mWidth = 0;
	unsigned int mHeight = 0;

	bool initAddOns();
	SDL_Window* getDisplay() const { return mpWindow; };


};
