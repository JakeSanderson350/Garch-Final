#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>
#include <Timer.h>

#include "functions.h"

using namespace std;

int main()
{
	if (!initAllSubsystems())
	{
		cout << "ERROR - Init failed\n";
		system("pause");
		return 1;
	}

	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;

	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 48;
	const double SLEEP_TIME = 5.0;

	ALLEGRO_DISPLAY* display = createDisplay(DISP_WIDTH, DISP_HEIGHT);
	assert(display);

	ALLEGRO_BITMAP* backbuffer = getBackbuffer(display);
	assert(backbuffer);
	ALLEGRO_FONT* font = loadFont((ASSET_PATH + FONT_FILENAME).c_str(), FONT_SIZE);
	assert(font);

	const ALLEGRO_COLOR WHITE = createColor(255, 255, 255);
	const ALLEGRO_COLOR PURPLE = createColor(128, 64, 212);

	setBitmapToColor(backbuffer, PURPLE);

	drawText(backbuffer, font, Vector2D(DISP_WIDTH/2, DISP_HEIGHT/2), ALLEGRO_ALIGN_CENTER, "Welcome to Allegro!", WHITE);

	flip();

	Timer timer;
	timer.sleep(SLEEP_TIME*1000);

	destroyFont(font);
	destroyDisplay(display);

	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");
	return 0;
}

