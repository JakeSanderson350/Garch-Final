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
	return true;
}

ALLEGRO_FONT* loadFont(const std::string& filename, int size)
{
	return al_load_ttf_font(filename.c_str(),size,0);
}


ALLEGRO_DISPLAY* createDisplay(int width, int height)
{
	return al_create_display(width, height);
}

ALLEGRO_BITMAP* getBackbuffer(ALLEGRO_DISPLAY* pDisplay)
{
	return al_get_backbuffer(pDisplay);
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

void drawText(ALLEGRO_BITMAP* dest, ALLEGRO_FONT* pFont, const Vector2D& loc, int alignment, const std::string& text, const ALLEGRO_COLOR& color)
{
	ALLEGRO_BITMAP* pOldTarget = al_get_target_bitmap();
	al_set_target_bitmap(dest);

	al_draw_text(pFont, color, loc.getX(), loc.getY(), alignment, text.c_str());

	al_set_target_bitmap(pOldTarget);
}

void destroyFont(ALLEGRO_FONT* font)
{
	al_destroy_font(font);
}

void destroyDisplay(ALLEGRO_DISPLAY* pDisplay)
{
	al_destroy_display(pDisplay);
}

void cleanupAllegro()
{
	al_uninstall_system();
}
