#include "Sprite.h"

//implement me
Sprite::Sprite(GraphicsBuffer* pBuffer, const Vector2D& ulCorner, unsigned int width, unsigned int height)
{
	mpSrcBuffer = pBuffer;
	mSpritePos = ulCorner;
	mWidth = width;
	mHeight = height;
}

//implement me
Sprite::Sprite()
{
	mpSrcBuffer = nullptr;
	mSpritePos = Vector2D(0.0f, 0.0f);
	mWidth = 0;
	mHeight = 0;
}

//implement me
Sprite::~Sprite()
{
	
}
