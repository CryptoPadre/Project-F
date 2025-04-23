#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(){

};

void BaseCharacter::undoMovement()
{
	worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
	return Rectangle{
		screenPos.x,
		screenPos.y ,
		width * scale,
		height * scale};
}

void BaseCharacter::tick(float deltaTime)
{   
	worldPosLastFrame = worldPos;

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