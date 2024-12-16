#include "Font.h"
#include "Font.h"
#include <cassert>

using namespace std;

Font::Font(const std::string& filename, int size)
{
	//call ttf_openFont
	mpFont = TTF_OpenFont(filename.c_str(), size);
	mSize = size;

	if (!mpFont)
	{
		cout << "Error creating font\n";
	}
}

Font::~Font()
{
	//call ttf_closeFont
	TTF_CloseFont(mpFont);
	mpFont = nullptr;
}
