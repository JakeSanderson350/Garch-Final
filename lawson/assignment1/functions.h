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
bool initSoundSubsystem(int numSamplesToReserve);

bool initAllSubsystems();

ALLEGRO_BITMAP* loadBitmap(const std::string& filename);
ALLEGRO_BITMAP* createBitmap(int width, int height);
ALLEGRO_FONT* loadFont(const std::string& filename, int size);
ALLEGRO_SAMPLE* loadSample(const std::string& filename);
void playSample(ALLEGRO_SAMPLE* pSample, bool loop = true);
ALLEGRO_DISPLAY* createDisplay(int width, int height);

ALLEGRO_BITMAP* getBackbuffer(ALLEGRO_DISPLAY* pDisplay);

void blit(ALLEGRO_BITMAP* dest, ALLEGRO_BITMAP* src,
	const Vector2D& destLoc,
	const Vector2D& srcLoc,
	const Vector2D& srcSize,
	const Vector2D& scale);
void drawBitmap(ALLEGRO_BITMAP* dest, ALLEGRO_BITMAP* src, const Vector2D& loc);

void flip();

void setBitmapToColor(ALLEGRO_BITMAP* bitmap, const ALLEGRO_COLOR& color);

ALLEGRO_COLOR createColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);

void drawCircle(ALLEGRO_BITMAP* dest, const Vector2D& center, float radius, const ALLEGRO_COLOR& color, bool filled = true);
void drawText(ALLEGRO_BITMAP* dest, ALLEGRO_FONT* pFont, const Vector2D& loc, int alignment, const std::string& text, const ALLEGRO_COLOR& color);
Vector2D getSize(ALLEGRO_BITMAP* bitmap);
void save(ALLEGRO_BITMAP* bitmap, const std::string filename);

void destroyBitmap(ALLEGRO_BITMAP* bitmap);
void destroyFont(ALLEGRO_FONT* font);
void destroyDisplay(ALLEGRO_DISPLAY* pDisplay);
void destroySample(ALLEGRO_SAMPLE* pSample);
void cleanupAllegro();