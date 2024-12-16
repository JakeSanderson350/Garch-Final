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
	//DO NOT modify any code in main!
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;

	const string INIT_TRACKER_NAME = "init";
	const string DRAW_TRACKER_NAME = "draw";
	const string WAIT_TRACKER_NAME = "wait";


	pPerformanceTracker->startTracking(INIT_TRACKER_NAME);


	if (!initAllSubsystems())
	{
		cout << "ERROR - Init failed\n";
		system("pause");
		return 1;
	}

	const int DISP_WIDTH = 800;
	const int DISP_HEIGHT = 600;

	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string BACKGROUND_FILENAME = "axamer-lizum.png";
	const string QUIMBY_FILENAME = "mayor_quimby.png";
	const string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 24;
	const string SAMPLE_FILENAME = "clapping.wav";
	const double SLEEP_TIME_IN_SEC = 5.0;

	ALLEGRO_DISPLAY* display = createDisplay(DISP_WIDTH, DISP_HEIGHT);
	assert(display);

	ALLEGRO_BITMAP* backbuffer = getBackbuffer(display);
	assert(backbuffer);
	ALLEGRO_BITMAP* bitmap = loadBitmap((ASSET_PATH + BACKGROUND_FILENAME).c_str());
	assert(bitmap);
	ALLEGRO_BITMAP* quimby = loadBitmap((ASSET_PATH + QUIMBY_FILENAME).c_str());
	assert(quimby);
	ALLEGRO_BITMAP* memMap = createBitmap(DISP_WIDTH, DISP_HEIGHT);

	ALLEGRO_FONT* font = loadFont((ASSET_PATH + FONT_FILENAME).c_str(), FONT_SIZE);
	assert(font);

	const ALLEGRO_COLOR WHITE = createColor(255, 255, 255);
	const ALLEGRO_COLOR BLACK = createColor(0, 0, 0);
	const ALLEGRO_COLOR BLACK_TRANSPARENT = createColor(0, 0, 0, 200);
	const ALLEGRO_COLOR PURPLE = createColor(128, 64, 212);

	setBitmapToColor(memMap, PURPLE);
	drawCircle(memMap, Vector2D(DISP_WIDTH, DISP_HEIGHT), 300, createColor(200, 100, 0), true);
	drawCircle(memMap, Vector2D(DISP_WIDTH, DISP_HEIGHT), 300, BLACK, false);

	save(memMap, "memory.jpg");

	blit(backbuffer, memMap, Vector2D(0, 0), Vector2D(0, 0), getSize(memMap), Vector2D(.333f, .333f));

	ALLEGRO_SAMPLE* sample = loadSample((ASSET_PATH + SAMPLE_FILENAME).c_str());
	assert(sample);

	playSample(sample, true);

	pPerformanceTracker->stopTracking(INIT_TRACKER_NAME);

	pPerformanceTracker->startTracking(DRAW_TRACKER_NAME);

	setBitmapToColor(backbuffer, WHITE);

	drawBitmap(backbuffer, bitmap, Vector2D(100,0));

	blit(backbuffer, memMap, Vector2D(0, 0), Vector2D(0, 0), getSize(memMap), Vector2D(.333f, .333f));

	const int CIRCLE_RADIUS = 150;
	const int LOC1_X = 400;
	const int LOC1_Y = 300;

	drawCircle(backbuffer,Vector2D(LOC1_X, LOC1_Y), CIRCLE_RADIUS, BLACK);
	drawText(backbuffer, font, Vector2D(LOC1_X, LOC1_Y), ALLEGRO_ALIGN_CENTER, "Welcome to Allegro!", WHITE);

	const int LOC2_X = 200;
	const int LOC2_Y = 500;
	drawCircle(backbuffer, Vector2D(LOC2_X, LOC2_Y), CIRCLE_RADIUS, BLACK_TRANSPARENT);
	drawText(backbuffer, font, Vector2D(LOC2_X, LOC2_Y), ALLEGRO_ALIGN_CENTER, "Welcome to Allegro!", PURPLE);

	const int LOC3_X = 500;
	const int LOC3_Y = 400;
	Vector2D size = getSize(quimby);
	const float SCALE_FACTOR = 0.75f;
	blit(backbuffer, quimby, Vector2D(LOC3_X, LOC3_Y), Vector2D(0, 0), size, Vector2D(SCALE_FACTOR, SCALE_FACTOR));

	save(backbuffer,"output.jpg");
	flip();

	pPerformanceTracker->stopTracking(DRAW_TRACKER_NAME);

	pPerformanceTracker->startTracking(WAIT_TRACKER_NAME);

	Timer timer;
	timer.sleep(SLEEP_TIME_IN_SEC*1000);

	pPerformanceTracker->stopTracking(WAIT_TRACKER_NAME);

	destroyBitmap(bitmap);
	destroyBitmap(quimby);
	destroyBitmap(memMap);
	destroySample(sample);
	destroyFont(font);
	destroyDisplay(display);

	//report elapsed times
	cout << endl << "Time to Init:" << pPerformanceTracker->getElapsedTime(INIT_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time to Draw:" << pPerformanceTracker->getElapsedTime(DRAW_TRACKER_NAME) << " ms" << endl;
	cout << endl << "Time spent waiting:" << pPerformanceTracker->getElapsedTime(WAIT_TRACKER_NAME) << " ms" << endl;

	MemoryTracker::getInstance()->reportAllocations(cout);

	system("pause");
	return 0;
}