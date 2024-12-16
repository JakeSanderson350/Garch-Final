#include <iostream>
#include <cassert>
#include <string>
#include <random>
#include <ctime>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <GraphicsSystem.h>
#include <GraphicsBuffer.h>
#include <Sprite.h>
#include <Color.h>
#include <Font.h>

using namespace std;

int main()
{
	default_random_engine randomEngine;
	randomEngine.seed((unsigned int)time(NULL));
	uniform_int_distribution<> distribution(1, 100000);

	bool ret = false;
	const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string KENNEY_ASSET_PATH = "kenney_toon-characters\\female adventurer\\tilesheet\\";
	const string FADVENTURER_FILENAME = "character_femaleAdventurer_sheet.png";
	const string FADVENTURERHD_FILENAME = "character_femaleAdventurer_sheetHD.png";
	const string STEPS_FILENAME = "steps.png";
	const string SMURF_FILENAME = "smurf_sprites.png";
	const string QUIMBY_FILENAME = "mayor_quimby.png";
	const string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 48;
	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 600;
	const Color RED(255, 0, 0);
	const Color BLACK(0, 0, 0);
	const Color WHITE(1.0f, 1.0f, 1.0f);
	const Color PINK(255, 105, 180, 128);

	{
		Timer timer;

		GraphicsSystem theSystem;

		theSystem.cleanup();
		bool ret = theSystem.init(WIDTH, HEIGHT);
		timer.sleep(500.0);
		ret = theSystem.init(1024, 768);
		timer.sleep(500.0);
		theSystem.cleanup();
		ret = theSystem.init(WIDTH*2, HEIGHT*2);
		timer.sleep(500.0);
		ret = theSystem.init(WIDTH, HEIGHT);

		GraphicsBuffer* pStepsBuffer = new GraphicsBuffer(ASSET_PATH + STEPS_FILENAME);
		GraphicsBuffer* pSmurfBuffer = new GraphicsBuffer(ASSET_PATH + SMURF_FILENAME);
		GraphicsBuffer* pQuimbyBuffer = new GraphicsBuffer(ASSET_PATH + QUIMBY_FILENAME);
		GraphicsBuffer* pRedBuffer = new GraphicsBuffer(WIDTH, HEIGHT, RED);
		GraphicsBuffer* pFAdventurer = new GraphicsBuffer(ASSET_PATH + KENNEY_ASSET_PATH + FADVENTURER_FILENAME);
		GraphicsBuffer* pFAdventurerHD = new GraphicsBuffer(ASSET_PATH + KENNEY_ASSET_PATH + FADVENTURERHD_FILENAME);

		Font* pFont = new Font(ASSET_PATH + FONT_FILENAME, FONT_SIZE);
		Font* pFont2 = new Font(ASSET_PATH + FONT_FILENAME, FONT_SIZE*4);

		pRedBuffer->draw( Vector2D(0, 0), *pQuimbyBuffer);
		pRedBuffer->writeText(Vector2D(0, 0), *pFont, BLACK, "Curse you Papa Smurf!!!", Font::LEFT);
		pRedBuffer->saveToFile("temp.jpg");

		GraphicsSystem::getBackBuffer()->draw(Vector2D(0, 0), *pStepsBuffer);
		GraphicsSystem::getBackBuffer()->draw(Vector2D(133, 100), *pRedBuffer, 0.66667);

		const unsigned int PIXEL_WIDTH = 60;
		const unsigned int PIXEL_HEIGHT = 60;
		const unsigned int SPRITES_ACROSS = 4;
		const unsigned int SPRITES_DOWN = 4;
		Sprite sprites[SPRITES_ACROSS*SPRITES_DOWN];
		unsigned int spriteNum = 0;

		for (unsigned int x = 0; x < SPRITES_ACROSS; x++)
		{
			for (unsigned int y = 0; y < SPRITES_DOWN; y++)
			{
				Sprite sprite(pSmurfBuffer, Vector2D((int)(x*PIXEL_WIDTH), (int)(y*PIXEL_HEIGHT)), PIXEL_WIDTH, PIXEL_HEIGHT);
				sprites[spriteNum] = sprite;
				spriteNum++;
			}
		}

		for (int i = 0; i < SPRITES_ACROSS*SPRITES_DOWN; i++)
		{
			int x = distribution(randomEngine) % (WIDTH-60);
			int y = distribution(randomEngine) % (HEIGHT-60);
			cout << "sprite:" << i+1 << " at " << x << " " << y << endl;
			GraphicsSystem::getBackBuffer()->draw(Vector2D(x,y), sprites[i]);
		}

		Sprite adventurerSprite(pFAdventurer, Vector2D(0, 512), 96, 128);
		Sprite adventurerHDSprite(pFAdventurerHD, Vector2D(0, 1024), 192, 256);
		GraphicsSystem::getBackBuffer()->draw(Vector2D(100, 100), adventurerSprite);
		GraphicsSystem::getBackBuffer()->draw(Vector2D(250, 100), adventurerHDSprite);

		GraphicsBuffer* clonedBackbuffer = GraphicsSystem::getBackBuffer()->clone();
		clonedBackbuffer->writeText(Vector2D(200, 400), *pFont2, PINK, "PINK", Font::CENTER);

		GraphicsSystem::getBackBuffer()->draw(Vector2D(0, 0), *clonedBackbuffer, 0.5f);

		GraphicsSystem::getBackBuffer()->saveToFile("backbuffer.jpg");
		pRedBuffer->saveToFile("redbuffer.jpg");

		theSystem.flip();

		timer.start();
		timer.sleepUntilElapsed(5000.0);

		delete pStepsBuffer;
		delete pSmurfBuffer;
		delete pQuimbyBuffer;
		delete pRedBuffer;
		delete pFAdventurer;
		delete pFAdventurerHD;
		delete clonedBackbuffer;
		delete pFont;
		delete pFont2;

		theSystem.cleanup();

	}

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

	return ret;

}