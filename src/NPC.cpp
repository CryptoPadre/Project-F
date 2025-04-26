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

std::string NPC::talk(){
    for(int i = 0; i < NPCDialog.size(); i++){
        DrawText(NPCDialog[i].c_str(), worldPos.x, worldPos.y - 30, 30, RED );
    }
}

