#include "Font.h"
#include "Font.h"
#include <cassert>

using namespace std;

Font::Font(const std::string& filename, int size)
{
	//call al_load_font
	mpFont = al_load_font(filename.c_str(), size, 0);
}

Font::~Font()
{
	//call al_destroy_font
	al_destroy_font(mpFont);
}

int Font::getAllegroFontAlignFlag(Font::Alignment align)
{
	int flag = 0;
	//map the align variable to one of the allegro alignment flags
	switch (align)
	{
	case Font::LEFT:
		flag = ALLEGRO_ALIGN_LEFT;
		break;
	case Font::CENTER:
		flag = ALLEGRO_ALIGN_CENTER;
		break;
	case Font::RIGHT:
		flag = ALLEGRO_ALIGN_RIGHT;
		break;
	default:
		assert(false);
	};
	return flag;
}
