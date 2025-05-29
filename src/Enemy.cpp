#include "Enemy.h"
#include "raymath.h"


Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D attack, bool type)
{
    worldPos = pos;
    texture = idle_texture;
    walk = idle_texture;
    width = (float)texture.width / totalColumns;
    height = (float)texture.height / totalRows;
    speed = 1.0f;
    interact = attack;
    type = isCaveMonster;
}

void Enemy::tick(float deltaTime)
{
    if(isCaveMonster){
        texture = interact;
        if(Vector2Distance(getScreenPos(), target->getScreenPos()) < 50.f && !awakeningAnimDone){
            if (awakeningFrameTime <= awakeningFrameDuration){
            awakeningFrameTime --; 
            awakeningFrameTime = 0.f;
            if (awakeningFrame <= awakeningTotalFrames)
                {
                    awakeningFrame = awakeningTotalFrames - 6;
                    awakeningAnimDone = true;
                }
            }
        }
    }
    // get toTarget
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius)
    {
        velocity = {};
        texture = interact;
    } else {
        texture = walk;
    }
    if (velocity.x > velocity.y)
    {
        // Horizontal movement dominates
        if (velocity.x > 0)
            currentRow = 3; // Right
        else
            currentRow = 1; // Left
    }
    else
    {
        // Vertical movement dominates
        if (velocity.y > 0)
            currentRow = 2; // Down
        else
            currentRow = 0; // Up
    }

    // move the Enemy
    BaseCharacter::tick(deltaTime);
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}
