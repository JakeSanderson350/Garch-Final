#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

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

	GraphicsBuffer(SDL_Window* pDisplay);//to be called by GraphicsSystem only

	GraphicsBuffer* clone() const;//return a new (dynamically allocated) buffer with the same contents as this

	unsigned int getWidth() const { return mWidth; };
	unsigned int getHeight() const { return mHeight; };
	SDL_Texture* getTexture() { return mpTexture; }

	void draw(const Vector2D& destLoc, const GraphicsBuffer& src, double angle = 0.0f, double scale = 1.0f);
	void draw(const Vector2D& destLoc, const Sprite& sprite, double angle = 0.0f, double scale = 1.0f);
	void writeText(const Vector2D& destLoc, const Font& font, const Color& color, const std::string& text, Font::Alignment align = Font::LEFT, double angle = 0.0f);
	void setToColor(const Color& color);
	void saveToFile(const std::string& filename) const;

private:
	SDL_Texture* mpTexture = nullptr;
	bool mOwnsBitmap = true;

	int mWidth;
	int mHeight;

	//static SDL_Renderer* mpRenderer;

	//invalidate copy constructor and assignment operator - why?
	GraphicsBuffer(GraphicsBuffer&)=delete;
	GraphicsBuffer operator=(GraphicsBuffer&)=delete;
};
