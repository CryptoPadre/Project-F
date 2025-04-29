#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter() {

};

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        getScreenPos().x + 50,
        getScreenPos().y + 50,
        width / scale,
        height / scale };
}

void BaseCharacter::tick(float deltaTime)
{   
    DrawRectangleLines(getScreenPos().x + 50,
    getScreenPos().y + 50,
    width / scale,
    height / scale, RED);

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
}