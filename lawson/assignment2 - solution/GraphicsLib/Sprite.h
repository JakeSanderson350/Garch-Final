#pragma once

#include <Trackable.h>
#include <Vector2D.h>

class GraphicsBuffer;

class Sprite : public Trackable
{
public:
	Sprite(GraphicsBuffer* pBuffer, const Vector2D& ulCorner, unsigned int width, unsigned int height);
	Sprite();//default constructor
	~Sprite();//implement this destructor

	//implement these functions for real
	GraphicsBuffer* getBuffer() const { return mpBuffer; };
	const Vector2D& getSourceLoc() const { return mSrcLoc; };
	unsigned int getWidth() const { return mWidth; };
	unsigned int getHeight() const { return mHeight; };
private:
	//add data
	GraphicsBuffer* mpBuffer = nullptr;
	Vector2D mSrcLoc;
	unsigned int mWidth = 0;
	unsigned int mHeight = 0;
};