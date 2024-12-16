#include "GraphicsBuffer.h"
#include "GraphicsSystem.h"
#include "Color.h"
#include "Sprite.h"
#include "Font.h"

GraphicsBuffer::GraphicsBuffer(ALLEGRO_DISPLAY* pDisplay)
{
	//get backbuffer and set mpBitmap to that
	mpBitmap = al_get_backbuffer(pDisplay);
	mOwnsBitmap = false;
}

GraphicsBuffer::GraphicsBuffer(const std::string& filename)
{
	//load bitmap from the given file
	mpBitmap = al_load_bitmap(filename.c_str());
}

GraphicsBuffer::GraphicsBuffer(unsigned int width, unsigned int height, Color color)
{
	//create bitmap and set it to the given color
	mpBitmap = al_create_bitmap(width, height);

	setToColor(color);
}

GraphicsBuffer::~GraphicsBuffer()
{
	//make sure you destroy the bitmap (if appropriate)
	if (mOwnsBitmap)
	{
		al_destroy_bitmap(mpBitmap);
		mpBitmap = nullptr;
	}
}

GraphicsBuffer * GraphicsBuffer::clone() const
{
	//create new bitmap and copy all of "this" into it
	GraphicsBuffer* pNewBuffer = nullptr;

	//Creates new bitmap
	pNewBuffer = new GraphicsBuffer(this->getWidth(), this->getHeight());

	//Draws to new bitmap
	pNewBuffer->draw(Vector2D(0.0f, 0.0f), *this);

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
		al_draw_scaled_bitmap(src.mpBitmap, 0.0f, 0.0f, srcW, srcH, destLoc.getX(), destLoc.getY(), srcW * scale, srcW * scale, 0.0f);

		//restore the old target
		al_set_target_bitmap(pOldTarget);
	}
}


void GraphicsBuffer::draw(const Vector2D& destLoc, const Sprite& sprite, double scale /*= 1.0*/)
{
	ALLEGRO_BITMAP* pTarget = mpBitmap;
	GraphicsBuffer* pSrc = sprite.getBuffer();

	//do the same steps as in the other draw function - 
	//  make sure we are not drawing from and to the same bitmap

	assert(pTarget != pSrc->mpBitmap);//make sure we are not trying to draw to and from the same bitmap
	if (pTarget != pSrc->mpBitmap)
	{
		//get old target so we can restore it after we draw
		ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
		//set the new target
		al_set_target_bitmap(pTarget);

		int spriteW = sprite.getWidth();
		int spriteH = sprite.getHeight();

		Vector2D spritePos = Vector2D(sprite.getSourceLoc().getX(), sprite.getSourceLoc().getY());

		//call al_draw_scaled_bitmap to do the actual drawing
		al_draw_scaled_bitmap(pSrc->mpBitmap, spritePos.getX(), spritePos.getY(), spriteW, spriteH, destLoc.getX(), destLoc.getY(), spriteW * scale, spriteW * scale, 0.0f);

		//restore the old target
		al_set_target_bitmap(pOldTarget);
	}
}

void GraphicsBuffer::writeText(const Vector2D& destLoc, const Font& font, const Color& color, const std::string& text, Font::Alignment align)
{
	//get old target
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	//set the new target
	al_set_target_bitmap(mpBitmap);

	//call al_draw_text - 
	//  use helper functions Color::getAllegroColorFromColor and
	//  Font::getAllegroFontAlignFlag
	al_draw_text(font.mpFont, Color::getAllegroColorFromColor(color), destLoc.getX(), destLoc.getY(), Font::getAllegroFontAlignFlag(align), text.c_str());

	//restore old target
	al_set_target_bitmap(pOldTarget);

}

void GraphicsBuffer::setToColor(const Color& color)
{
	//use al_clear_to_color - make sure to save/restore old target before calling
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(mpBitmap);

	al_clear_to_color(Color::getAllegroColorFromColor(color));

	al_set_target_bitmap(pOldTarget);
}

void GraphicsBuffer::saveToFile(const std::string& filename) const
{
	//call al_save_bitmap
	al_save_bitmap(filename.c_str(), mpBitmap);
}

