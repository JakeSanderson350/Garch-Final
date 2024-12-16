#include "functions.h"
using namespace std;

bool initSystem()
{
	return al_init();
}

bool initGraphicsSubsystem()
{
	return al_init_image_addon() && al_init_primitives_addon();
}

bool initFontSubsystem()
{
	return al_init_font_addon() && al_init_ttf_addon();
}

//TODO - call al_install_audio, al_init_acodec_addon, and al_reserve_samples
//return true if everything installs correctly, false otherwise
//
bool initSoundSubsystem(int numSamplesToReserve)
{
	return al_install_audio() && al_init_acodec_addon() && al_reserve_samples(numSamplesToReserve);
}

bool initAllSubsystems()
{
	if (!initSystem())
	{
		cout << "ERROR - System not initted\n";
		return false;
	}
	if (!initGraphicsSubsystem())
	{
		cout << "ERROR - Graphics subsystem not initted\n";
		return false;
	}
	if (!initFontSubsystem())
	{
		cout << "ERROR - Font subsystem not initted\n";
		return false;
	}
	if (!initSoundSubsystem(1))
	{
		cout << "ERROR - Sound subsystem not initted\n";
		return false;
	}

	//TODO - call initSoundSubsystem reserving 1 sample
	//write a warning to cout if it returns false but do not return false
	//
	return true;
}

//TODO - call al_load_bitmap to open the given file.
// return the ALLEGRO_BITMAP* returned from al_load_bitmap
//
ALLEGRO_BITMAP* loadBitmap(const std::string& filename)
{
	ALLEGRO_BITMAP* newBitmap = al_load_bitmap(filename.c_str());

	return newBitmap;
}

//TODO - call al_create_bitmap with the given width and height
// return the ALLEGRO_BITMAP*
//
ALLEGRO_BITMAP* createBitmap(int width, int height)
{
	ALLEGRO_BITMAP* newBitmap = al_create_bitmap(width, height);

	return newBitmap;
}

ALLEGRO_FONT* loadFont(const std::string& filename, int size)
{
	return al_load_ttf_font(filename.c_str(),size,0);
}

//TODO - call al_load_sample
// return the ALLEGRO_SAMPLE*
ALLEGRO_SAMPLE* loadSample(const std::string& filename)
{
	ALLEGRO_SAMPLE* newSample = al_load_sample(filename.c_str());

	return newSample;
}

//TODO - call al_play_sample - set the correct ALLEGRO_PLAYMODE based on the loop bool
//  if loop is true use ALLEGRO_PLAYMODE_LOOP, use ALLEGRO_PLAYMODE_ONCE otherwise
//  use values 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.0f and nullptr for the other arguments to al_play_sample
void playSample(ALLEGRO_SAMPLE* pSample, bool loop)
{
	if (loop)
	{
		al_play_sample(pSample, 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.0f, ALLEGRO_PLAYMODE_LOOP, NULL);
	}
	else
	{
		al_play_sample(pSample, 1.0f, ALLEGRO_AUDIO_PAN_NONE, 1.0f, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

ALLEGRO_DISPLAY* createDisplay(int width, int height)
{
	return al_create_display(width, height);
}

ALLEGRO_BITMAP* getBackbuffer(ALLEGRO_DISPLAY* pDisplay)
{
	return al_get_backbuffer(pDisplay);
}

//TODO - call al_draw_scaled_bitmap - make sure you save the old target, set the new target, call al_draw_scaled_bitmap,
//  and then set the target bitmap back to the old bitmap as done in setBitmapToColor
// Parameters:
// dest - the ALLEGRO_BITMAP* that will be drawn to
// src - the ALLEGRO_BITMAP* where the image already exists
// destLoc - the pixel location of where to draw to (the upper left corner)
// srcLoc - the pixel location in the src bitmap to draw from (upper left corner)
// srcSize - the width and height of the area to draw from
// srcScale - the scale of how to stretch the copied rectangle. Vector2D(1,1) would not stretch in either the x or y direction
void blit(ALLEGRO_BITMAP* dest, ALLEGRO_BITMAP* src, const Vector2D& destLoc, const Vector2D& srcLoc, const Vector2D& srcSize, const Vector2D& scale)
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(dest);

	al_draw_scaled_bitmap(src, srcLoc.getX(), srcLoc.getX(), srcSize.getX(), srcSize.getY(), destLoc.getX(), destLoc.getY(), srcSize.getX() * scale.getX(), srcSize.getY() * scale.getY(), 0.0f);

	al_set_target_bitmap(pOldTarget);
}

//TODO - call blit to copy the entire src bitmap starting at loc in dest bitmap
// call getSize to determine srcSize argument to blit call
void drawBitmap(ALLEGRO_BITMAP* dest, ALLEGRO_BITMAP* src, const Vector2D& loc)
{
	blit(dest, src, loc, Vector2D(0.0f, 0.0f), getSize(src), Vector2D(1.0f, 1.0f));
}

void flip()
{
	al_flip_display();
}

void setBitmapToColor(ALLEGRO_BITMAP* bitmap, const ALLEGRO_COLOR& color)
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(bitmap);

	al_clear_to_color(color);

	al_set_target_bitmap(pOldTarget);
}

ALLEGRO_COLOR createColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return al_map_rgba(r, g, b, a);
}

//TODO - call al_draw_circle or al_draw_filled_circle based on the filled bool parameter
// make sure you save the old target, set the new target, call al_draw_scaled_bitmap,
//  and then set the target bitmap back to the old bitmap as done in setBitmapToColor
//Parameters:
// dest - the ALLEGRO_BITMAP* to draw to
// center - the location of the center of the circle
// radius - the radius of the circle
// color - the ALLEGRO_COLOR of the circle
// filled - true means call al_draw_filled_circle
//          false means call al_draw_circle - use 3 as the last argument to al_draw_circle
void drawCircle(ALLEGRO_BITMAP* dest, const Vector2D& center, float radius, const ALLEGRO_COLOR& color, bool filled)
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(dest);

	if (filled)
	{
		al_draw_filled_circle(center.getX(), center.getY(), radius, color);
	}
	else
	{
		al_draw_circle(center.getX(), center.getY(), radius, color, 3);
	}

	al_set_target_bitmap(pOldTarget);
}

void drawText(ALLEGRO_BITMAP* dest, ALLEGRO_FONT* pFont, const Vector2D& loc, int alignment, const std::string& text, const ALLEGRO_COLOR& color)
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(dest);

	al_draw_text(pFont, color, loc.getX(), loc.getY(), alignment, text.c_str());

	al_set_target_bitmap(pOldTarget);

}

//TODO - call al_get_bitmap_width and al_get_bitmap_height to return the size of a given bitmap
Vector2D getSize(ALLEGRO_BITMAP* bitmap)
{
	Vector2D bitmapSizes;

	bitmapSizes.setX(al_get_bitmap_width(bitmap));
	bitmapSizes.setY(al_get_bitmap_height(bitmap));

	return bitmapSizes;
}

//TODO - call al_save_bitmap
void save(ALLEGRO_BITMAP* bitmap, const std::string filename)
{
	al_save_bitmap(filename.c_str(), bitmap);
}

//TODO - call al_destroy_bitmap
void destroyBitmap(ALLEGRO_BITMAP* bitmap)
{
	al_destroy_bitmap(bitmap);
}

void destroyFont(ALLEGRO_FONT* font)
{
	al_destroy_font(font);
}

void destroyDisplay(ALLEGRO_DISPLAY* pDisplay)
{
	al_destroy_display(pDisplay);
}

//TODO - call al_destroy_sample
void destroySample(ALLEGRO_SAMPLE* pSample)
{
	al_destroy_sample(pSample);
}

void cleanupAllegro()
{
	al_uninstall_system();
}
