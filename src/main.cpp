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
#include "NPC.h"
#include "Dialogues.h"

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
	// draw hero
	Character hero{screenWidth, screenHeight};
	// draw NPCs
	NPC boyd{Vector2{1850.f, 1270.f}, LoadTexture("boyd-walk.png"), LoadTexture("boyd-hurt.png"), true};
	NPC kid{Vector2{3550.f, 480.f}, LoadTexture("kid-walk.png"), LoadTexture("kid-jump.png"), false};
	NPC *npcs[2]{
		&boyd,
		&kid};
	for (auto npc : npcs)
	{
		npc->setTarget(&hero);
	}
	for (auto dialogue : boydDialogues)
	{
		boyd.addDialog(dialogue);
	};
	// Load the map for day time
	Texture2D map = LoadTexture("fromville.png");
	Vector2 mapPos{entryWidth, entryHeight};
	const float mapScale{2.0};
	// Create a map for nighttime - same map but with manipulated brightness
	Image mapNight = LoadImageFromTexture(map);
	ImageColorBrightness(&mapNight, -80);
	Texture2D mapNightTexture = LoadTextureFromImage(mapNight);
	// Render props
	Prop props[2]{
		Prop{Vector2{1800.f, 10.f}, LoadTexture("house.png"), 3.f},
		Prop{Vector2{1300.f, 50.f}, LoadTexture("temple.png"), 4.f},
	};
	// render enemy
	Enemy she{Vector2{0.f, 1080.f}, LoadTexture("monster-she-walk.png"), LoadTexture("monster-she-attack.png")};
	Enemy he{Vector2{3100.f, 1080.f}, LoadTexture("monster-he-walk.png"), LoadTexture("monster-he-attack.png")};
	Enemy monster{Vector2{2100.f, 1000.f}, LoadTexture("monster-walk.png"), LoadTexture("monster-attack.png")};
	Enemy *enemies[]{
		&she,
		&he,
		&monster};
	for (auto enemy : enemies)
	{
		enemy->setTarget(&hero);
	}
	// set target fps
	SetTargetFPS(60);
	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();
		// counting the time since gamestart
		double time = GetTime();
		// change the map if it night or daytime
		bool isDayTime = fmod(GetTime(), 120.0) < 60.0;
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
			for (auto enemy : enemies)
			{
				enemy->tick(GetFrameTime());
				if (CheckCollisionRecs(enemy->GetCollisionRec(), hero.GetCollisionRec()))
				{
					hero.setAlive(true);
				}
			}
		}
		// draw props
		for (auto prop : props)
		{
			prop.Render(hero.getWorldPos());
		}
		hero.tick(GetFrameTime());
		if (hero.getWorldPos().x < 0.f || hero.getWorldPos().y < 0.f ||
			hero.getWorldPos().x + screenWidth > map.width * mapScale ||
			hero.getWorldPos().y + screenHeight > map.height * mapScale - 30 ||
			hero.getWorldPos().x >= 2930 && hero.getWorldPos().y > 35 && hero.getWorldPos().y < 345)
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
			for (auto enemy : enemies)
			{
				if (CheckCollisionRecs(prop.GetCollisionRec(hero.getWorldPos()), enemy->GetCollisionRec()))
				{
					enemy->undoMovement();
				}
			}
			for (auto npc : npcs)
			{
				if (CheckCollisionRecs(prop.GetCollisionRec(hero.getWorldPos()), npc->GetCollisionRec()))
				{
					npc->undoMovement();
				}
			}
		}
		for (auto npc : npcs)
		{
			npc->isDay = isDayTime;
			npc->tick(GetFrameTime());
			if (IsKeyPressed(KEY_E) && Vector2Distance(npc->getScreenPos(), hero.getScreenPos()) < 150.f)
			{
				npc->talk();
				npc->setInteractionCount();
			}
			if (CheckCollisionRecs(npc->GetCollisionRec(), hero.GetCollisionRec()))
			{
				hero.undoMovement();
				npc->undoMovement();
			}
			
		}
	

	DrawText(TextFormat("Time %.2f", time), 50, 50, 20, RED);
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
