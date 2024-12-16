#pragma once

#include <allegro5/allegro.h>

#include <Trackable.h>

class GraphicsSystem;

class Color :public Trackable
{
	friend class GraphicsBuffer;//allows GraphicsBuffer functions to call getAllegroColorFromColor
public:
	Color() {};//default constructor
	Color(int r, int g, int b, int a = 255);//construct Color from int values
	Color(float r, float g, float b, float a = 1.0f);//construct Color from float values

	//implement these functions for real
	int getR() const { return mRed; };
	int getG() const { return mGreen; };
	int getB() const { return mBlue; };
	int getA() const { return mAlpha; };

private:
	//use variable(s) to hold values to represent color
	//0-255
	int mRed = 255;
	int mGreen = 255;
	int mBlue = 255;
	int mAlpha = 255;

	//map a Color to an ALLEGRO_COLOR
	static ALLEGRO_COLOR getAllegroColorFromColor(const Color& color);

};
