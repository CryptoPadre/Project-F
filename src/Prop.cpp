#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex, float scale, bool building, int height, int widthA, int widthB) : worldPos(pos),
                                                                     texture(tex),
                                                                     scale(scale),
                                                                     isBuilding(building),
                                                                     adjustmentHeight(height),
                                                                     adjustmentWidthA(widthA),
                                                                     adjustmentWidthB(widthB),

{
}

void Prop::Render(Vector2 heroPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, heroPos)};
    float totalWidth = texture.width * scale;
    float totalHeight = texture.height * scale;
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
    if (isBuilding)
    {
        DrawRectangleLines(
            screenPos.x + 150, // modify width by adding
            screenPos.y + totalHeight * 0.4f - adjustmentHeight, // lower half
            totalWidth - 250, // modify width by substracting
            totalHeight * 0.5f, RED);
    }
    else
    {
        float trunkWidth = totalWidth * 0.6f;
        float trunkHeight = totalHeight * 0.2f;
        DrawRectangleLines(
            screenPos.x + (totalWidth - trunkWidth) / 2.0f,
            screenPos.y + totalHeight - trunkHeight,
            trunkWidth,
            trunkHeight,
            BLUE);
    }
}

Rectangle Prop::GetCollisionRec(Vector2 heroPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, heroPos)};
    float totalWidth = texture.width * scale;
    float totalHeight = texture.height * scale;
    if (isBuilding)
    {
        return Rectangle{
            screenPos.x,
            screenPos.y + totalHeight * 0.4f - adjustmentHeight, // lower half
            totalWidth,
            totalHeight * 0.5f};
    }
    else
    {
        float trunkWidth = totalWidth * 0.6f;
        float trunkHeight = totalHeight * 0.2f;
        return Rectangle{
            screenPos.x + (totalWidth - trunkWidth) / 2.0f,
            screenPos.y + totalHeight - trunkHeight,
            trunkWidth,
            trunkHeight};
    }
}
