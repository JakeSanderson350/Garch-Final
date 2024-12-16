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
	mRed = r * 255;
	mGreen = g * 255;
	mBlue = b * 255;
	mAlpha = a * 255;
}

ALLEGRO_COLOR Color::getAllegroColorFromColor(const Color& color)
{
	//call al_map_rgba or al_map_rgba_f
	ALLEGRO_COLOR aColor;

	aColor = al_map_rgba(color.getR(), color.getG(), color.getB(), color.getA());

	return aColor;
}


