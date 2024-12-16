#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <Vector2D.h>
#include <string>

bool initSystem();
bool initGraphicsSubsystem();
bool initFontSubsystem();

bool initAllSubsystems();

ALLEGRO_FONT* loadFont(const std::string& filename, int size);
ALLEGRO_DISPLAY* createDisplay(int width, int height);

ALLEGRO_BITMAP* getBackbuffer(ALLEGRO_DISPLAY* pDisplay);

void flip();

void setBitmapToColor(ALLEGRO_BITMAP* bitmap, const ALLEGRO_COLOR& color);

ALLEGRO_COLOR createColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);

void drawText(ALLEGRO_BITMAP* dest, ALLEGRO_FONT* pFont, const Vector2D& loc, int alignment, const std::string& text, const ALLEGRO_COLOR& color);

void destroyFont(ALLEGRO_FONT* font);
void destroyDisplay(ALLEGRO_DISPLAY* pDisplay);
void cleanupAllegro();