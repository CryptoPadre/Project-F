#include "Enemy.h"
#include "raymath.h"
#include "raylib.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture) : worldPos(pos),
                                                    texture(idle_texture)
                                                                            
{
    width = (float)texture.width / totalColumns;
    height = (float)texture.height / totalRows;
}

void Enemy::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
    // set worldPos = worldPos + direction

    frameTime += deltaTime;
    if (frameTime >= frameDuration)
    {
        currentFrame++;
        if (currentFrame >= totalColumns)
            currentFrame = 0;
        frameTime = 0.0f;
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
}

void Enemy::undoMovement()
{
	worldPos = worldPosLastFrame;
}

Rectangle Enemy::GetCollisionRec()
{
	return Rectangle{
		screenPos.x,
		screenPos.y,
		width * scale,
		height * scale};
}