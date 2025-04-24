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
    if (velocity.x > velocity.y) {
        // Horizontal movement dominates
        if (velocity.x > 0) currentRow = 3; // Right
        else currentRow = 1;               // Left
    } else {
        // Vertical movement dominates
        if (velocity.y > 0) currentRow = 2; // Down
        else currentRow = 0;               // Up
    }
   
    // move the Enemy
    BaseCharacter::tick(deltaTime);
}

Vector2 Enemy::getScreenPos(){
    return Vector2Subtract(worldPos, target->getWorldPos());
}
