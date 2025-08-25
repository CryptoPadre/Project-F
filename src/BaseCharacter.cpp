#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() {

};

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

void BaseCharacter::resolveCollision(Vector2 otherPos)
{
    Vector2 direction = Vector2Subtract(worldPos, otherPos);

    // Prevent division by zero
    if (Vector2Length(direction) == 0)
    {
        direction = {(float)GetRandomValue(-10, 10), (float)GetRandomValue(-10, 10)};
    }

    direction = Vector2Normalize(direction);
    float pushBackAmount = 3.0f;

    worldPos = Vector2Add(worldPos, Vector2Scale(direction, pushBackAmount));
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        getScreenPos().x + 50,
        getScreenPos().y + 50,
        width / scale ,
        height / scale + 30};
}

void BaseCharacter::tick(float deltaTime)
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
    else if (isGettingUp)
    {
        velocity = {};
        texture = die;

        if (!deathAnimDone)
        {
            deathFrameTime += deltaTime;
            if (deathFrameTime >= deathFrameDuration)
            {
                getUpFrame--;
                deathFrameTime = 0.f;
                if (getUpFrame < 0)
                {
                    getUpFrame = 0;
                    deathAnimDone = true;
                    isGettingUp = false;
                }
            }
        }

        Rectangle source{
            width * getUpFrame,
            0,
            width,
            height};

        Rectangle dest{
            getScreenPos().x,
            getScreenPos().y,
            width * scale,
            height * scale};

        DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.f, WHITE);
        texture = walk;
        return;
    }
    else
    {

        worldPosLastFrame = worldPos;

        if (Vector2Length(velocity) != 0.0)
        {
            // set worldPos = worldPos + direction

            worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
            frameTime += deltaTime;
            if (frameTime >= frameDuration)
            {
                currentFrame++;
                if (currentFrame >= totalColumns)
                    currentFrame = 0;
                frameTime = 0.0f;
            }
        }

        velocity = {};
        // Define source rectangle to pick one frame
        Rectangle source{
            width * currentFrame, // X: shift by frame
            height * currentRow,  // Y: shift by row
            width,
            height};

        // Define destination rectangle
        Rectangle dest{
            getScreenPos().x,
            getScreenPos().y,
            width * scale,
            height * scale};
        // draw character
        DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.f, WHITE);
        deathAnimDone = false;
        getUpFrame = 5;
    }
    DrawRectangleLines(getScreenPos().x + 50,
                       getScreenPos().y + 50,
                       width / scale ,
                       height / scale + 30, RED);
}