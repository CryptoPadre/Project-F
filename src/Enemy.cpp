#include "Enemy.h"
#include "raymath.h"
#include "Character.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture)
{
    worldPos = pos;
    texture = idle_texture;
    width = (float)texture.width / totalColumns;
    height = (float)texture.height / totalRows;
    speed = 1.0f;
}

void Enemy::tick(float deltaTime)
{
    // get toTarget
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    // move the Enemy
    BaseCharacter::tick(deltaTime);
}

Vector2 Enemy::getScreenPos(){
    return Vector2Subtract(worldPos, target->getWorldPos());
}
