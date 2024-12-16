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
	int getR() const { return 0; };
	int getG() const { return 0; };
	int getB() const { return 0; };
	int getA() const { return 0; };

private:
	//use variable(s) to hold values to represent color

	//map a Color to an ALLEGRO_COLOR
	static ALLEGRO_COLOR getAllegroColorFromColor(const Color& color);

};
