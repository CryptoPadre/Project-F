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
	if (!getAlive())
	{
		texture = die;

		if (!deathAnimDone)
		{
			deathFrameTime += deltaTime;
			if (deathFrameTime >= deathFrameDuration)
			{
				deathFrame++;
				deathFrameTime = 0.f;
				if (deathFrame >= deathTotalFrames)
				{
					deathFrame = deathTotalFrames - 1;
					deathAnimDone = true;
				}
			}
		}

		Rectangle source{
			width * deathFrame,
			0,
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
	if (IsKeyPressed(KEY_E) && !isAttacking)
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
			attackFrame ++;

			if (attackFrame > attackTotalFrames)
			{
				isAttacking = false;

				texture = walk;
			}
		}
	}
	BaseCharacter::tick(deltaTime);
	if (hasDagger)
	{
		Vector2 origin{};
		Vector2 offset{};
		if (currentRow == 1)
		{
			origin = {0.f, dagger.height * 0.2f};
			offset = {35.f, 55.f};
			daggerCollisionRec = {
				getScreenPos().x + offset.x - dagger.width * 0.2f,
				getScreenPos().y + offset.y,
				dagger.width * 0.2f,
				dagger.height * 0.2f};
			Rectangle source{0.f, 0.f, static_cast<float>(dagger.width), static_cast<float>(dagger.height)};
			Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, dagger.width * 0.2f, dagger.height * 0.2f};
			DrawTexturePro(dagger, source, dest, origin, 0.f, WHITE);
		}
		else if (currentRow == 3)
		{
			origin = {daggerRigth.width * 0.2f, daggerRigth.height * 0.2f};
			offset = {105.f, 100.f};
			daggerCollisionRec = {
				getScreenPos().x + offset.x - daggerRigth.width * 0.2f,
				getScreenPos().y + offset.y - daggerRigth.height * 0.2f,
				daggerRigth.width * 0.2f,
				daggerRigth.height * 0.2f};
			Rectangle source{0.f, 0.f, static_cast<float>(daggerRigth.width), static_cast<float>(daggerRigth.height)};
			Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, daggerRigth.width * 0.2f, daggerRigth.height * 0.2f};
			DrawTexturePro(daggerRigth, source, dest, origin, 0.f, WHITE);
		}
		else
		{
			origin = {dagger.width * 0.2f, dagger.height * 0.2f};
			offset = {15.f, 55.f};
			Rectangle source{0.f, 0.f, static_cast<float>(dagger.width), static_cast<float>(dagger.height)};
			Rectangle dest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, dagger.width * 0.2f, dagger.height * 0.2f};
			DrawTexturePro(dagger, source, dest, origin, 0.f, WHITE);
		}

		// draw dagger
		DrawRectangleLines(
			daggerCollisionRec.x,
			daggerCollisionRec.y,
			daggerCollisionRec.width,
			daggerCollisionRec.height,
			RED);
	}

	DrawText(TextFormat("Width: %.2f Height: %.2f", worldPos.x, worldPos.y), 10, 10, 20, RED);
}
