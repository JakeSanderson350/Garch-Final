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
	GraphicsBuffer* getBuffer() const { return nullptr; };
	const Vector2D& getSourceLoc() const { return ZERO_VECTOR2D; };
	unsigned int getWidth() const { return 0; };
	unsigned int getHeight() const { return 0; };
private:
	//add data
};