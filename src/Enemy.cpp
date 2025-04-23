#include "Enemy.h"
#include "raymath.h"
#include "Character.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture)                                                                            
{   
    worldPos = pos;
    texture= idle_texture;
    width = (float)texture.width / totalColumns;
    height = (float)texture.height / totalRows;
    speed = 1.0f;
}

void Enemy::tick(float deltaTime)
{   
    // get toTarget
    Vector2 toTarget = Vector2Subtract(target->getScreenPos(), screenPos);
    // normalize toTarget
    toTarget = Vector2Normalize(toTarget);
    // multiple toTarget by speed
    toTarget = Vector2Scale(toTarget, speed);
    // move the Enemy
    worldPos = Vector2Add(worldPos, toTarget);
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    if(worldPos.x > target->getWorldPos().x){
        currentRow = 1;
    }
   
    BaseCharacter::tick(deltaTime);
}

