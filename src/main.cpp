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
#include "Conversation.h"

int main()
{
	// window size
	int screenWidth = 1000;
	int screenHeight = 600;
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "FROM");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	InitAudioDevice();
	// music in game
	// Music intro = LoadMusicStream("rise-up.mp3");
	// PlayMusicStream(intro);
	// draw hero
	Character hero{screenWidth, screenHeight};
	hero.setWorldPos(400.f, 100.f);
	// draw NPCs
	NPC boyd{Vector2{2000.f, 1270.f}, LoadTexture("boyd-walk.png"), LoadTexture("boyd-hurt.png"), true};
	NPC kid{Vector2{3550.f, 480.f}, LoadTexture("kid-walk.png"), LoadTexture("kid-jump.png"), false};
	NPC sara{Vector2{1080.f, 2700.f}, LoadTexture("sara-walk.png"), LoadTexture("sara-hurt.png"), true};
	NPC yellow{Vector2{700.f, 450.f}, LoadTexture("yellow-walk.png"), LoadTexture("yellow-magic.png"), true};
	NPC *npcs[4]{
		&boyd,
		&kid,
		&sara,
		&yellow};
	for (auto npc : npcs)
	{
		npc->setTarget(&hero);
	}
	// Add the dialogues to npcs dialogue vector for the first day in the game
	boyd.addDialog(boydDialoguesDayOne);
	kid.addDialog(kidDialogues);
	sara.addDialog(saraDialoguesDayOne);
	// Create the maps and positions
	Texture2D map = LoadTexture("fromville.png");
	Vector2 mapPos{0.f, 0.f};
	const float mapScale{2.0};
	Image mapNight = LoadImageFromTexture(map);
	ImageColorBrightness(&mapNight, -80);
	Texture2D mapNightTexture = LoadTextureFromImage(mapNight);
	Texture2D mapOutsideTown = LoadTexture("fromville_outside_one.png");
	Image mapOutside = LoadImageFromTexture(mapOutsideTown);
	ImageColorBrightness(&mapOutside, -80);
	Texture2D mapOutsideNight = LoadTextureFromImage(mapOutside);
	Texture2D house_two_interior = LoadTexture("house_two_interior.png");
	Texture2D temple_interior = LoadTexture("temple_interior.png");
	Texture2D start = LoadTexture("start.png");
	Image startNighttime = LoadImageFromTexture(start);
	ImageColorBrightness(&startNighttime, -80);
	Texture2D startNight = LoadTextureFromImage(startNighttime);
	Texture2D house_one_interior = LoadTexture("house_interior.png");
	Texture2D house_one_interior_floor = LoadTexture("house_interior_floor.png");
	Texture2D cave = LoadTexture("cave.png");
	Texture2D caveEntrance = LoadTexture("cave_entrance.png");
	Image caveEntranceNight = LoadImageFromTexture(caveEntrance);
	ImageColorBrightness(&caveEntranceNight, -80);
	Texture2D caveEntranceNightMap = LoadTextureFromImage(caveEntranceNight);
	Texture2D maps[13]{
		map,
		mapNightTexture,
		temple_interior,
		house_two_interior,
		mapOutsideTown,
		start,
		mapOutsideNight,
		startNight,
		house_one_interior,
		house_one_interior_floor,
		cave,
		caveEntrance,
		caveEntranceNightMap};
	Vector2 interiorPos = {
		static_cast<float>(screenWidth) / 2 - maps[2].width * 1.5f,
		static_cast<float>(screenHeight) / 2 - maps[2].height * 1.5f};
	Vector2 outsideTownPos = {
		screenWidth - maps[4].width * mapScale,
		screenHeight - maps[4].height * mapScale};
	Vector2 startPos{
		screenWidth - maps[5].width * mapScale,
		screenHeight - maps[5].height * mapScale};
	// Render props
	Prop props[8]{
		Prop{Vector2{1800.f, 10.f}, LoadTexture("house.png"), 3.f, true,-20,10,0},
		Prop{Vector2{1300.f, 50.f}, LoadTexture("temple.png"), 4.f, true,55,50,80},
		Prop{Vector2{3100.f, 0.f}, LoadTexture("house_type.png"), 0.5, true,55,40,40},
		Prop{Vector2{700.f, 600.f}, LoadTexture("house-3.png"), 1.f, true,20,180,350},
		Prop{Vector2{1400.f, 750.f}, LoadTexture("house-4.png"), 1.f, true,-40,130,255},
		Prop{Vector2{570.f, -150.f}, LoadTexture("fallen_tree.png"), 1.f, false,0,0,0},
		Prop{Vector2{600.f, 380.f}, LoadTexture("car.png"), 8.f, true,40,0,0},
		Prop{Vector2{1330.f, 1850.f}, LoadTexture("bottle-tree.png"), 1.5, false,0,0,0},
	};
	// render enemy
	Enemy she{Vector2{0.f, 1080.f}, LoadTexture("monster-she-walk.png"), LoadTexture("monster-she-attack.png")};
	Enemy he{Vector2{3100.f, 1080.f}, LoadTexture("monster-he-walk.png"), LoadTexture("monster-he-attack.png")};
	Enemy monster{Vector2{2100.f, 1000.f}, LoadTexture("monster-walk.png"), LoadTexture("monster-attack.png")};
	Enemy monster_he{Vector2{400.f, 100.f}, LoadTexture("monster_he_he.png"), LoadTexture("monster_he_he.png")};
	Enemy *enemies[]{
		&she,
		&he,
		&monster};
	for (auto enemy : enemies)
	{
		enemy->setTarget(&hero);
	}
	// Check if character is inside a house / outside the town / starting the game
	bool isInTown{true};
	bool isInside{};
	bool isOutsideTown{};
	bool isGameStart{};
	bool isUpstairs{};
	bool isInCave{};
	bool isOutsideCave{};
	// Positions of the buildings where player can enter
	int temple_entry_width_min = 1000;
	int temple_entry_width_max = 1050;
	int temple_entry_height = 179;
	int house_one_entry_width_min = 1410;
	int house_one_entry_width_max = 1455;
	int house_one_entry_height = 220;
	int house_two_entry_width_min = 2810;
	int house_two_entry_width_max = 2870;
	int house_two_entry_height = 30;
	int town_exit_width_min = 2100;
	int town_exit_width_max = 2530;
	int town_exit_height = 10;
	enum InteriorType
	{
		NONE,
		HOUSE_ONE,
		HOUSE_TWO,
		TEMPLE
	};
	InteriorType currentInterior = NONE;
	int daysSurvived = 0;
	double lastDayTriggerTime = 0.0;

	// set target fps
	SetTargetFPS(60);
	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		// drawing
		BeginDrawing();
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);
		// UpdateMusicStream(intro);

		interiorPos = Vector2Scale(hero.getWorldPos(), -1.f);
		mapPos = Vector2Scale(hero.getWorldPos(), -1.f);
		outsideTownPos = Vector2Scale(hero.getWorldPos(), -1.f);
		startPos = Vector2Scale(hero.getWorldPos(), -1.f);
		// counting the time since gamestart and days survived
		double time = GetTime();
		if (time - lastDayTriggerTime >= 40.0)
		{
			daysSurvived++;
			lastDayTriggerTime = time;
		}
		// change the map if it night or daytime
		bool isDayTime = fmod(GetTime(), 40.0) < 20.0;
		// Beginning of the game
		if (isGameStart)
		{
			if (isDayTime)
			{
				DrawTextureEx(maps[5], startPos, 0.0, mapScale, WHITE);
			}
			else
			{
				DrawTextureEx(maps[7], startPos, 0.0, mapScale, WHITE);
			}
			props[6].Render(hero.getWorldPos());
			props[7].Render(hero.getWorldPos());
			if (CheckCollisionRecs(props[7].GetCollisionRec(hero.getWorldPos()),
								   hero.GetCollisionRec()))
			{
				hero.undoMovement();
			}
			if (
				hero.getWorldPos().x < 77.f ||
				hero.getWorldPos().y < 100.f ||
				hero.getWorldPos().x > 739 ||
				hero.getWorldPos().y > 1415)
			{
				hero.undoMovement();
			}
			if (hero.getWorldPos().y >= 1410)
			{
				DrawText("Press E to enter the town", 250, 250, 20, BLACK);
				if (IsKeyPressed(KEY_E))
				{
					isGameStart = false;
					isInTown = true;
					hero.setWorldPos(230.f, 120.f);
				}
			}
			hero.tick(GetFrameTime());
		}

		// World map changing between daytime/nighttime
		else if (isInTown)
		{

			if (isDayTime)
			{
				// draw the map for daytime
				DrawTextureEx(maps[0], mapPos, 0.0, mapScale, WHITE);
			}
			else
			{
				// draw the map for nighttime
				DrawTextureEx(maps[1], mapPos, 0.0, mapScale, WHITE);
				// Set collision with enemies
				for (auto enemy : enemies)
				{
					enemy->tick(GetFrameTime());
					if (CheckCollisionRecs(enemy->GetCollisionRec(), hero.GetCollisionRec()))
					{
						hero.setAlive(true);
					}
				}
			}

			if (hero.getWorldPos().x > 14 && hero.getWorldPos().x < 410 &&
				hero.getWorldPos().y < 120)
			{
				DrawText("Press E to go back to the car.", 250, 250, 20, BLACK);
				if (IsKeyPressed(KEY_E))
				{
					isGameStart = true;
					isInTown = false;
					hero.setWorldPos(300.f, 1400.f);
				}
			}
			if (hero.getWorldPos().x >= town_exit_width_min && hero.getWorldPos().x <= town_exit_width_max &&
				hero.getWorldPos().y <= town_exit_height)
			{
				DrawText("Press E to leave the town", 250, 250, 20, BLACK);
				if (IsKeyPressed(KEY_E))
				{
					isOutsideTown = true;
					isInTown = false;
					hero.setWorldPos(300.f, 1442.f);
				}
			}
			if (hero.getWorldPos().x > 2100 && hero.getWorldPos().x < 2520 &&
				hero.getWorldPos().y > 3400)
			{
				DrawText("Press E to leave the town", 250, 250, 20, BLACK);
				if (IsKeyPressed(KEY_E))
				{
					isOutsideTown = true;
					isInTown = false;
					hero.setWorldPos(340.f, 188.f);
				}
			}
			
			// draw props
			for (int i = 0; i < 3; i++)
			{
				props[i].Render(hero.getWorldPos());
			}
			if (hero.getWorldPos().x < 50.f || hero.getWorldPos().y < 0.f ||
				hero.getWorldPos().x + screenWidth > maps[0].width * mapScale ||
				hero.getWorldPos().y + screenHeight > maps[0].height * mapScale ||
				hero.getWorldPos().x >= 2930 && hero.getWorldPos().y > 35 && hero.getWorldPos().y < 345)
			{
				conversation("There must be a way out.", hero.getScreenPos().x, hero.getScreenPos().y);
				hero.undoMovement();
			}
			hero.tick(GetFrameTime());
			props[3].Render(hero.getWorldPos());
			props[4].Render(hero.getWorldPos());
			// check prop collision
			for (int i = 0; i < 5; i++)
			{
				if (CheckCollisionRecs(props[i].GetCollisionRec(hero.getWorldPos()),
									   hero.GetCollisionRec()))
				{
					hero.undoMovement();
				}
				for (auto enemy : enemies)
				{
					if (CheckCollisionRecs(props[i].GetCollisionRec(hero.getWorldPos()), enemy->GetCollisionRec()))
					{
						enemy->undoMovement();
					}
				}
				for (auto npc : npcs)
				{
					if (CheckCollisionRecs(props[i].GetCollisionRec(hero.getWorldPos()), npc->GetCollisionRec()))
					{
						npc->undoMovement();
					}
				}
			}
			for (auto npc : npcs)
			{
				npc->isDay = isDayTime;
				npc->tick(GetFrameTime());
				if (IsKeyPressed(KEY_E))
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
			if (hero.getWorldPos().x >= house_one_entry_width_min && hero.getWorldPos().x <= house_one_entry_width_max &&
					hero.getWorldPos().y <= house_one_entry_height ||
				hero.getWorldPos().x >= house_two_entry_width_min && hero.getWorldPos().x <= house_two_entry_width_max &&
					hero.getWorldPos().y <= house_two_entry_height ||
				hero.getWorldPos().x >= temple_entry_width_min &&
					hero.getWorldPos().x <= temple_entry_width_max && hero.getWorldPos().y <= temple_entry_height)
			{
				DrawText("Press E to enter the house", 250, 250, 20, BLACK);
				if (IsKeyPressed(KEY_E))
				{
					if (hero.getWorldPos().x >= house_one_entry_width_min && hero.getWorldPos().x <= house_one_entry_width_max &&
						hero.getWorldPos().y <= house_one_entry_height)
					{
						currentInterior = HOUSE_ONE;
						hero.setWorldPos(-387.f, 320.f);
					}
					if (hero.getWorldPos().x >= house_two_entry_width_min && hero.getWorldPos().x <= house_two_entry_width_max &&
						hero.getWorldPos().y <= house_two_entry_height)
					{
						currentInterior = HOUSE_TWO;
						hero.setWorldPos(-70.f, 320.f);
					}
					if (hero.getWorldPos().x >= temple_entry_width_min &&
						hero.getWorldPos().x <= temple_entry_width_max && hero.getWorldPos().y <= temple_entry_height)
					{
						currentInterior = TEMPLE;
						hero.setWorldPos(0.f, 270.f);
					}
					isInside = true;
					isInTown = false;
				}
			}
			
		}
		// Maps if the hero enters into a building
		else if (isInside && !isUpstairs)
		{
			switch (currentInterior)
			{
			case HOUSE_ONE:
				DrawTextureEx(maps[8], interiorPos, 0.0, 1.5, WHITE);
				if (hero.getWorldPos().x < -450 || hero.getWorldPos().x > 156 ||
					hero.getWorldPos().y > 320 || hero.getWorldPos().y < -230 ||
					hero.getWorldPos().x > 111 && hero.getWorldPos().y > 180 ||
					hero.getWorldPos().x > -24 && hero.getWorldPos().x < 105 &&
						hero.getWorldPos().y > 152 && hero.getWorldPos().y < 284 ||
					hero.getWorldPos().x > -400 && hero.getWorldPos().x < -305 &&
						hero.getWorldPos().y > 40 && hero.getWorldPos().y < 145 ||
					hero.getWorldPos().x > -221 && hero.getWorldPos().x < -116 &&
						hero.getWorldPos().y < 280)
				{
					hero.undoMovement();
				}
				if (hero.getWorldPos().x < -420 && hero.getWorldPos().y < -185)
				{
					DrawText("Press E to go upstairs.", 250, 250, 20, BLACK);
					if (IsKeyPressed(KEY_E))
					{
						isUpstairs = true;
						currentInterior = NONE;
						isInside = false;
						hero.setWorldPos(-350.f, -177.f);
					}
				}
				if (hero.getWorldPos().x > -415 && hero.getWorldPos().x < -350 && hero.getWorldPos().y > 300)
				{
					DrawText("Press E to exit.", 250, 250, 20, BLACK);
					if (IsKeyPressed(KEY_E))
					{
						isInside = false;
						currentInterior = NONE;
						isInTown = true;
						hero.setWorldPos(1430.f, 235.f);
					}
				}
				break;
			case HOUSE_TWO:
				DrawTextureEx(maps[3], interiorPos, 0.0, 1.5, WHITE);

				if (hero.getWorldPos().x < -456 || hero.getWorldPos().x > 160 ||
					hero.getWorldPos().y > 320 || hero.getWorldPos().y < -270)
				{
					conversation("Is anybody here?", hero.getScreenPos().x, hero.getScreenPos().y);
					hero.undoMovement();
				}

				if (hero.getWorldPos().x >= -134 && hero.getWorldPos().x <= -23 &&
					hero.getWorldPos().y >= 310)
				{
					DrawText("Press E to exit the house", 250, 250, 20, WHITE);
					if (IsKeyPressed(KEY_E))
					{
						isInside = false;
						isInTown = true;
						currentInterior = NONE;
						hero.setWorldPos(2830, 30);
					}
				}

				break;
			case TEMPLE:
				DrawTextureEx(maps[2], interiorPos, 0.0, 1.5, WHITE);
				if (hero.getWorldPos().x < -390 || hero.getWorldPos().x > 102 ||
					hero.getWorldPos().y > 270 || hero.getWorldPos().y < -200)
				{

					hero.undoMovement();
				}
				if (hero.getWorldPos().x >= -28 && hero.getWorldPos().x <= 28 &&
					hero.getWorldPos().y >= 260)
				{
					DrawText("Press E to exit the temple", 250, 250, 20, WHITE);
					if (IsKeyPressed(KEY_E))
					{
						isInside = false;
						currentInterior = NONE;
						isInTown = true;
						hero.setWorldPos(1020.f, 179.f);
					}
				}
				break;
			default:
				break;
			}
			hero.tick(GetFrameTime());
		}
		else if (isUpstairs)
		{
			DrawTextureEx(maps[9], interiorPos, 0.0, mapScale, WHITE);
			if (hero.getWorldPos().x < -439 || hero.getWorldPos().x > -85 ||
				hero.getWorldPos().y > 54 || hero.getWorldPos().y < -220 ||
				hero.getWorldPos().x > -185 && hero.getWorldPos().y < -90)
			{
				hero.undoMovement();
			}
			if (hero.getWorldPos().x < -339 && hero.getWorldPos().y > -201 &&
				hero.getWorldPos().y < -135)
			{
				DrawText("Press E to go downstairs.", 250, 250, 20, BLACK);
				if (IsKeyPressed(KEY_E))
				{
					isUpstairs = false;
					currentInterior = HOUSE_ONE;
					isInside = true;
					hero.setWorldPos(-449.f, -198.f);
				}
			}
			hero.tick(GetFrameTime());
		}
		// Map if hero tries to leave the town
		else if (isOutsideTown)
		{
			if (isDayTime)
			{
				DrawTextureEx(maps[4], outsideTownPos, 0.0, mapScale, WHITE);
			}
			else
			{
				DrawTextureEx(maps[6], outsideTownPos, 0.0, mapScale, WHITE);
			}
			if (hero.getWorldPos().x < 70 || hero.getWorldPos().x > 1043 | hero.getWorldPos().y > 1442 || hero.getWorldPos().y < 0)
			{
				hero.undoMovement();
			}
			if (hero.getWorldPos().x < 95 && hero.getWorldPos().y > 715 &&
				hero.getWorldPos().y < 870)
			{
				conversation("Where does this road lead?", hero.getScreenPos().x, hero.getScreenPos().y);
				if (IsKeyPressed(KEY_E))
				{
					isOutsideCave = true;
					isOutsideTown = false;
					hero.setWorldPos(1260.f, 785.f);
				}
			}
			if (hero.getWorldPos().y > 1430 && hero.getWorldPos().x < 600)
			{
				DrawText("Press E to return to the town", 250, 250, 20, BLACK);
				if (IsKeyPressed(KEY_E))
				{
					isOutsideTown = false;
					isInTown = true;
					hero.setWorldPos(2330, 30);
				}
			}
			if (hero.getWorldPos().y < 10 && hero.getWorldPos().x < 600)
			{
				DrawText("Press E to exit!", 250, 250, 20, BLACK);
				if (IsKeyPressed(KEY_E))
				{
					isOutsideTown = false;
					isGameStart = true;
					hero.setWorldPos(400.f, 1330.f);
				}
			}
			hero.tick(GetFrameTime());
		}
		else if (isOutsideCave)
		{
			if (isDayTime)
			{
				DrawTextureEx(maps[11], outsideTownPos, 0.0, 3.f, WHITE);
			}
			else
			{
				DrawTextureEx(maps[12], outsideTownPos, 0.0, 3.f, WHITE);
			}
			hero.tick(GetFrameTime());
			props[7].Render(hero.getWorldPos());
			if (CheckCollisionRecs(props[2].GetCollisionRec(hero.getWorldPos()),
								   hero.GetCollisionRec()))
			{
				hero.undoMovement();
			}
			if (hero.getWorldPos().x > 1295 ||
				hero.getWorldPos().y < 400 || hero.getWorldPos().x < 90 ||
				hero.getWorldPos().y > 2010)
			{
				hero.undoMovement();
			}
			if (hero.getWorldPos().x < 690 && hero.getWorldPos().x > 640 &&
				hero.getWorldPos().y < 435)
			{
				conversation("It's too dark in there! Can't see anything!", hero.getScreenPos().x, hero.getScreenPos().y);
			}
			if (hero.getWorldPos().x > 1270 && hero.getWorldPos().y > 720 && hero.getWorldPos().y < 840)
			{
				conversation("I should go back to the road.", hero.getScreenPos().x, hero.getScreenPos().y);
				if (IsKeyPressed(KEY_E))
				{
					isOutsideCave = false;
					isOutsideTown = true;
					hero.setWorldPos(90.f, 750.f);
				}
			}
		}

		DrawText(TextFormat("Time %.2f", time), 50, 50, 20, RED);
		DrawText(TextFormat("Days Survived: %i", daysSurvived), 150, 50, 20, RED);
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
