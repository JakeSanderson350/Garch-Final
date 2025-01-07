#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Color.h"

#include <SDL_ttf.h>
#include <SDL_image.h>

#include <iostream>
#include <cassert>

using namespace std;

GraphicsBuffer* GraphicsSystem::mpBackBuffer = nullptr;
SDL_Renderer* GraphicsSystem::mpRenderer = nullptr;

GraphicsSystem::GraphicsSystem()
{
	//init any member variables to default values
	
	//Default variable initializtion in header

	//DO NOT call init
}

GraphicsSystem::~GraphicsSystem()
{
	//make sure you call cleanup
	cleanup();
}

bool GraphicsSystem::init(unsigned int width, unsigned int height)
{
	//Call cleanup to not make new backbuffers that won't get deleted
	cleanup();

	//init all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "error - SDL not initted\n";
		return false;
	}
	if (!initAddOns())
	{
		cout << "error - Add-ons not initted\n";
		return false;
	}

	// create a window of size width X height
	mpWindow = SDL_CreateWindow("My application",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height,
		0);
	if (!mpWindow)
	{
		cout << "Error creating window\n";
		return false;
	}

	// create renderer for window
	mpRenderer = SDL_CreateRenderer(mpWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!mpRenderer)
	{
		cout << "Error creating renderer\n";
		return false;
	}

	// create the backbuffer GraphicsBuffer
	mpBackBuffer = new GraphicsBuffer(mpWindow);

	// create texture from back buffer
	mpTexture = mpBackBuffer->getTexture();

	mWidth = width;
	mHeight = height;

	//return true if everything is initted properly
	return true;
}

void GraphicsSystem::cleanup()
{
	//Destroy Window
	SDL_DestroyWindow(mpWindow);
	mpWindow = nullptr;

	//Destroy renderer
	SDL_DestroyRenderer(mpRenderer);
	mpRenderer = nullptr;

	//Destroy texture
	SDL_DestroyTexture(mpTexture);

	//Delete backbuffer
	delete mpBackBuffer;
	mpBackBuffer = nullptr;

	//Quit SDL systems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void GraphicsSystem::clearRenderer()
{
	SDL_RenderClear(mpRenderer);
}

void GraphicsSystem::flip()
{
	SDL_RenderPresent(mpRenderer);
}

bool GraphicsSystem::initAddOns()
{
	if (TTF_Init() < 0)
	{
		cout << "error - Font Add-on not initted\n";
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) < 0)
	{
		cout << "error - Image Add-on not initted\n";
		return false;
	}

	return true;
}
