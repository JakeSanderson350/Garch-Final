#pragma once

#include <Trackable.h>
#include <Vector2D.h>

class GraphicsBuffer;

class Sprite : public Trackable
{
public:
	Sprite(GraphicsBuffer* pBuffer, const Vector2D& ulCorner, unsigned int width, unsigned int height);
	Sprite(const Sprite& sprite);
	Sprite();//default constructor
	~Sprite();//implement this destructor

	//implement these functions for real
	GraphicsBuffer* getBuffer() const { return mpSrcBuffer; };
	const Vector2D& getSourceLoc() const { return mSpritePos; };
	unsigned int getWidth() const { return mWidth; };
	unsigned int getHeight() const { return mHeight; };
private:
	//add data
	GraphicsBuffer* mpSrcBuffer;
	Vector2D mSpritePos;
	int mWidth;
	int mHeight;

};