#include "NPC.h"
#include <string>
#include "raylib.h"
#include "raymath.h"

NPC::NPC(Vector2 pos, Texture2D idle_texture, Texture2D interact)
{
    worldPos = pos;
    texture = idle_texture;
    walk = idle_texture;
    this->interact = interact;
    width = (float)texture.width / totalColumns;
    height = (float)texture.height / totalRows;
    speed = 1.f;
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
    // move the NPC
    BaseCharacter::tick(deltaTime);
}

Vector2 NPC::getScreenPos()
{
    return Vector2Subtract(worldPos, hero->getWorldPos());
}
