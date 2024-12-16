#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <Trackable.h>

#include <string>
#include "Color.h"
#include "Font.h"

class GraphicsSystem;
class Vector2D;
class Sprite;

class GraphicsBuffer : public Trackable
{
public:
	GraphicsBuffer(const std::string& filename);
	GraphicsBuffer(unsigned int width, unsigned int height, Color color = Color() );
	~GraphicsBuffer();

	GraphicsBuffer(ALLEGRO_DISPLAY* pDisplay);//to be called by GraphicsSystem only

	GraphicsBuffer* clone() const;//return a new (dynamically allocated) buffer with the same contents as this

	unsigned int getWidth() const { return al_get_bitmap_width(mpBitmap); };
	unsigned int getHeight() const { return al_get_bitmap_height(mpBitmap); };

	void draw(const Vector2D& destLoc, const GraphicsBuffer& src, double scale = 1.0);
	void draw(const Vector2D& destLoc, const Sprite& sprite, double scale = 1.0);
	void writeText(const Vector2D& destLoc, const Font& font, const Color& color, const std::string& text, Font::Alignment align = Font::LEFT);
	void setToColor(const Color& color);
	void saveToFile(const std::string& filename) const;

private:
	ALLEGRO_BITMAP* mpBitmap = nullptr;

	//invalidate copy constructor and assignment operator - why?
	GraphicsBuffer(GraphicsBuffer&)=delete;
	GraphicsBuffer operator=(GraphicsBuffer&)=delete;
};
