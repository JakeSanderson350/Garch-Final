#include "GraphicsBuffer.h"
#include "GraphicsSystem.h"
#include "Color.h"
#include "Sprite.h"
#include "Font.h"

GraphicsBuffer::GraphicsBuffer(ALLEGRO_DISPLAY* pDisplay)
{
	//get backbuffer and set mpBitmap to that
	mpBitmap = al_get_backbuffer(pDisplay);
	assert(mpBitmap);
	mOwnsBitmap = false;
}

GraphicsBuffer::GraphicsBuffer(const std::string& filename)
{
	//load bitmap from the given file
	mpBitmap = al_load_bitmap(filename.c_str());
	assert(mpBitmap);
	mOwnsBitmap = true;
}

GraphicsBuffer::GraphicsBuffer(unsigned int width, unsigned int height, Color color)
{
	//create bitmap and set it to the given color
	mpBitmap = al_create_bitmap(width, height);
	assert(mpBitmap);
	mOwnsBitmap = true;
	setToColor(color);
}

GraphicsBuffer::~GraphicsBuffer()
{
	//make sure you destroy the bitmap (if appropriate)
	if (mOwnsBitmap)
		al_destroy_bitmap(mpBitmap);
}

GraphicsBuffer * GraphicsBuffer::clone() const
{
	//create new bitmap and copy all of "this" into it
	GraphicsBuffer* pNewBuffer = new GraphicsBuffer(getWidth(),getHeight());
	pNewBuffer->draw(ZERO_VECTOR2D, *this);
	return pNewBuffer;
}

void GraphicsBuffer::draw(const Vector2D& destLoc, const GraphicsBuffer& src, double scale)
{
	ALLEGRO_BITMAP* pTarget = mpBitmap;//set the target bitmap
	
	assert(pTarget != src.mpBitmap);//make sure we are not trying to draw to and from the same bitmap
	if (pTarget != src.mpBitmap)
	{
		//get old target so we can restore it after we draw
		ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
		//set the new target
		al_set_target_bitmap(pTarget);

		int srcW = src.getWidth();
		int srcH = src.getHeight();

		//call al_draw_scaled_bitmap to do the actual drawing
		al_draw_scaled_bitmap(src.mpBitmap, 0.0f, 0.0f, srcW, srcH, destLoc.getX(), destLoc.getY(), srcW * scale, srcH * scale, 0);
		//restore the old target
		al_set_target_bitmap(pOldTarget);
	}
}


void GraphicsBuffer::draw(const Vector2D& destLoc, const Sprite& sprite, double scale /*= 1.0*/)
{
	ALLEGRO_BITMAP* pTarget = mpBitmap;
	GraphicsBuffer* pSrc = sprite.getBuffer();
	//get old target so we can restore it after we draw
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	//set the new target
	al_set_target_bitmap(pTarget);

	//call al_draw_scaled_bitmap to do the actual drawing
	Vector2D srcLoc = sprite.getSourceLoc();
	float srcWidth = sprite.getWidth();
	float srcHeight = sprite.getHeight();
	al_draw_scaled_bitmap(pSrc->mpBitmap, srcLoc.getX(), srcLoc.getY(), srcWidth, srcHeight, destLoc.getX(), destLoc.getY(), srcWidth * scale, srcHeight * scale, 0);
	//restore the old target
	al_set_target_bitmap(pOldTarget);
}

void GraphicsBuffer::writeText(const Vector2D& destLoc, const Font& font, const Color& color, const std::string& text, Font::Alignment align)
{
	//get old target
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	//set the new target
	al_set_target_bitmap(mpBitmap);

	al_draw_text(font.mpFont,
		Color::getAllegroColorFromColor(color),
		destLoc.getX(),
		destLoc.getY(),
		Font::getAllegroFontAlignFlag(align),
		text.c_str());
	//call al_draw_text - 
	//  use helper functions Color::getAllegroColorFromColor and
	//  Font::getAllegroFontAlignFlag

	//restore old target
	al_set_target_bitmap(pOldTarget);

}

void GraphicsBuffer::setToColor(const Color& color)
{
	//use al_clear_to_color - make sure to save/restore old target before calling
	//get old target
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	//set the new target
	al_set_target_bitmap(mpBitmap);

	al_clear_to_color(Color::getAllegroColorFromColor(color));
	//restore old target
	al_set_target_bitmap(pOldTarget);
}

void GraphicsBuffer::saveToFile(const std::string& filename) const
{
	//call al_save_bitmap
	al_save_bitmap(filename.c_str(), mpBitmap);
}

