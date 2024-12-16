#pragma once

#include <SDL_ttf.h>

#include <Trackable.h>

#include <string>

class GraphicsSystem;

class Font:public Trackable
{
	friend class GraphicsBuffer;
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
	void setSize(int newSize) { mSize = newSize; };

private:
	TTF_Font * mpFont;
	int mSize=0;

};
