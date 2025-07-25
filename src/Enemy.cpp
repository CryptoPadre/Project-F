#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D attack, Texture2D death, bool type)
{
    worldPos = pos;
    texture = idle_texture;
    walk = idle_texture;
    width = (float)texture.width / totalColumns;
    height = (float)texture.height / totalRows;
    speed = 2.0f;
    interact = attack;
    die = death;
    isCaveMonster = type;
}

void Enemy::tick(float deltaTime)
{

    if (isStanding && isCaveMonster)
    {
        texture = walk;
        currentFrame = 0;
        if (currentRow != 1){
            currentRow = 3;
        }
        velocity = {};

        Rectangle source{
            width * currentFrame,
            height * currentRow,
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
        if (isCaveMonster && !isAwake)
        {
            texture = interact;

            if (Vector2Distance(getScreenPos(), target->getScreenPos()) < awakeningTrigger && !awakeningAnimDone)
            {
                awakeningTrigger = 1500;
                awakeningFrameTime += deltaTime;
                if (awakeningFrameTime >= awakeningFrameDuration)
                {
                    awakeningFrame--;
                    awakeningFrameTime = 0.f;
                    if (awakeningFrame < 0)
                    {
                        awakeningAnimDone = true;
                        awakeningFrame = 0;
                        isAwake = true;
                    }
                }
            }

            Rectangle source{width * awakeningFrame, 0, width, height};
            Rectangle dest{getScreenPos().x, getScreenPos().y, width * scale, height * scale};
            DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.f, WHITE);
            return;
        }

        // Set movement and animation direction
        velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

        // Choose texture and direction row
        if (isCaveMonster && isAwake)
        {
            texture = walk;
        }
        else if (!isCaveMonster && Vector2Length(velocity) < radius)
        {
            velocity = {};
            texture = interact;
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
            texture = walk;
        }

        // Determine animation row based on direction
        if (fabs(velocity.x) > fabs(velocity.y))
        {
            currentRow = (velocity.x > 0) ? 3 : 1; // Right or Left
        }
        else
        {
            currentRow = (velocity.y > 0) ? 2 : 0; // Down or Up
        }
    }
    // Move the enemy
    BaseCharacter::tick(deltaTime);
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}
