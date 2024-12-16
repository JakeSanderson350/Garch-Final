#include "Color.h"

Color::Color(int r, int g, int b, int a /*= 255*/)
	:mR(r),mG(g),mB(b),mA(a)
{
}

Color::Color(float r, float g, float b, float a /*= 1.0f*/)
	:mR(r*255), mG(g*255), mB(b*255), mA(a*255)

{
}

ALLEGRO_COLOR Color::getAllegroColorFromColor(const Color& color)
{
	//call al_map_rgba or al_map_rgba_f
	ALLEGRO_COLOR aColor = al_map_rgba(color.mR,color.mG,color.mB,color.mA);
	return aColor;
}


