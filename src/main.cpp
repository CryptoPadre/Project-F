/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/
// das
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include "Character.h"
#include <string>
#include "Prop.h"
#include "Enemy.h"

int main()
{
	// window size
	int screenWidth = 1000;
	int screenHeight = 600;
	// entry and exit points of the map
	float entryWidth = -150.0;
	float entryHeight = -30.0;
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "FROM");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load the map for day time
	Texture2D map = LoadTexture("fromville.png");
	Vector2 mapPos{entryWidth, entryHeight};
	const float mapScale{2.0};
	// Create a map for nighttime - same map but with manipulated brightness
	Image mapNight = LoadImageFromTexture(map);
	ImageColorBrightness(&mapNight, -80);
	Texture2D mapNightTexture = LoadTextureFromImage(mapNight);
	// Render props

	Prop props[1]{
		Prop{Vector2{1500.f, 10.f}, LoadTexture("house.png")}};
    // render enemy
	Enemy she{Vector2{},LoadTexture("monster-she-walk.png") };

	// set target fps
	SetTargetFPS(60);
	// change the map if it night or daytime
	bool isDayTime{true};
	Character hero{screenWidth, screenHeight};
	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);
		mapPos = Vector2Scale(hero.getWorldPos(), -1.f);
		if (isDayTime)
		{
			// draw the map for daytime
			DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
		}
		else
		{
			// draw the map for nighttime
			DrawTextureEx(mapNightTexture, mapPos, 0.0, mapScale, WHITE);
		}
		// draw props
		for (auto prop : props)
		{
			prop.Render(hero.getWorldPos());
		}
		hero.tick(GetFrameTime());
		if (hero.getWorldPos().x < 0.f || hero.getWorldPos().y < 0.f ||
			hero.getWorldPos().x + screenWidth > map.width * mapScale ||
			hero.getWorldPos().y + screenHeight > map.height * mapScale - 30)
		{
			hero.undoMovement();
		}
		// check prop collision
		for (auto prop : props)
		{
			if (CheckCollisionRecs(prop.GetCollisionRec(hero.getWorldPos()),
			hero.GetCollisionRec()))
			{
				hero.undoMovement();
			}
		}
		she.tick(GetFrameTime());

			// end the frame and get ready for the next one  (display frame, poll input, etc...)
			EndDrawing();
		}

		// cleanup
		// unload our texture so it can be cleaned up
		UnloadTexture(map);
		UnloadTexture(mapNightTexture);

		// destroy the window and cleanup the OpenGL context
		CloseWindow();
		return 0;
	}
