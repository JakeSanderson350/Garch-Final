#include "GraphicsBuffer.h"
#include "GraphicsSystem.h"
#include "Color.h"
#include "Sprite.h"
#include "Font.h"

GraphicsBuffer::GraphicsBuffer(SDL_Window* pDisplay)
{
	//make surface out of window
	SDL_Surface* pSurface = SDL_GetWindowSurface(pDisplay);
	mOwnsBitmap = false;

	//make texture from surface
	mpTexture = SDL_CreateTextureFromSurface(GraphicsSystem::getRenderer(), pSurface);

	//set width and height
	SDL_QueryTexture(mpTexture, nullptr, nullptr, &mWidth, &mHeight);
}

GraphicsBuffer::GraphicsBuffer(const std::string& filename)
{
	//load texture from the given file
	mpTexture = IMG_LoadTexture(GraphicsSystem::getRenderer(), filename.c_str());

	//set width and height
	SDL_QueryTexture(mpTexture, nullptr, nullptr, &mWidth, &mHeight);
}

GraphicsBuffer::GraphicsBuffer(unsigned int width, unsigned int height, Color color)
{
	//create surface and set it to the given color
	SDL_Surface* pSurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_FillRect(pSurface, nullptr, Color::getUint32Color(color));

	//make texture from surface
	mpTexture = SDL_CreateTextureFromSurface(GraphicsSystem::getRenderer(), pSurface);

	//set width and height
	SDL_QueryTexture(mpTexture, nullptr, nullptr, &mWidth, &mHeight);
}

GraphicsBuffer::~GraphicsBuffer()
{
	//make sure you destroy the texture (if appropriate)
	if (mOwnsBitmap)
	{
		SDL_DestroyTexture(mpTexture);
		mpTexture = nullptr;
	}
}

GraphicsBuffer* GraphicsBuffer::clone() const
{
	//create new bitmap and copy all of "this" into it
	GraphicsBuffer* pNewBuffer = nullptr;

	//Creates new bitmap
	pNewBuffer = new GraphicsBuffer(this->getWidth(), this->getHeight());

	//Draws to new bitmap
	pNewBuffer->draw(Vector2D(0.0f, 0.0f), *this);

	return pNewBuffer;
}

void GraphicsBuffer::draw(const Vector2D& destLoc, const GraphicsBuffer& src, double angle, double scale)
{
	SDL_Texture* pTarget = mpTexture;//set the target bitmap

	assert(pTarget != src.mpTexture);//make sure we are not trying to draw to and from the same bitmap
	if (pTarget != src.mpTexture)
	{
		//Make Rects used for blit
		SDL_Rect destRect;
		destRect.x = (int)destLoc.getX();
		destRect.y = (int)destLoc.getY();
		destRect.w = (int)(src.getWidth() * scale);
		destRect.h = (int)(src.getHeight() * scale);

		SDL_Rect srcRect;
		srcRect.w = (int)src.getWidth();
		srcRect.h = (int)src.getHeight();

		//SDL_BlitScaled(src.mpSurface, &srcRect, pTarget, &destRect);
		SDL_RenderCopyEx(GraphicsSystem::getRenderer(), src.mpTexture, nullptr, &destRect, angle, nullptr, SDL_FLIP_NONE);
	}
}


void GraphicsBuffer::draw(const Vector2D& destLoc, const Sprite& sprite, double angle, double scale /*= 1.0*/)
{
	SDL_Texture* pTarget = mpTexture;
	GraphicsBuffer* pSrc = sprite.getBuffer();

	//do the same steps as in the other draw function - 
	//  make sure we are not drawing from and to the same bitmap

	assert(pTarget != pSrc->mpTexture);//make sure we are not trying to draw to and from the same bitmap
	if (pTarget != pSrc->mpTexture)
	{
		int spriteW = sprite.getWidth();
		int spriteH = sprite.getHeight();
		Vector2D spritePos = Vector2D(sprite.getSourceLoc().getX(), sprite.getSourceLoc().getY());

		//Make Rects used for blit
		SDL_Rect destRect;
		destRect.x = destLoc.getX();
		destRect.y = destLoc.getY();
		destRect.w = spriteW * scale;
		destRect.h = spriteH * scale;

		SDL_Rect srcRect;
		srcRect.x = spritePos.getX();
		srcRect.y = spritePos.getY();
		srcRect.w = spriteW;
		srcRect.h = spriteH;

		SDL_RenderCopyEx(GraphicsSystem::getRenderer(), pSrc->mpTexture, &srcRect, &destRect, angle, nullptr, SDL_FLIP_NONE);
	}
}

void GraphicsBuffer::writeText(const Vector2D& destLoc, const Font& font, const Color& color, const std::string& text, Font::Alignment align, double angle)
{
	//create surface for text
	SDL_Color SDLColor = Color::getSDLColorFromColor(color);
	SDL_Surface* pTextSurface = TTF_RenderText_Solid(font.mpFont, text.c_str(), SDLColor);

	//create texture from surface
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(GraphicsSystem::getRenderer(), pTextSurface);

	//Create new destLoc to offset text based on alignment
	Vector2D alignedDestLoc = destLoc;
	if (align == Font::Alignment::CENTER)
	{
		alignedDestLoc = Vector2D(destLoc.getX() - (pTextSurface->w / 2.0f), destLoc.getY());
	}
	else if (align == Font::Alignment::RIGHT)
	{
		alignedDestLoc = Vector2D(destLoc.getX() - (pTextSurface->w), destLoc.getY());
	}

	//Make Rect used for blit
	SDL_Rect destRect;
	destRect.x = alignedDestLoc.getX();
	destRect.y = alignedDestLoc.getY();
	destRect.w = pTextSurface->w;
	destRect.h = pTextSurface->h;

	SDL_RenderCopyEx(GraphicsSystem::getRenderer(), pTexture, nullptr, &destRect, angle, nullptr, SDL_FLIP_NONE);

	SDL_DestroyTexture(pTexture);
}

void GraphicsBuffer::setToColor(const Color& color)
{
	//SDL_FillRect(mpSurface, nullptr, Color::getUint32Color(color));
}

void GraphicsBuffer::saveToFile(const std::string& filename) const
{
	//call al_save_bitmap
	//IMG_SavePNG(mpSurface, filename.c_str());
}