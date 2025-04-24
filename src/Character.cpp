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
	BaseCharacter::tick(deltaTime);

	DrawText(TextFormat("Width: %.2f Height: %.2f", worldPos.x, worldPos.y), 10, 10, 20, RED);
}
