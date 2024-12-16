#include "Font.h"
#include "Font.h"
#include <cassert>

using namespace std;

Font::Font(const std::string& filename, int size)
{
	//call al_load_font
	mpFont = al_load_font(filename.c_str(), size, 0);
	mSize = size;
}

Font::~Font()
{
	//call al_destroy_font
	al_destroy_font(mpFont);
	mpFont = nullptr;
}

int Font::getAllegroFontAlignFlag(Font::Alignment align)
{
	int flag = 0;
	//map the align variable to one of the allegro alignment flags
	if (align == LEFT)
	{
		flag = ALLEGRO_ALIGN_LEFT;
	}
	else if (align == CENTER)
	{
		flag = ALLEGRO_ALIGN_CENTER;
	}
	else if (align == RIGHT)
	{
		flag = ALLEGRO_ALIGN_RIGHT;
	}
	//Defaults to left aligned if parameter isn't valid
	else
	{
		flag = ALLEGRO_ALIGN_LEFT;
	}

	return flag;
}
