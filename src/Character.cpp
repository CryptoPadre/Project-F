#include "Character.h"
#include "raylib.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) : windowWidth(winWidth),
													windowHeight(winHeight)
{

	width = (float)texture.width / totalColumns;
	height = (float)texture.height / totalRows;
}

Vector2 Character::getScreenPos()
{
	return Vector2{static_cast<float>(windowWidth) / 2.0f - (0.5f * width),
				   static_cast<float>(windowHeight) / 2.0f - (0.5f * height)};
}

void Character::tick(float deltaTime)
{

	if (IsKeyDown(KEY_A))
	{
		velocity.x -= 1.0;
		currentRow = 1;
	}
	if (IsKeyDown(KEY_D))
	{
		velocity.x += 1.0;
		currentRow = 3;
	}
	if (IsKeyDown(KEY_W))
	{
		velocity.y -= 1.0;
		currentRow = 0;
	}
	if (IsKeyDown(KEY_S))
	{
		velocity.y += 1.0;
		currentRow = 2;
	}
	/* Vector2 origin{};
	Vector2 offset{};
	if(currentRow == 2){
		origin = {0.f,talisman.height*scale};
		offset = {35.f, 55.f};
		talismanCollisionRec = {
			getScreenPos().x + offset.x - talisman.width * scale,
			getScreenPos().y + offset.y,
			talisman.width * scale,
			talisman.height * scale
		};
	} else if (currentRow == 3){
		origin = {talisman.width * scale, talisman.height * scale};
		offset = {35.f, 55.f};
		talismanCollisionRec = {
			getScreenPos().x + offset.x - talisman.width * scale,
			getScreenPos().y + offset.y - talisman.height * scale,
			talisman.width * scale,
			talisman.height * scale
		};
	} else {
		origin = {talisman.width * scale, talisman.height * scale};
		offset = {15.f, 55.f};
	}

	// draw talisman
	Rectangle source{0.f, 0.f, static_cast<float>(talisman.width), static_cast<float>(talisman.height)};
	Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, talisman.width*scale, talisman.height*scale};
	DrawTexturePro(talisman, source,dest,origin, 0.f, WHITE);
	DrawRectangleLines(
		talismanCollisionRec.x,
		talismanCollisionRec.y,
		talismanCollisionRec.width,
		talismanCollisionRec.height,
		RED);
	*/
	BaseCharacter::tick(deltaTime);
	DrawText(TextFormat("Width: %.2f Height: %.2f", worldPos.x, worldPos.y), 10, 10, 20, RED);
}
