#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex, float scale) : 
    worldPos(pos),
    texture(tex),
    scale(scale)
{

}

void Prop::Render(Vector2 heroPos){
    Vector2 screenPos{Vector2Subtract(worldPos, heroPos)};
    DrawTextureEx(texture, screenPos, 0.f, scale,WHITE);
    DrawRectangleLines( screenPos.x,
        screenPos.y - 80,
        texture.width * scale,
        texture.height * scale, RED);
}

Rectangle Prop:: GetCollisionRec(Vector2 heroPos){
    Vector2 screenPos{Vector2Subtract(worldPos, heroPos)};
    return Rectangle{
        screenPos.x,
        screenPos.y -80,
        texture.width * scale,
        texture.height * scale
    };

}