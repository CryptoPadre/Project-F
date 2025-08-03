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
	// draw NPCs
	// yellow original pos 1200 2100
	NPC boyd{Vector2{1000.f, 700.f}, LoadTexture("boyd-walk.png"), LoadTexture("boyd-hurt.png"), LoadTexture("boyd-hurt.png"), true};
	NPC sara{Vector2{1200.f, 670.f}, LoadTexture("sara-walk.png"), LoadTexture("sara-hurt.png"), LoadTexture("sara-hurt.png"), true};
	NPC kid{Vector2{1150.f, 1300.f}, LoadTexture("kid-walk.png"), LoadTexture("kid-jump.png"), LoadTexture("kid-jump.png"), false};
	NPC yellow{Vector2{1200.f, 2100.f}, LoadTexture("yellow-walk.png"), LoadTexture("yellow-magic.png"), LoadTexture("yellow-attack.png"), true};
	NPC woman{Vector2{150.f, 250.f}, LoadTexture("woman-hurt.png"), LoadTexture("woman-hurt.png"), LoadTexture("woman-hurt.png"), true};
	NPC baby{Vector2{210.f, 250.f}, LoadTexture("baby-walk.png"), LoadTexture("baby-hurt.png"), LoadTexture("baby-attack.png"), false};
	NPC jade{Vector2{2000.f, 2000.f}, LoadTexture("jade-walk.png"), LoadTexture("jade-hurt.png"), LoadTexture("jade-hurt.png"), true};
	NPC *npcs[7]{
		&boyd,
		&sara,
		&kid,
		&yellow,
		&woman,
		&baby,
		&jade};
	for (auto npc : npcs)
	{
		npc->setTarget(&hero);
	}
	npcs[4]->isInHouse = true;
	npcs[4]->setCurrentFrame(2);
	npcs[3]->setCanAttack(true);
	npcs[5]->setCanAttack(true);
	// Add the dialogues to npcs dialogue vector for the first day in the game
	boyd.addDialog(boydDialoguesDayOne);
	kid.addDialog(kidDialogues);
	sara.addDialog(saraDialoguesDayOne);
	yellow.addDialog(yellowDialogByTree);
	woman.addDialog(womanInTheHouse);
	jade.addDialog(jadeDialog);
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
	Texture2D caveEntrance = LoadTexture("cave_entrance.png");
	Image caveEntranceNight = LoadImageFromTexture(caveEntrance);
	ImageColorBrightness(&caveEntranceNight, -80);
	Texture2D caveEntranceNightMap = LoadTextureFromImage(caveEntranceNight);
	Texture2D cave = LoadTexture("cave.png");
	Image caveDark = LoadImageFromTexture(cave);
	ImageColorBrightness(&caveDark, -270);
	Texture2D caveDarkMap = LoadTextureFromImage(caveDark);
	Texture2D endgame = LoadTexture("endgame.png");
	Texture2D gameOver = LoadTexture("game_over.png");
	Texture2D end = LoadTexture("end.png");
	Texture2D secretRoom = LoadTexture("secret_room.png");
	Texture2D sarasHouse = LoadTexture("saras-house.png");
	Texture2D maps[19]{
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
		caveEntranceNightMap,
		caveDarkMap,
		endgame,
		gameOver,
		end,
		secretRoom,
		sarasHouse};
	Vector2 interiorPos = {
		static_cast<float>(screenWidth) / 2 - maps[2].width * 1.5f,
		static_cast<float>(screenHeight) / 2 - maps[2].height * 1.5f};
	Vector2 outsideTownPos = {
		screenWidth - maps[4].width * mapScale,
		screenHeight - maps[4].height * mapScale};
	Vector2 startPos{
		screenWidth - maps[5].width * mapScale,
		screenHeight - maps[5].height * mapScale};
	Vector2 gameOverScreenPos{
		screenWidth - maps[15].width * mapScale,
		screenHeight - maps[15].height * mapScale};
	Rectangle srcEnd = {0, 0, (float)maps[16].width, (float)maps[16].height};
	Rectangle destEnd = {0, 0, (float)screenWidth, (float)screenHeight};
	// Render props
	Prop props[35]{
		Prop{Vector2{1800.f, 10.f}, LoadTexture("house.png"), 3.f, true, -20, 0, 10, 0},
		Prop{Vector2{350.f, 180.f}, LoadTexture("temple.png"), 4.f, true, 55, 0, 50, 80},
		Prop{Vector2{780.f, 190.f}, LoadTexture("house_type.png"), 0.6, true, 55, 0, 40, 40},
		Prop{Vector2{1200.f, 190.f}, LoadTexture("house-4.png"), 0.8, true, 45, 0, 100, 200},
		Prop{Vector2{1050.f, 30.f}, LoadTexture("house-3.png"), 1.f, true, -20, 0, 10, 0},
		Prop{Vector2{570.f, -150.f}, LoadTexture("fallen_tree.png"), 1.f, false, 0, 0, 0, 0},
		Prop{Vector2{520.f, 330.f}, LoadTexture("car-2.png"), 0.35, false, 100, 40, 0, 0},
		Prop{Vector2{1330.f, 1850.f}, LoadTexture("bottle-tree.png"), 1.5, false, 30, 30, 0, 0},
		Prop{Vector2{1590.f, 480.f}, LoadTexture("ghost.png"), 0.5, false, 30, 30, 0, 0},
		Prop{Vector2{500.f, 220.f}, LoadTexture("hole.png"), 0.5, false, 30, 30, 0, 0},
		Prop{Vector2{490.f, 2300.f}, LoadTexture("ghost_kids.png"), 0.3, false, 140, 100, 0, 0},
		Prop{Vector2{900.f, 2220.f}, LoadTexture("ghost_kid.png"), 0.2, false, 140, 100, 0, 0},
		Prop{Vector2{0.f, 0.f}, LoadTexture("talisman.png"), 3.f, false, 0, 0, 0, 0},
		Prop{Vector2{0.f, 0.f}, LoadTexture("flashlight.png"), 0.25, false, 0, 0, 0, 0},
		Prop{Vector2{0.f, 0.f}, LoadTexture("key.png"), 0.4, false, 0, 0, 0, 0},
		Prop{Vector2{600.f, 2340.f}, LoadTexture("hole.png"), 0.5, false, 30, 30, 0, 0},
		Prop{Vector2{0.f, 0.f}, LoadTexture("first-aid-kit.png"), 0.2, false, 0, 0, 0, 0},
		Prop{Vector2{0.f, 0.f}, LoadTexture("scroll.png"), 0.2, false, 0, 0, 0, 0},
		Prop{Vector2{640.f, 2600.f}, LoadTexture("scroll.png"), 0.1, false, 0, 0, 0, 0},
		Prop{Vector2{260.f, 250.f}, LoadTexture("old-house.png"), 1.f, false, 0, 0, 0, 0},
		Prop{Vector2{130.f, -120.f}, LoadTexture("wardrobe.png"), 0.5f, false, 0, 0, 0, 0},
		Prop{Vector2{300.f, 25.f}, LoadTexture("wardrobe-olive.png"), 0.5, false, 0, 0, 0, 0},
		Prop{Vector2{300.f, -120.f}, LoadTexture("wardrobe-red.png"), 0.5, false, 0, 0, 0, 0},
		Prop{Vector2{0.f, 0.f}, LoadTexture("dagger.png"), 0.25, false, 0, 0, 0, 0},
		Prop{Vector2{0.f, 0.f}, LoadTexture("rusty-key.png"), 0.25, false, 0, 0, 0, 0},
		Prop{Vector2{530.f, 120.f}, LoadTexture("box-locked.png"), 0.25, false, 0, 0, 0, 0},
		Prop{Vector2{530.f, 120.f}, LoadTexture("box-open.png"), 0.25, false, 0, 0, 0, 0},
		Prop{Vector2{140.f, 30.f}, LoadTexture("chair.png"), 0.4, false, 30, 0, 10, 5},
		Prop{Vector2{385.f, -180.f}, LoadTexture("clock.png"), 0.6, false, 0, 0, 0, 0},
		Prop{Vector2{100.f, 130.f}, LoadTexture("desk.png"), 0.6, false, 0, 0, 0, 0},
		Prop{Vector2{550.f, 20.f}, LoadTexture("desk-2.png"), 0.6, false, 70, 0, 0, 0},
		Prop{Vector2{800.f, 600.f}, LoadTexture("desk-3.png"), 0.5, false, 0, 0, 0, 0},
		Prop{Vector2{500.f, 220.f}, LoadTexture("ladder.png"), 0.4, false, 0, 0, 0, 0},
		Prop{Vector2{65.f, 150.f}, LoadTexture("stairs.png"), 0.4, false, 0, 0, 0, 0},
		Prop{Vector2{300.f, -40.f}, LoadTexture("stove.png"), 0.6, false, 0, 0, 20, -10}};
	// render enemy
	// 410 , 330 extra for cave monster
	Enemy she{Vector2{2000.f, 1000.f}, LoadTexture("monster-she-walk.png"), LoadTexture("monster-she-attack.png"), LoadTexture("cave-monster-sleep.png"), false};
	Enemy he{Vector2{2200.f, 1000.f}, LoadTexture("monster-he-walk.png"), LoadTexture("monster-he-attack.png"), LoadTexture("cave-monster-sleep.png"), false};
	Enemy monster{Vector2{2100.f, 1000.f}, LoadTexture("monster-walk.png"), LoadTexture("monster-attack.png"), LoadTexture("cave-monster-sleep.png"), false};
	Enemy caveMonster{Vector2{610.f, 650.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster1{Vector2{490.f, 1440.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster2{Vector2{560.f, 1340.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster3{Vector2{970.f, 1650.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster4{Vector2{1080.f, 1550.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster5{Vector2{1320.f, 2480.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster6{Vector2{2100.f, 2300.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster7{Vector2{700.f, 2390.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster8{Vector2{2400.f, 1720.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster9{Vector2{1150.f, 1050.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster10{Vector2{1350.f, 1150.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster11{Vector2{2330.f, 1200.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster12{Vector2{2450.f, 700.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster13{Vector2{2250.f, 950.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster14{Vector2{1550.f, 2650.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster15{Vector2{1050.f, 2400.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster16{Vector2{1850.f, 1200.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster17{Vector2{1950.f, 2200.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster18{Vector2{1700.f, 1850.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster19{Vector2{1700.f, 1850.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster20{Vector2{1700.f, 1850.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster21{Vector2{1700.f, 1850.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster22{Vector2{1700.f, 1850.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster23{Vector2{1700.f, 1850.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster24{Vector2{1700.f, 1850.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster25{Vector2{1700.f, 1850.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster26{Vector2{1700.f, 1850.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster27{Vector2{1700.f, 1850.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy caveMonster28{Vector2{1700.f, 1850.f}, LoadTexture("cave-monster-walk.png"), LoadTexture("cave-monster-sleep.png"), LoadTexture("cave-monster-sleep.png"), true};
	Enemy *enemies[]{
		&she,
		&he,
		&monster,
		&caveMonster,
		&caveMonster1,
		&caveMonster2,
		&caveMonster3,
		&caveMonster4,
		&caveMonster5,
		&caveMonster6,
		&caveMonster7,
		&caveMonster8,
		&caveMonster9,
		&caveMonster10,
		&caveMonster11,
		&caveMonster12,
		&caveMonster13,
		&caveMonster14,
		&caveMonster15,
		&caveMonster16,
		&caveMonster17,
		&caveMonster18,
		&caveMonster19,
		&caveMonster20,
		&caveMonster21,
		&caveMonster22,
		&caveMonster23,
		&caveMonster24,
		&caveMonster25,
		&caveMonster26,
		&caveMonster27,
		&caveMonster28};
	for (auto enemy : enemies)
	{
		enemy->setTarget(&hero);
		enemy->setCameraTarget(&hero);
	}
 	// 400 200
	hero.setWorldPos(282.f, 12.f);
	// Check if character is inside a house / outside the town / starting the game
	bool isInTown{};
	bool isInside{};
	bool isOutsideTown{};
	bool isGameStart{true};
	bool isGameOver{};
	bool isUpstairs{};
	bool isInCave{};
	bool isOutsideCave{};
	bool isInSecretRoom{};
	bool isInSarasHouse{};
	bool wasInSarasHouse{};
	bool hasFlashlight{};
	bool isEndGame{};
	bool hasStarted{};
	bool isDayTime{true};
	bool hasTalisman{};
	bool hasMedkit{};
	bool hasKey{};
	bool hasScroll{};
	bool hasDagger{};
	bool hasRustyKey{};
	bool talkedToKid{};
	bool boydDialogDayTwo{};
	bool saraDialogDayTwo{};
	bool dialogsAfterFight{};
	bool boydDialogKid{};
	bool boydDialogAfterBook{};
	bool wasInCave{};
	bool isYellowDead{};
	bool metYellow{};
	bool metSara{};
	bool talkedBeforeFight{};
	bool metYellowAtCar{};
	bool talkedToWoman{};
	bool scrollDialogAdded{};
	bool renderEnemy{};
	bool doorUnlocked{};
	bool boxOpen{};
	bool daggerPickedUp{};
	bool hasFallen{};
	bool fellIntoCave{};
	bool yellowStartMapDialogAdded{};
	bool isTheEnd{};

	hero.setHasDagger(hasDagger);
	int endingTitle = 200;
	float leftY = 840;
	float rightY = 1240;

	for (int i = 22; i < 32; i++)
	{
		enemies[i]->isStanding = true;
		enemies[i]->setWorldPos(260.f, leftY);
		leftY += 100;
		if (i > 26)
		{
			enemies[i]->setCurrentRow(1);
			enemies[i]->setWorldPos(680.f, rightY);
			rightY -= 100;
		}
	}

	// Positions of the buildings where player can enter
	int temple_entry_width_min = 50;
	int temple_entry_width_max = 116;
	int temple_entry_height = 280;
	int house_one_entry_width_min = 1410;
	int house_one_entry_width_max = 1455;
	int house_one_entry_height = 220;
	int house_two_entry_width_min = 550;
	int house_two_entry_width_max = 600;
	int house_two_entry_height = 295;
	int town_exit_width_min = 1750;
	int town_exit_height_min = 877;
	int town_exit_height_max = 1417;
	int closed_house_width_min = 935;
	int closed_house_width_max = 1000;
	int closed_house_height = 355;

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

	// counting the conversation of the hero on the start map
	int heroStartMapCounter = 0;
	// counting the end game converstaion with yellow man prefigth
	int endGameConvo = 0;
	// counting the conversation of the hero if interacts with props
	int inCaveCounter = 0;
	// interaction with doors
	int interactionWithDoors = 0;

	int yellowWarningCounter = 0;

	int lockedHouseCounter = 0;

	int outsideHouseCounter = 0;

	int interactionWithScroll = 0;

	int randomValue = GetRandomValue(1, 4);

	int hitCounter = 0;

	int afterFightCounter = 0;

	int templeBookInteraction = 0;

	int startMapCounter = 0;
	// set target fps
	SetTargetFPS(60);
	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{

		// drawing
		BeginDrawing();
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);
		// UpdateMusicStream(intro);
		hero.setIsGettingUp(hasFallen);
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
		if (hasStarted)
		{
			isDayTime = fmod(GetTime(), 40.0) < 20.0;
		}
		if (metYellow && !yellowStartMapDialogAdded)
		{
			npcs[3]->addDialog(yellowDialogStartMap);
			yellowStartMapDialogAdded = true;
		}
		if (templeBookInteraction > 5 && !boydDialogAfterBook)
		{
			npcs[0]->addDialog(boydDialoguesAfterReadingTheBook);
			npcs[0]->setWorldPos(280.f, 500.f);
			boydDialogAfterBook = true;
		}
		if (!boydDialogDayTwo & metSara)
		{
			npcs[0]->addDialog(boydDialoguesDayTwo);
			boydDialogDayTwo = true;
		}
		if (wasInCave && !saraDialogDayTwo && boydDialogDayTwo)
		{
			npcs[1]->addDialog(saraDialoguesDayTwo);
			saraDialogDayTwo = true;
		}
		if (isYellowDead && !dialogsAfterFight)
		{
			npcs[0]->addDialog(boydDialoguesAfterFight);
			npcs[1]->addDialog(saraDialoguesDayAfterFight);
			npcs[4]->addDialog(yellowDialogAfterFight);
			npcs[0]->setWorldPos(700.f, 300.f);
			npcs[0]->setCurrentRow(2);
			dialogsAfterFight = true;
		}
		if (talkedToKid && !boydDialogKid)
		{
			npcs[0]->addDialog(boydDialoguesAfterInteractionWithKid);
			boydDialogKid = true;
		}
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

			props[5].Render(hero.getWorldPos());
			props[6].Render(hero.getWorldPos());

			if (CheckCollisionRecs(props[6].GetCollisionRec(hero.getWorldPos()),
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
					hero.setWorldPos(90.f, 1100.f);
				}
			}
			if (hero.getWorldPos().x > 145 && hero.getWorldPos().x < 300 && hero.getWorldPos().y < 285)
			{
				if (heroStartMapCounter < heroTextStartMap.size())
				{
					conversation(heroTextStartMap[heroStartMapCounter], hero.getScreenPos().x, hero.getScreenPos().y);
					if (IsKeyPressed(KEY_E))
					{

						heroStartMapCounter++;
					}
				}
			}
			if (talkedToKid && !hasDagger)
			{
				npcs[3]->talk();

				if (IsKeyPressed(KEY_E) && npcs[3]->getIsTalking())
				{
					npcs[3]->setInteractionCount();
				}
				if (hero.getWorldPos().y > 420.f && hero.getWorldPos().y < 520.f && yellowWarningCounter <= yellowWarning.size())
				{
					conversation(yellowWarning[yellowWarningCounter], npcs[3]->getScreenPos().x, npcs[3]->getScreenPos().y);
					metYellowAtCar = true;
				}
				if (hero.getWorldPos().y < 370.f)
				{
					npcs[3]->setAttack();
					yellowWarningCounter++;
				}
				npcs[3]->tick(GetFrameTime());
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
			}

			if (hero.getWorldPos().x < 80 &&
				hero.getWorldPos().y > town_exit_height_min &&
				hero.getWorldPos().y < town_exit_height_max)
			{
				DrawText("Press E to go back to the car.", 250, 250, 20, BLACK);
				if (IsKeyPressed(KEY_E))
				{
					isGameStart = true;
					isInTown = false;
					hero.setWorldPos(300.f, 1400.f);
				}
			}
			if (hero.getWorldPos().x > town_exit_width_min &&
				hero.getWorldPos().y > town_exit_height_min && hero.getWorldPos().y < town_exit_height_max)
			{
				if (!hasStarted)
				{
					conversation("I shoud look around in town.", hero.getScreenPos().x, hero.getScreenPos().y);
				}
				else
				{
					conversation("This way I might get back to the car.", hero.getScreenPos().x, hero.getScreenPos().y);
					if (IsKeyPressed(KEY_E))
					{
						isOutsideTown = true;
						isInTown = false;
						hero.setWorldPos(340.f, 188.f);
					}
				}
			}

			// draw props
			for (int i = 0; i < 4; i++)
			{
				props[i].Render(hero.getWorldPos());
			}
			if (hero.getWorldPos().y < 165 || hero.getWorldPos().y > 1411 || hero.getWorldPos().x < 12 ||
				hero.getWorldPos().x + screenWidth > maps[0].width * mapScale ||
				hero.getWorldPos().y + screenHeight > maps[0].height * mapScale)
			{
				hero.undoMovement();
			}
			// render enemies after props to make sure they cannot cross them
			if (!isDayTime)
			{
				// Set collision with enemies
				for (int i = 0; i < 3; i++)
				{
					for (int j = i + 1; j < 3; j++)
					{
						if (CheckCollisionRecs(enemies[i]->GetCollisionRec(), enemies[j]->GetCollisionRec()))
						{
							enemies[i]->resolveCollision(enemies[j]->getWorldPos());
							enemies[j]->resolveCollision(enemies[i]->getWorldPos());
						}
					}
				}
				for (int i = 0; i < 3; i++)
				{
					enemies[i]->tick(GetFrameTime());
					if (Vector2Distance(enemies[i]->getScreenPos(), hero.getScreenPos()) > 150.f)
					{
						conversation("Don't run sweetey!", enemies[i]->getScreenPos().x, enemies[i]->getScreenPos().y);
					}
					if (CheckCollisionRecs(enemies[i]->GetCollisionRec(), hero.GetCollisionRec()))
					{
						hero.setAlive(true);
					}
				}
			}
			if (CheckCollisionRecs(npcs[0]->GetCollisionRec(), hero.GetCollisionRec()))
			{
				hero.undoMovement();
				npcs[0]->undoMovement();
			}
			hero.tick(GetFrameTime());
			if (!boydDialogAfterBook)
			{
				npcs[0]->tick(GetFrameTime());
				npcs[0]->isDay = isDayTime;
				npcs[0]->talk();
			}
			if (IsKeyPressed(KEY_E) && npcs[0]->getIsTalking())
			{
				npcs[0]->setInteractionCount();
			}
			if (boydDialoguesDayOne.size() - 1 == npcs[0]->getInteractionCount())
			{
				hasStarted = true;
				hasTalisman = true;
			}
			// check prop collision
			for (int i = 0; i < 4; i++)
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
			if (hero.getWorldPos().x >= house_two_entry_width_min && hero.getWorldPos().x <= house_two_entry_width_max &&
				hero.getWorldPos().y <= house_two_entry_height)
			{
				conversation(heroInteractionWithDoors[interactionWithDoors], hero.getScreenPos().x, hero.getScreenPos().y);
				if (IsKeyPressed(KEY_E))
				{
					if (hasKey)
					{
						currentInterior = HOUSE_TWO;
						isInside = true;
						isInTown = false;
						hero.setWorldPos(-70.f, 320.f);
						interactionWithDoors = 0;
					}
					else
					{
						isInside = false;
						isInTown = true;
						interactionWithDoors = 1;
					}
				}
			}
			if (hero.getWorldPos().x >= house_one_entry_width_min && hero.getWorldPos().x <= house_one_entry_width_max &&
					hero.getWorldPos().y <= house_one_entry_height ||
				hero.getWorldPos().x >= temple_entry_width_min &&
					hero.getWorldPos().x <= temple_entry_width_max && hero.getWorldPos().y <= temple_entry_height)
			{
				if (!hasStarted)
				{
					conversation("I should talk to that man first.", hero.getScreenPos().x, hero.getScreenPos().y);
				}
				else
				{
					conversation("Let's see what's inside!", hero.getScreenPos().x, hero.getScreenPos().y);

					if (IsKeyPressed(KEY_E))
					{
						if (hero.getWorldPos().x >= house_one_entry_width_min && hero.getWorldPos().x <= house_one_entry_width_max &&
							hero.getWorldPos().y <= house_one_entry_height)
						{

							currentInterior = HOUSE_ONE;
							isInside = true;
							isInTown = false;
							hero.setWorldPos(-387.f, 320.f);
							interactionWithDoors = 0;
						}
						if (hero.getWorldPos().x >= temple_entry_width_min &&
							hero.getWorldPos().x <= temple_entry_width_max && hero.getWorldPos().y <= temple_entry_height)
						{
							currentInterior = TEMPLE;
							isInside = true;
							isInTown = false;
							hero.setWorldPos(0.f, 270.f);
							interactionWithDoors = 0;
						}
					}
				}
			}
			if (hero.getWorldPos().x > closed_house_width_min && hero.getWorldPos().x < closed_house_width_max &&
				hero.getWorldPos().y < closed_house_height)
			{
				if (!doorUnlocked)
				{
					if (lockedHouseCounter < heroInteractionWithDoor2.size())
					{
						conversation(heroInteractionWithDoor2[lockedHouseCounter], hero.getScreenPos().x, hero.getScreenPos().y);
					}
					if (IsKeyPressed(KEY_E) && lockedHouseCounter <= heroInteractionWithDoor2.size() - 1)
					{
						lockedHouseCounter++;
					}
				}
				else
				{
					conversation("Let's look around!", hero.getScreenPos().x, hero.getScreenPos().y);
					if (IsKeyPressed(KEY_E))
					{
						isInTown = false;
						isInSecretRoom = true;
						hero.setWorldPos(-294.f, 56.f);
					}
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
				props[32].Render(hero.getWorldPos());
				if (hero.getWorldPos().x < 140 && hero.getWorldPos().x > -65 && hero.getWorldPos().y > -170)
				{

					conversation("What the hell is that hole?", hero.getScreenPos().x, hero.getScreenPos().y);
				}
				if (hero.getWorldPos().x < 125 && hero.getWorldPos().x > -40 && hero.getWorldPos().y > -160 && hero.getWorldPos().y < 0)
				{
					hero.undoMovement();
				}
				if (hero.getWorldPos().x < 70 && hero.getWorldPos().x > 10 && hero.getWorldPos().y > -180 && hero.getWorldPos().y < -160)
				{
					if (metYellow)
					{
						if (IsKeyPressed(KEY_E))
						{
							currentInterior = NONE;
							isInside = false;
							isInCave = true;
							hasFallen = true;
							fellIntoCave = true;
							hero.setWorldPos(1800.f, 500.f);
							hero.setSpeed(2.f);
						}
					}
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
					if (!isDayTime)
					{
						conversation("They are still outside!", hero.getScreenPos().x, hero.getScreenPos().y);
					}
					else
					{
						conversation("Where should I go now?", hero.getScreenPos().x, hero.getScreenPos().y);
					}
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
						hero.setWorldPos(house_two_entry_width_min, house_two_entry_height);
					}
				}

				props[27].Render(hero.getWorldPos());
				props[30].Render(hero.getWorldPos());
				props[34].Render(hero.getWorldPos());
				if (hero.getWorldPos().x > 65 && hero.getWorldPos().x < 130 && hero.getWorldPos().y < -210)
				{
					conversation("A flashlight! That might come in handy!", hero.getScreenPos().x, hero.getScreenPos().y);
					if (IsKeyPressed(KEY_E))
					{
						hasFlashlight = true;
					}
				}
				npcs[4]->tick(GetFrameTime());
				npcs[4]->talk();
				if (IsKeyPressed(KEY_E) && npcs[4]->getIsTalking())
				{
					npcs[4]->setInteractionCount();
				}
				if (npcs[4]->getInteractionCount() >= womanInTheHouse.size() - 1)
				{
					talkedToWoman = true;
				}
				if (hasMedkit)
				{
					npcs[5]->tick(GetFrameTime());
					if (Vector2Distance(npcs[5]->getScreenPos(), hero.getScreenPos()) < 150.f)
					{
						npcs[5]->setAttack();
					}
					else
					{
						conversation("Moooother!", npcs[5]->getScreenPos().x + 30, npcs[5]->getScreenPos().y + 20);
					}
				}
				if (CheckCollisionRecs(npcs[4]->GetCollisionRec(), hero.GetCollisionRec()))
				{
					hero.undoMovement();
				}
				if (CheckCollisionRecs(props[27].GetCollisionRec(hero.getWorldPos()), hero.GetCollisionRec()))
				{
					hero.undoMovement();
				}
				if (CheckCollisionRecs(props[30].GetCollisionRec(hero.getWorldPos()), hero.GetCollisionRec()))
				{
					hero.undoMovement();
				}
				if (CheckCollisionRecs(props[34].GetCollisionRec(hero.getWorldPos()), hero.GetCollisionRec()))
				{
					hero.undoMovement();
				}

				break;
			case TEMPLE:
				DrawTextureEx(maps[2], interiorPos, 0.0, 1.5, WHITE);
				if (hero.getWorldPos().x < -390 || hero.getWorldPos().x > 102 ||
					hero.getWorldPos().y > 270 || hero.getWorldPos().y < -200 ||
					hero.getWorldPos().x < -255 && hero.getWorldPos().y < -145 ||
					hero.getWorldPos().x > -18 && hero.getWorldPos().x < 90 && hero.getWorldPos().y < -150)
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
						hero.setWorldPos(temple_entry_width_min, temple_entry_height);
					}
				}
				props[21].Render(hero.getWorldPos());
				if (hero.getWorldPos().x > -170 && hero.getWorldPos().x < -130 && hero.getWorldPos().y < -150)
				{
					if (!doorUnlocked)
					{
						conversation("What a nice wardrobe!", hero.getScreenPos().x, hero.getScreenPos().y);
					}
					else
					{
						conversation("I hope it takes me to Narnia!", hero.getScreenPos().x, hero.getScreenPos().y);
						if (IsKeyPressed(KEY_E))
						{
							if (randomValue == 1)
							{
								currentInterior = NONE;
								isInside = false;
								isInSarasHouse = true;
								randomValue = GetRandomValue(1, 2);
								hero.setWorldPos(-150.f, -275.f);
							}
							else
							{
								currentInterior = NONE;
								isInside = false;
								isInSecretRoom = true;
								randomValue = GetRandomValue(1, 2);
								hero.setWorldPos(-316.f, -220.f);
							}
						}
					}
				}
				props[29].Render(hero.getWorldPos());
				if (hero.getWorldPos().x < -300 && hero.getWorldPos().y < -135 && templeBookInteraction <= heroInteractionWithBookInTemple.size() - 1)
				{
					conversation(heroInteractionWithBookInTemple[templeBookInteraction], hero.getScreenPos().x, hero.getScreenPos().y);
					if (IsKeyPressed(KEY_E))
					{
						templeBookInteraction++;
					}
				}
				if (boydDialogAfterBook && !isYellowDead)
				{
					npcs[0]->tick(GetFrameTime());
					npcs[0]->talk();

					if (IsKeyPressed(KEY_E) && npcs[0]->getIsTalking())
					{
						npcs[0]->setInteractionCount();
					}
					if (CheckCollisionRecs(npcs[0]->GetCollisionRec(), hero.GetCollisionRec()))
					{
						hero.undoMovement();
						npcs[0]->undoMovement();
					}
				}
				if (!boxOpen)
				{
					props[25].Render(hero.getWorldPos());
				}
				else
				{
					props[26].Render(hero.getWorldPos());
				}
				if (hero.getWorldPos().x > 20 && hero.getWorldPos().x < 60 && hero.getWorldPos().y < -140)
				{
					if (!boxOpen)
					{
						if (templeBookInteraction > 1 && !hasRustyKey)
						{
							conversation("It must be inside!", hero.getScreenPos().x, hero.getScreenPos().y);
						}
						else if (!boxOpen && hasRustyKey)
						{
							conversation("Let's see if this opens it!", hero.getScreenPos().x, hero.getScreenPos().y);
							if (IsKeyPressed(KEY_E))
							{
								boxOpen = true;
							}
						}
						else
						{
							conversation("I can't open it without a key!", hero.getScreenPos().x, hero.getScreenPos().y);
						}
					}
					else if (boxOpen && !hasDagger)
					{
						conversation("Okay, let's see if Jade's theory is right.", hero.getScreenPos().x, hero.getScreenPos().y);
						if (IsKeyPressed(KEY_E))
						{
							hasDagger = true;
							hero.setHasDagger(hasDagger);
						}
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
			if (hero.getWorldPos().x > -125 && hero.getWorldPos().y > 15)
			{
				conversation("Huh? A purse? Something's inside!", hero.getScreenPos().x, hero.getScreenPos().y);
				if (IsKeyPressed(KEY_E))
				{
					hasKey = true;
				}
			}
			if (talkedToWoman)
			{
				if (hero.getWorldPos().x > -195 && hero.getWorldPos().y < -75)
				{
					conversation("There is something under the bed!", hero.getScreenPos().x, hero.getScreenPos().y);
					if (IsKeyPressed(KEY_E))
					{
						hasMedkit = true;
						npcs[4]->setCurrentFrame(5);
					}
				}
			}
			props[33].Render(hero.getWorldPos());
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
			if (hero.getWorldPos().x < 70 || hero.getWorldPos().x > 1043 | hero.getWorldPos().y > 1408 || hero.getWorldPos().y < 0 ||
				hero.getWorldPos().x > 675 && hero.getWorldPos().y < 235)
			{
				hero.undoMovement();
			}
			if (metYellow || hasScroll)
			{

				npcs[2]->tick(GetFrameTime());
				npcs[2]->talk();
				if (CheckCollisionRecs(npcs[2]->GetCollisionRec(), hero.GetCollisionRec()))
				{
					hero.undoMovement();
					npcs[2]->undoMovement();
				}
				if (IsKeyPressed(KEY_E) && npcs[2]->getIsTalking())
				{
					npcs[2]->setInteractionCount();
					if (npcs[2]->getInteractionCount() == 1)
					{
						talkedToKid = true;
						npcs[3]->setWorldPos(850.f, 750.f);
						npcs[3]->setCurrentRow(2);
					}
				}
			}
			npcs[1]->tick(GetFrameTime());
			npcs[1]->talk();
			if (IsKeyPressed(KEY_E) && npcs[1]->getIsTalking())
			{
				npcs[1]->setInteractionCount();
			}
			if (npcs[1]->getInteractionCount() == 1)
			{
				metSara = true;
			}
			if (CheckCollisionRecs(npcs[1]->GetCollisionRec(), hero.GetCollisionRec()))
			{
				hero.undoMovement();
				npcs[1]->undoMovement();
			}
			props[4].Render(hero.getWorldPos());
			if (hero.getWorldPos().x < 95 && hero.getWorldPos().y > 715 &&
				hero.getWorldPos().y < 870)
			{
				conversation("Where does this road lead?", hero.getScreenPos().x, hero.getScreenPos().y);
				if (IsKeyPressed(KEY_E))
				{
					isOutsideCave = true;
					isOutsideTown = false;
					randomValue = GetRandomValue(1, 4);
					hero.setWorldPos(1260.f, 785.f);
				}
			}
			if (hero.getWorldPos().x < 912 && hero.getWorldPos().x > 870 && hero.getWorldPos().y < 250)
			{

				if (wasInSarasHouse)
				{
					if (IsKeyPressed(KEY_E))
					{
						isInSarasHouse = true;
						isOutsideTown = false;
						hero.setWorldPos(-150.f, 50.f);
					}
				}
				else
				{
					conversation("It's locked!", hero.getScreenPos().x, hero.getScreenPos().y);
				}
			}
			if (
				hero.getWorldPos().x < 560 && hero.getWorldPos().y > 1350)
			{
				DrawText("Press E to return to the town", 250, 250, 20, BLACK);
				if (IsKeyPressed(KEY_E))
				{
					isOutsideTown = false;
					isInTown = true;
					hero.setWorldPos(1700, 1150);
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
			if (hero.getWorldPos().x > 840 && hero.getWorldPos().x < 920 && hero.getWorldPos().y < 270 && outsideHouseCounter <= interactionWithHouseOutsideTown.size() - 1)
			{
				conversation(interactionWithHouseOutsideTown[outsideHouseCounter], npcs[1]->getScreenPos().x, npcs[1]->getScreenPos().y);
				if (IsKeyPressed(KEY_E))
				{
					outsideHouseCounter++;
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
			if (wasInCave)
			{
				npcs[1]->tick(GetFrameTime());
				npcs[1]->talk();
				if (IsKeyPressed(KEY_E) && npcs[1]->getIsTalking())
				{
					npcs[1]->setInteractionCount();
				}
				if (CheckCollisionRecs(npcs[1]->GetCollisionRec(), hero.GetCollisionRec()))
				{
					hero.undoMovement();
					npcs[1]->undoMovement();
				}
			}
			hero.tick(GetFrameTime());
			if (!talkedToKid && !wasInCave)
			{
				npcs[3]->tick(GetFrameTime());
				npcs[3]->setCurrentRow(3);
				npcs[3]->talk();
				if (IsKeyPressed(KEY_E) && npcs[3]->getIsTalking())
				{
					npcs[3]->setInteractionCount();
					if (npcs[3]->getInteractionCount() == 1)
					{
						metYellow = true;
					}
				}
				if (CheckCollisionRecs(npcs[3]->GetCollisionRec(), hero.GetCollisionRec()))
				{
					hero.undoMovement();
					npcs[3]->undoMovement();
				}
			}
			if (hasScroll)
			{
				if (IsKeyPressed(KEY_E) && npcs[3]->getIsTalking())
				{

					npcs[3]->setInteractionCount();
				}
			}
			props[7].Render(hero.getWorldPos());
			props[8].Render(hero.getWorldPos());
			if (CheckCollisionRecs(props[7].GetCollisionRec(hero.getWorldPos()),
								   hero.GetCollisionRec()) ||
				hero.getWorldPos().x > 1295 ||
				hero.getWorldPos().y < 400 || hero.getWorldPos().x < 90 ||
				hero.getWorldPos().y > 2010)
			{
				hero.undoMovement();
			}
			if (hero.getWorldPos().x < 690 && hero.getWorldPos().x > 640 &&
				hero.getWorldPos().y < 435)
			{
				if (!metYellow)
				{
					conversation("There is no way I will go in there!", hero.getScreenPos().x, hero.getScreenPos().y);
				}
				else
				{
					conversation("Let's see what is inside!", hero.getScreenPos().x, hero.getScreenPos().y);
					if (IsKeyPressed(KEY_E))
					{
						isOutsideCave = false;
						isInCave = true;
						wasInCave = true;
						npcs[3]->setWorldPos(750.f, 800.f);
						hero.setWorldPos(1055.f, 27.f);
					}
				}
			}
			if (hero.getWorldPos().x < 1180 && hero.getWorldPos().x > 1050 &&
				hero.getWorldPos().y < 435)
			{
				conversation("Hello Charles! Come here, I know the way out!", 680.f, 60.f);
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
			if (hero.getWorldPos().x > 930 && hero.getWorldPos().x < 1040 && hero.getWorldPos().y > 1915 && hero.getWorldPos().y < 1950)
			{
				if (hasScroll && talkedToKid && !isYellowDead)
				{
					conversation("Would it be the exit?", hero.getScreenPos().x, hero.getScreenPos().y);
					if (IsKeyPressed(KEY_E))
					{
						isOutsideCave = false;
						isGameOver = true;
						hero.setWorldPos(17.f, 1340.f);
					}
				}
				else if (isYellowDead)
				{
					conversation("We lived together, now we leave together!", hero.getScreenPos().x, hero.getScreenPos().y);
					if (IsKeyPressed(KEY_E))
					{
						isOutsideCave = false;
						isTheEnd = true;
					}
				}
				else
				{
					conversation("This is a really strange tree!", hero.getScreenPos().x, hero.getScreenPos().y);
				}
			}
		}
		else if (isInCave)
		{
			if (hasFlashlight)
			{
				DrawTextureEx(maps[13], mapPos, 0.0, 3.f, WHITE);
			}
			else
			{
				DrawTextureEx(maps[10], mapPos, 0.0, 3.f, WHITE);
			}
			if (!hasScroll)
			{

				props[18].Render(hero.getWorldPos());
				if (hero.getWorldPos().x > 60 && hero.getWorldPos().x < 145 && hero.getWorldPos().y < 2310 && hero.getWorldPos().y > 2200)
				{
					conversation(heroScroll[interactionWithScroll], hero.getScreenPos().x, hero.getScreenPos().y);
					if (IsKeyPressed(KEY_E))
					{
						interactionWithScroll++;
						if (interactionWithScroll == heroScroll.size() && !scrollDialogAdded)
						{
							hasScroll = true;
							npcs[2]->addDialog(kidDialogScroll);
							npcs[3]->addDialog(yellowDialogScroll);
							npcs[6]->addDialog(jadeDialogAfterScroll);
							scrollDialogAdded = true;
						}
					}
				}
			}
			if (hero.getWorldPos().y < 5 || hero.getWorldPos().y > 2400 ||
				hero.getWorldPos().x < 0 || hero.getWorldPos().x > 2065)
			{
				hero.undoMovement();
			}
			if (hero.getWorldPos().y < 25 && hero.getWorldPos().x > 1025 && hero.getWorldPos().x < 1100)
			{
				if (hasFlashlight)
				{
					conversation("Let's get out from here", hero.getScreenPos().x, hero.getScreenPos().y);
				}
				else
				{
					conversation("I can't see anything! I'd a need a flashlight or something!", hero.getScreenPos().x, hero.getScreenPos().y);
				}
				if (IsKeyPressed(KEY_E))
				{
					isInCave = false;
					isOutsideCave = true;
					hero.setWorldPos(650.f, 435.f);
					wasInCave = true;
					npcs[1]->setWorldPos(1200.f, 2100.f);
				}
			}
			if (hero.getWorldPos().y > 2360 && hero.getWorldPos().x > 830 && hero.getWorldPos().x < 899)
			{
				conversation("An exit!!!", hero.getScreenPos().x, hero.getScreenPos().y);
				if (IsKeyPressed(KEY_E))
				{
					isInCave = false;
					isEndGame = true;
					npcs[3]->setWorldPos(750.f, 1000.f);
					yellow.addDialog(yellowDialogBeforeFight);
					hero.setWorldPos(282.f, 12.f);
				}
			}
			npcs[6]->tick(GetFrameTime());
			npcs[6]->talk();
			if (CheckCollisionRecs(npcs[6]->GetCollisionRec(), hero.GetCollisionRec()))
			{
				hero.undoMovement();
			}
			if (IsKeyPressed(KEY_E) && npcs[6]->getIsTalking())
			{
				npcs[6]->setInteractionCount();
			}
			for (int i = 3; i < 22; i++)
			{

				if (CheckCollisionRecs(enemies[i]->GetCollisionRec(), hero.GetCollisionRec()) && enemies[i]->hasAwaken() && enemies[i]->getAlive())
				{
					hero.setAlive(true);
				}
				if (CheckCollisionRecs(enemies[i]->GetCollisionRec(), npcs[6]->GetCollisionRec()) && enemies[i]->hasAwaken() && enemies[i]->getAlive())
				{
					npcs[6]->setAlive(false);
				}
				enemies[i]->tick(GetFrameTime());
				if (npcs[6]->getInteractionCount() == 15 && npcs[6]->getAlive())
				{
					enemies[i]->setPlanned(true);
					enemies[i]->setTarget(&jade);
				}
				else{
					enemies[i]->setTarget(&hero);
				}
				if (hasDagger)
				{
					if (CheckCollisionRecs(enemies[i]->GetCollisionRec(), hero.getDaggerCollisionRec()) && enemies[i]->hasAwaken() && IsKeyPressed(KEY_SPACE))
					{
						enemies[i]->setAlive(false);
					}
				}
			}
			if (!hero.getAlive())
			{
				isInCave = false;
				isGameOver = true;
			}
			for (int i = 3; i < 22; i++)
			{
				for (int j = i + 1; j < 22; j++)
				{
					if (CheckCollisionRecs(enemies[i]->GetCollisionRec(), enemies[j]->GetCollisionRec()))
					{
						enemies[i]->resolveCollision(enemies[j]->getWorldPos());
						enemies[j]->resolveCollision(enemies[i]->getWorldPos());
					}
				}
			}
			for (int i = 10; i < 12; i++)
			{
				props[i].Render(hero.getWorldPos());
			}

			if (hero.getWorldPos().x > 1750 && hero.getWorldPos().x < 1820 && hero.getWorldPos().y < 540 && hero.getWorldPos().y > 480 && inCaveCounter < heroInCave.size())
			{
				conversation(heroInCave[inCaveCounter], hero.getScreenPos().x, hero.getScreenPos().y);
				if (IsKeyPressed(KEY_E) && inCaveCounter <= heroInCave.size() - 1)
				{
					inCaveCounter++;
					hasFallen = false;
				}
			}
			hero.tick(GetFrameTime());
		}
		else if (isGameOver)
		{

			if (randomValue == 5)
			{
				DrawTextureEx(maps[15], gameOverScreenPos, 0.0, 2.f, WHITE);
				DrawText("You may escape in another life.", screenWidth / 6, screenHeight / 2, 40, RED);
			}
			else if (randomValue == 6)
			{

				DrawTexturePro(maps[16], srcEnd, destEnd, {0, 0}, 0.0f, WHITE);
				DrawText("Oh you woke up! You are very lucky!", screenWidth / 6, screenHeight / 2, 40, RED);
			}
			else
			{
				props[19].Render(hero.getWorldPos());
				for (int i = 22; i < 32; i++)
				{
					enemies[i]->tick(GetFrameTime());
				}
				hero.tick(GetFrameTime());
				if (hero.getWorldPos().y < 500)
				{
					hero.undoMovement();
				}
				if (hero.getWorldPos().y < 550)
				{
					conversation("Come in. We were waiting for you!", hero.getScreenPos().x, hero.getScreenPos().y);
					if (IsKeyPressed(KEY_E))
					{
						isGameOver = false;
						isInSecretRoom = true;
						randomValue = GetRandomValue(1, 2);
						hero.setWorldPos(-316.f, -220.f);
					}
				}
				if (hero.getWorldPos().y > 1500 || hero.getWorldPos().x > 1500 || hero.getWorldPos().x < -1500)
				{
					renderEnemy = true;
				}
				if (renderEnemy)
				{
					enemies[1]->tick(GetFrameTime());
				}
			}
		}
		else if (isInSecretRoom)
		{
			DrawTextureEx(maps[17], interiorPos, 0.0, 1.5, WHITE);
			props[20].Render(hero.getWorldPos());
			props[28].Render(hero.getWorldPos());
			hero.tick(GetFrameTime());
			if (hero.getWorldPos().y < -352 || hero.getWorldPos().x > -90 || hero.getWorldPos().x < -491 || hero.getWorldPos().y > 71)
			{
				hero.undoMovement();
			}
			if (hero.getWorldPos().x > -322 && hero.getWorldPos().x < -260 && hero.getWorldPos().y > 51)
			{
				if (!doorUnlocked)
				{
					conversation("Who locked this door?", hero.getScreenPos().x, hero.getScreenPos().y);
				}
				if (IsKeyPressed(KEY_E))
				{
					isInSecretRoom = false;
					isInTown = true;
					doorUnlocked = true;
					hero.setWorldPos(962.f, 346.f);
				}
			}
			if (hero.getWorldPos().x > -360 && hero.getWorldPos().x < -290 && hero.getWorldPos().y < -310)
			{
				conversation("What happens if I get back in?", hero.getScreenPos().x, hero.getScreenPos().y);
				if (IsKeyPressed(KEY_E))
				{
					if (randomValue == 1)
					{
						isInSecretRoom = false;
						currentInterior = TEMPLE;
						isInside = true;
						randomValue = GetRandomValue(1, 2);
						hero.setWorldPos(-153.f, -165.f);
					}
					else
					{
						isInSecretRoom = false;
						isInSarasHouse = true;
						randomValue = GetRandomValue(1, 2);
						hero.setWorldPos(-150.f, -275.f);
					}
				}
			}
			if (hero.getWorldPos().x > -110 && hero.getWorldPos().y < -310)
			{
				conversation("Why would anyone need a clock here?", hero.getScreenPos().x, hero.getScreenPos().y);
			}
		}
		else if (isInSarasHouse)
		{
			DrawTextureEx(maps[18], interiorPos, 0.0, 2.f, WHITE);
			props[22].Render(hero.getWorldPos());
			hero.tick(GetFrameTime());
			if (hero.getWorldPos().x < -494 || hero.getWorldPos().x > 71 || hero.getWorldPos().y < -350 ||
				hero.getWorldPos().y > 98 || hero.getWorldPos().x > -489 && hero.getWorldPos().x < -312 && hero.getWorldPos().y < 70 && hero.getWorldPos().y > -106 ||
				hero.getWorldPos().x < -405 && hero.getWorldPos().y < -131 && hero.getWorldPos().y > -346 ||
				hero.getWorldPos().x > -30 && hero.getWorldPos().y > -109 && hero.getWorldPos().y < 31)
			{
				hero.undoMovement();
			}
			if (hero.getWorldPos().x < -110 && hero.getWorldPos().x > -187 && hero.getWorldPos().y > 70)
			{
				conversation("It can't be!", hero.getScreenPos().x, hero.getScreenPos().y);
				if (IsKeyPressed(KEY_E))
				{
					isInSarasHouse = false;
					isOutsideTown = true;
					wasInSarasHouse = true;
					hero.setWorldPos(900.f, 250.f);
				}
			}
			if (hero.getWorldPos().x > -40 && hero.getWorldPos().y > -50 && hero.getWorldPos().y < 15 && !hasRustyKey)
			{
				conversation("An old rusty key?", hero.getScreenPos().x, hero.getScreenPos().y);
				if (IsKeyPressed(KEY_E))
				{
					hasRustyKey = true;
				}
			}
			if (hero.getWorldPos().x > -313 && hero.getWorldPos().x < -300 && hero.getWorldPos().y > -50 && hero.getWorldPos().y < 10)
			{
				conversation("It must be Sara and her brother. But who is that third person? ", hero.getScreenPos().x, hero.getScreenPos().y);
			}
			if (hero.getWorldPos().x > -495 && hero.getWorldPos().x < -465 && hero.getWorldPos().y > -44 && hero.getWorldPos().y < 0)
			{
				conversation("Another tree? This one isn't familiar.", hero.getScreenPos().x, hero.getScreenPos().y);
			}
			if (hero.getWorldPos().x > -495 && hero.getWorldPos().x < -427 && hero.getWorldPos().y > 30 && hero.getWorldPos().y < 90 && !wasInSarasHouse)
			{
				if (!fellIntoCave)
				{
					conversation(interactionWithPotion[0], hero.getScreenPos().x, hero.getScreenPos().y);
				}
				else if (hero.getSpeed() != 3 && fellIntoCave)
				{
					conversation(interactionWithPotion[1], hero.getScreenPos().x, hero.getScreenPos().y);
					if(IsKeyPressed(KEY_E)){
						hero.setSpeed(3);
					}
				}
				else
				{
					conversation(interactionWithPotion[2], hero.getScreenPos().x, hero.getScreenPos().y);
				}
			}
			if (hero.getWorldPos().x > -165 && hero.getWorldPos().x < -125 && hero.getWorldPos().y < -300)
			{
				conversation("Ok. So it is one of those!", hero.getScreenPos().x, hero.getScreenPos().y);
				if (IsKeyPressed(KEY_E))
				{
					if (randomValue == 1)
					{
						isInSarasHouse = false;
						currentInterior = TEMPLE;
						isInside = true;
						hero.setWorldPos(-153.f, -165.f);
					}
					else
					{
						isInSarasHouse = false;
						isInSecretRoom = true;
						hero.setWorldPos(-316.f, -220.f);
					}
				}
			}
		}
		else if (isTheEnd)
		{
			DrawText("Thanks for playing my game!", 250, endingTitle, 30, RED);
			DrawText("You survived and escaped From.", 250, endingTitle + 100, 30, RED);
			DrawText("Graphics", 250, endingTitle + 150, 30, RED);
			DrawText("Music", 250, endingTitle + 200, 30, RED);

			endingTitle -= 0.5f;
		}
		else
		{
			DrawTextureEx(maps[14], interiorPos, 0.0, 3.f, WHITE);
			if (hero.getWorldPos().x < 28 || hero.getWorldPos().y < 10 ||
				hero.getWorldPos().x > 538 || hero.getWorldPos().y > 800 ||
				hero.getWorldPos().x < 180 && hero.getWorldPos().y < 530 ||
				hero.getWorldPos().x > 390 && hero.getWorldPos().y < 530)
			{
				hero.undoMovement();
			}
			if (isYellowDead)
			{
				if (hero.getWorldPos().x > 243 && hero.getWorldPos().x < 320 && hero.getWorldPos().y < 40)
				{
					conversation("Let's go back to the tree", hero.getScreenPos().x, hero.getScreenPos().y);
					if (IsKeyPressed(KEY_E))
					{
						isEndGame = false;
						isInCave = true;
						hero.setWorldPos(850.f, 2350.f);
					}
				}
				npcs[0]->tick(GetFrameTime());
				npcs[0]->talk();
				if (IsKeyPressed(KEY_E) && npcs[0]->getIsTalking())
				{
					npcs[0]->setInteractionCount();
				}
			}

			hero.tick(GetFrameTime());
			npcs[3]->tick(GetFrameTime());
			npcs[3]->setCurrentRow(0);
			npcs[3]->talk();

			if (IsKeyPressed(KEY_E) && npcs[3]->getIsTalking())
			{

				npcs[3]->setInteractionCount();
				endGameConvo++;
			}
			if (endGameConvo == yellowDialogBeforeFight.size() - 1)
			{
				talkedBeforeFight = true;
			}
			if (talkedBeforeFight)
			{
				if (Vector2Distance(hero.getScreenPos(), npcs[3]->getScreenPos()) > 150.f)
				{
					npcs[3]->setAttack();
				}
			}
			if (npcs[3]->getAttack())
			{
				if (CheckCollisionRecs(npcs[3]->GetCollisionRec(), hero.GetCollisionRec()))
				{
					hero.setAlive(true);
				}
			}
			if (hasDagger && npcs[3]->getAttack())
			{
				if (CheckCollisionRecs(npcs[3]->GetCollisionRec(), hero.getDaggerCollisionRec()) && IsKeyPressed(KEY_SPACE))
				{
					hitCounter++;
				}
				if (hitCounter == 10)
				{
					npcs[3]->setAlive(false);
					isYellowDead = true;
				}
			}
			if (!npcs[3]->getAlive())
			{
				if (afterFightCounter < yellowDialogAfterFight.size() - 1)
					conversation(yellowDialogAfterFight[afterFightCounter], npcs[3]->getScreenPos().x, npcs[3]->getScreenPos().y);
				if (IsKeyPressed(KEY_E))
				{
					afterFightCounter++;
				}
				if(Vector2Distance(npcs[3]->getScreenPos(), hero.getScreenPos()) > 150.f){
					npcs[3]->setCanAttack(false);
				}
			}
		}

		DrawText(TextFormat("Time %.2f", time), 50, 50, 20, RED);
		DrawText(TextFormat("Days Survived: %i", daysSurvived), 150, 50, 20, RED);
		DrawText(TextFormat("Random value: %d", randomValue), 190, 200, 20, RED);
		if (hasTalisman)
		{
			Texture2D tex = props[12].GetTexture();
			float scale = props[12].GetScale();
			Vector2 talismanScreenPos = {20.f, (float)GetScreenHeight() - tex.height * scale - 20.f};
			DrawTextureEx(tex, talismanScreenPos, 0.f, scale, WHITE);
		}
		if (hasFlashlight)
		{
			Texture2D tex = props[13].GetTexture();
			float scale = props[13].GetScale();
			Vector2 flashlightScreenPos = {50.f, (float)GetScreenHeight() - tex.height * scale - 5.f};
			DrawTextureEx(tex, flashlightScreenPos, 0.f, scale, WHITE);
		}
		if (hasKey)
		{
			Texture2D tex = props[14].GetTexture();
			float scale = props[14].GetScale();
			Vector2 keyScreenPos = {100.f, (float)GetScreenHeight() - tex.height * scale + 5.f};
			DrawTextureEx(tex, keyScreenPos, 0.f, scale, WHITE);
		}
		if (hasMedkit)
		{
			Texture2D tex = props[16].GetTexture();
			float scale = props[16].GetScale();
			Vector2 medkitScreenPos = {185.f, (float)GetScreenHeight() - tex.height * scale - 10.f};
			DrawTextureEx(tex, medkitScreenPos, 0.f, scale, WHITE);
		}
		if (hasScroll)
		{
			Texture2D tex = props[17].GetTexture();
			float scale = props[17].GetScale();
			Vector2 scrollScreenPos = {240.f, (float)GetScreenHeight() - tex.height * scale - 10.f};
			DrawTextureEx(tex, scrollScreenPos, 0.f, scale, WHITE);
		}
		if (hasDagger)
		{
			Texture2D tex = props[23].GetTexture();
			float scale = props[23].GetScale();
			Vector2 daggerScreenPos = {290.f, (float)GetScreenHeight() - tex.height * scale};
			DrawTextureEx(tex, daggerScreenPos, 0.f, scale, WHITE);
		}
		if (hasRustyKey)
		{
			Texture2D tex = props[24].GetTexture();
			float scale = props[24].GetScale();
			Vector2 rustyKeyPos = {330.f, (float)GetScreenHeight() - tex.height * scale};
			DrawTextureEx(tex, rustyKeyPos, 0.f, scale, WHITE);
		}
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
