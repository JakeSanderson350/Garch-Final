#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Color.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cassert>

using namespace std;

GraphicsBuffer* GraphicsSystem::mpBackBuffer=nullptr;


GraphicsSystem::GraphicsSystem()
{
	//init any member variables to default values

	//DO NOT call init
}

GraphicsSystem::~GraphicsSystem()
{
	//make sure you call cleanup
}

bool GraphicsSystem::init(unsigned int width, unsigned int height)
{
	//init all allegro subsystems (and allegro itself)
	// create a display of size width X height
	// create the backbuffer GraphicsBuffer

	//return true if everything is initted properly
	return true;
}

void GraphicsSystem::cleanup()
{
	//destroy mpDisplay at a minimum
}

void GraphicsSystem::flip()
{
}

bool GraphicsSystem::initAddOns()
{
	if (!al_init_image_addon())
	{
		cout << "error - Image Add-on not initted\n";
		return false;
	}
	if (!al_init_font_addon())
	{
		cout << "error - Font Add-on not initted\n";
		return false;
	}
	else if (!al_init_ttf_addon())
	{
		cout << "error - TTF Add-on not initted\n";
		return false;
	}
	if (!al_init_primitives_addon())
	{
		cout << "error - primitives Add-on not initted\n";
		return false;
	}
	if (!al_install_audio())
	{
		cout << "Warning!!! - Audio Add-on not initted\n";
	}
	else if (!al_init_acodec_addon())
	{
		cout << "Warning!!! - Audio Codec Add-on not initted\n";
	}
	else if (!al_reserve_samples(1))
	{
		cout << "Warning!!! - samples not reserved\n";
	}

	return true;
}
