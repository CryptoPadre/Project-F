#include "NPC.h"
#include <string>

NPC::NPC(Vector2 pos, Texture2D texture, Texture2D interact)
{
    worldPos = pos;
    texture = texture;
    interact = interact;
    width = (float)texture.width / totalColumns;
    height = (float)texture.height / totalRows;
    speed = 3.f;
}

int NPC::setInteractionCount()
{
    while (interactionCount != NPCDialog.size() - 1)
    {
        interactionCount++;
    }
}

std::string NPC::talk()
{
    DrawText(NPCDialog[interactionCount].c_str(), worldPos.x, worldPos.y - 30, 30, RED);
    if (interactionCount == NPCDialog.size() - 1)
    {
        DrawText(NPCDialog[interactionCount].c_str(), worldPos.x, worldPos.y - 30, 30, RED);
    }
}
