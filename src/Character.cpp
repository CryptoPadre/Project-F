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
	if (!isAttacking)
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
	}
	else
	{
		velocity = {0.f, 0.f};
	}
	if (IsKeyPressed(KEY_SPACE) && !isAttacking)
	{
		isAttacking = true;
		attackTimer = 0.0f;
		attackFrame = 4;
		texture = interact;
	}
	if (isAttacking)
	{
		attackTimer += GetFrameTime();
		if (attackTimer >= attackFrameDuration)
		{
			attackTimer = 0.0f;
			attackFrame++;
			if (attackFrame <= attackTotalFrames)
			{
				isAttacking = false;

				texture = walk;
			}
		}
	}
	if (isAttacking)
	{
		if (hasDagger)
		{
			Texture2D currentDagger = dagger;
			Vector2 offset{};
			Vector2 origin{};

			switch (currentRow)
			{
			case 0: // UP
				currentDagger = daggerUp;
				offset = {80.f, 10.f};
				origin = {0.f, 0.f};
				break;
			case 1: // LEFT
				currentDagger = daggerLeft;
				offset = {-30.f, 108.f};
				origin = {0.f, dagger.height * 0.2f};
				break;
			case 2: // DOWN
				currentDagger = dagger;
				offset = {122.f, 142.f};
				origin = {dagger.width * 0.2f, dagger.height * 0.2f};
				break;
			case 3: // RIGHT
				currentDagger = daggerRight;
				offset = {157.f, 87.f};
				origin = {daggerRight.width * 0.2f, daggerRight.height * 0.2f};
				break;
			}

			Rectangle source{0.f, 0.f, static_cast<float>(currentDagger.width), static_cast<float>(currentDagger.height)};
			Rectangle destDagger{
				getScreenPos().x + offset.x,
				getScreenPos().y + offset.y,
				currentDagger.width * 0.2f,
				currentDagger.height * 0.2f};

			daggerCollisionRec = {
				destDagger.x - origin.x,
				destDagger.y - origin.y,
				destDagger.width,
				destDagger.height};

			DrawTexturePro(currentDagger, source, destDagger, origin, 0.f, WHITE);

			
			DrawRectangleLines(
				daggerCollisionRec.x,
				daggerCollisionRec.y,
				daggerCollisionRec.width,
				daggerCollisionRec.height,
				RED);
		}
		Rectangle source{
			width * attackFrame,
			currentRow * height,
			width,
			height};

		Rectangle dest{
			getScreenPos().x,
			getScreenPos().y,
			width * scale,
			height * scale};

		DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.f, WHITE);

		return;
	}
	else
	{
		BaseCharacter::tick(deltaTime); // This draws the walking animation
	}

	DrawText(TextFormat("Width: %.2f Height: %.2f", worldPos.x, worldPos.y), 10, 10, 20, RED);
}
