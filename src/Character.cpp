#include "Character.h"
#include "raylib.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{

	width = (float)texture.width / totalColumns;
	height = (float)texture.height / totalRows;
	screenPos = {
		static_cast<float>(winWidth) / 2.0f - (0.5f * width),
		static_cast<float>(winHeight) / 2.0f - (0.5f * height)};
}

void Character::tick(float deltaTime)
{
	worldPosLastFrame = worldPos;

	Vector2 direction{};
	if (IsKeyDown(KEY_A))
	{
		direction.x -= 1.0;
		currentRow = 1;
	}
	if (IsKeyDown(KEY_D))
	{
		direction.x += 1.0;
		currentRow = 3;
	}
	if (IsKeyDown(KEY_W))
	{
		direction.y -= 1.0;
		currentRow = 0;
	}
	if (IsKeyDown(KEY_S))
	{
		direction.y += 1.0;
		currentRow = 2;
	}
	if (Vector2Length(direction) != 0.0)
	{
		// set worldPos = worldPos + direction

		worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
		frameTime += deltaTime;
		if (frameTime >= frameDuration)
		{
			currentFrame++;
			if (currentFrame >= totalColumns)
				currentFrame = 0;
			frameTime = 0.0f;
		}
	}

	// Define source rectangle to pick one frame
	Rectangle source{
		width * currentFrame, // X: shift by frame
		height * currentRow,  // Y: shift by row
		width,
		height};

	// Define destination rectangle
	Rectangle dest{
		screenPos.x,
		screenPos.y,
		width * scale,
		height * scale};
	// draw character
	DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.f, WHITE);
	DrawText(TextFormat("Width: %.2f Height: %.2f", worldPos.x, worldPos.y), 10, 10, 20, RED);
}

void Character::undoMovement()
{
	worldPos = worldPosLastFrame;
}

Rectangle Character::GetCollisionRec()
{
	return Rectangle{
		screenPos.x,
		screenPos.y ,
		width * scale,
		height * scale};
}