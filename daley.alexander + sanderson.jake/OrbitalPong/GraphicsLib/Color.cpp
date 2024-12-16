#include "Color.h"

Color::Color(int r, int g, int b, int a /*= 255*/)
{
	//implement this
	mRed = r;
	mGreen = g;
	mBlue = b;
	mAlpha = a;
}

Color::Color(float r, float g, float b, float a /*= 1.0f*/)
{
	//implement this
	//Convert float 0.0 - 1.0 to 0 - 255
	mRed = (int)(r * 255);
	mGreen = (int)(g * 255);
	mBlue = (int)(b * 255);
	mAlpha = (int)(a * 255);
}

SDL_Color Color::getSDLColorFromColor(const Color& color)
{
	//call al_map_rgba or al_map_rgba_f
	SDL_Color aColor;
	
	aColor.r = color.getR();
	aColor.g = color.getG();
	aColor.b = color.getB();

	return aColor;
}

Uint32 Color::getUint32Color(const Color& color)
{
	SDL_PixelFormat* pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);

	return SDL_MapRGBA(pixelFormat, color.getR(), color.getG(), color.getB(), color.getA());
}


