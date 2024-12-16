#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <Trackable.h>

#include <string>

class GraphicsSystem;

class Font:public Trackable
{
	friend class GraphicsBuffer;//allows GraphicsBuffer functions to call getAllegroFontAlignFlag
public:
	enum Alignment
	{
		LEFT,
		CENTER,
		RIGHT
	};

	Font(const std::string& filename,int size);
	~Font();

	int getSize() const { return mSize; };

private:
	ALLEGRO_FONT * mpFont = nullptr;
	int mSize=0;

	//map our Align enum values to the allegro values
	static int getAllegroFontAlignFlag(Font::Alignment align);
};
