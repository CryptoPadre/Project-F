#include "NPC.h"
#include <string>
#include "raylib.h"
#include "raymath.h"

NPC::NPC(Vector2 pos, Texture2D texture, Texture2D interact)
{
    worldPos = pos;
    texture = texture; 
    walk = texture; 
    width = (float)texture.width / totalColumns;
    height = (float)texture.height / totalRows;
    speed = 1.0f;
    interact = interact;
}

void NPC::setInteractionCount()
{
    if (interactionCount != NPCDialog.size() - 1)
    {
        interactionCount++;
    }
}

void NPC::talk()
{
    DrawText(NPCDialog[interactionCount].c_str(), worldPos.x, worldPos.y - 30, 30, RED);
    if (interactionCount == NPCDialog.size() - 1)
    {
        DrawText(NPCDialog[interactionCount].c_str(), worldPos.x, worldPos.y - 30, 30, RED);
    }
}

void NPC::tick(float deltaTime)
{
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

Vector2 NPC::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}