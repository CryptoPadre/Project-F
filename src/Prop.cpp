#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex, float scale, bool building) : worldPos(pos),
                                                                     texture(tex),
                                                                     scale(scale),
                                                                     isBuilding(building)
{
}

void Prop::Render(Vector2 heroPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, heroPos)};
    float totalHeight = texture.height * scale;
    float collisionHeight = totalHeight * 0.2f;
    float totalWidth = texture.width * scale;
    float collisionWidth = totalWidth * 0.6f;
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
    if(!isBuilding){
    DrawRectangleLines(screenPos.x + totalWidth - collisionWidth - 70,
                       screenPos.y + (totalHeight - collisionHeight) - 20, // Align to bottom
                       collisionWidth,
                       collisionHeight, RED);
    }
    else {
        DrawRectangleLines(screenPos.x,
            screenPos.y - 75,
            texture.width * scale,
            texture.height * scale, RED);
    }
}

Rectangle Prop::GetCollisionRec(Vector2 heroPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, heroPos)};
    float totalHeight = texture.height * scale;
    float collisionHeight = totalHeight * 0.2f; // Bottom 20%
    float totalWidth = texture.width * scale;
    float collisionWidth = totalWidth * 0.6f; // Bottom 20%
    if (!isBuilding)
    {
        return Rectangle{
            screenPos.x + totalWidth - collisionWidth - 70,
            screenPos.y + (totalHeight - collisionHeight) - 20, // Align to bottom
            collisionWidth,
            collisionHeight};
    }
    else
    {
        return Rectangle{
            screenPos.x,
            screenPos.y - 75,
            texture.width * scale,
            texture.height * scale};
    }
}
