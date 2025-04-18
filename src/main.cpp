/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/
// das
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main ()
{	
	// starting position of the map
	float startWidth = -3550.0;
	float startHeight = -5280.0;
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	// Create the window and OpenGL context
	InitWindow(GetScreenWidth(), GetScreenHeight(), "FROM");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	
	// Load the map for day time
	Texture2D map = LoadTexture("fromville.png");
	Vector2 mapPos{startWidth, startHeight};
	// Create a map for nighttime - same map but with manipulated brightness
	Image mapNight = LoadImageFromTexture(map);
	ImageColorBrightness(&mapNight, -80);
	Texture2D mapNightTexture = LoadTextureFromImage(mapNight);
	Vector2 mapNightPos{startWidth,startHeight};
	// character
	Texture2D character = LoadTexture("hero-walk.png");
	Vector2 characterPos{0.0,0.0};
	// set target fps
    SetTargetFPS(60);
	// change the map if it night or daytime
	bool isDayTime{true};
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);
		Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
		if (Vector2Length(direction) != 0.0)
        {
            // set mapPos = mapPos - direction
            
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), 4));
        }

		// Hide cursor
		HideCursor();
		if(isDayTime){
		// draw the map for daytime
		DrawTextureEx(map,mapPos,0.0, 3.0, WHITE);
		} else {
		// draw the map for nighttime
		DrawTextureEx(mapNightTexture,mapNightPos,0.0, 0.0, WHITE);
		}
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
