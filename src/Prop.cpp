#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) : 
    worldPos(pos),
    texture(tex)
{

}

void Prop::Render(Vector2 heroPos){
    Vector2 screenPos{Vector2Subtract(worldPos, heroPos)};
    DrawTextureEx(texture, screenPos, 0.f, scale,WHITE);
}

Rectangle Prop:: GetCollisionRec(Vector2 heroPos){
    Vector2 screenPos{Vector2Subtract(worldPos, heroPos)};
    return Rectangle{
        screenPos.x + 75,
        screenPos.y - 50,
        texture.width * scale  - 115,
        texture.height * scale -70
    };
}