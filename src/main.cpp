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
	// Create a map for nighttime - same map but with manipulated brightness
	Image mapNight = LoadImageFromTexture(map);
	ImageColorBrightness(&mapNight, -80);
	Texture2D mapNightTexture = LoadTextureFromImage(mapNight);
	Vector2 mapNightPos{entryWidth, entryHeight};
	// character
	Texture2D character = LoadTexture("hero-walk.png");
	Vector2 characterPos{
		(float)screenWidth / 2.0f - 0.1f * (float)(character.width),
		(float)screenHeight / 2.0f - 0.5f * ((float)character.height)

	};
	// set target fps
	SetTargetFPS(60);
	// change the map if it night or daytime
	bool isDayTime{true};

	// animation for character
	int totalColumns = 9;
	int totalRows = 4;

	int currentFrame = 0; // column (frame within the animation)
	int currentRow = 2;	  // row for direction: 0-back, 1-right, 2-front,3-left.

	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);
		if (isDayTime)
		{
			// draw the map for daytime
			DrawTextureEx(map, mapPos, 0.0, 2.0, WHITE);
		}
		else
		{
			// draw the map for nighttime
			DrawTextureEx(mapNightTexture, mapNightPos, 0.0, 2.0, WHITE);
		}
		Vector2 direction{};
		if (IsKeyDown(KEY_A))
			{direction.x -= 1.0;
			currentRow = 1;}
		if (IsKeyDown(KEY_D))
			{direction.x += 1.0;
			currentRow = 3;}
		if (IsKeyDown(KEY_W))
			{direction.y -= 1.0;
			currentRow = 0;}
		if (IsKeyDown(KEY_S))
			{direction.y += 1.0;
			currentRow = 2;}
		if (Vector2Length(direction) != 0.0)
		{
			// set mapPos = mapPos - direction

			mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), 3));
			currentFrame++;
			if (currentFrame > totalColumns)
			{
				currentFrame = 0;
			}
		}

		// Get frame width/height
		float frameWidth = (float)character.width / totalColumns;
		float frameHeight = (float)character.height / totalRows;

		// Define source rectangle to pick one frame
		Rectangle source{
			frameWidth * currentFrame, // X: shift by frame
			frameHeight * currentRow,  // Y: shift by row
			frameWidth,
			frameHeight};

		// Define destination rectangle
		Rectangle dest{
			characterPos.x,
			characterPos.y,
			frameWidth * 2.0f,
			frameHeight * 3.0f};
		// draw character

		DrawTexturePro(character, source, dest, Vector2{0, 0}, 0.f, WHITE);

		// Hide cursor
		HideCursor();

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(map);
	UnloadTexture(mapNightTexture);
	UnloadTexture(character);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
