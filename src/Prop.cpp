#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex, float scale, bool building, int heightA,int heightB, int widthA, int widthB) : worldPos(pos),
                                                                     texture(tex),
                                                                     scale(scale),
                                                                     isBuilding(building),
                                                                     adjustmentHeightA(heightA),
                                                                     adjustmentHeightB(heightB),
                                                                     adjustmentWidthA(widthA),
                                                                     adjustmentWidthB(widthB)

{
};

void Prop::Render(Vector2 heroPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, heroPos)};
    float totalWidth = texture.width * scale;
    float totalHeight = texture.height * scale;
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
    if (isBuilding)
    {
        DrawRectangleLines(
            screenPos.x + adjustmentWidthA, // modify width by adding adjustmentWidthA
            screenPos.y + totalHeight * 0.6f - adjustmentHeightA, // lower half
            totalWidth - adjustmentWidthB, // modify width by substracting adjustmentWidthB
            totalHeight * 0.5f / 2.f, RED);
    }
    else
    {
        float trunkWidth = totalWidth * 0.6f;
        float trunkHeight = totalHeight * 0.2f;
        DrawRectangleLines(
            screenPos.x + (totalWidth - trunkWidth) / 2.f + adjustmentWidthA, // right side
            screenPos.y + totalHeight - trunkHeight - adjustmentHeightA,
            trunkWidth + adjustmentWidthB, // left side
            trunkHeight + adjustmentHeightB,
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
            screenPos.x + adjustmentWidthA,
            screenPos.y + totalHeight * 0.6f - adjustmentHeightA, // lower half
            totalWidth - adjustmentWidthB,
            totalHeight * 0.5f / 2.f};
    }
    else
    {
        float trunkWidth = totalWidth * 0.6f;
        float trunkHeight = totalHeight * 0.2f;
        return Rectangle{
            screenPos.x + (totalWidth - trunkWidth) / 2.0f + adjustmentWidthA,
            screenPos.y + totalHeight - trunkHeight - adjustmentHeightA,
            trunkWidth + adjustmentWidthB,
            trunkHeight + adjustmentHeightB};
    }
}

void Prop::RenderOnScreen(Vector2 screenPos)
{
    float totalWidth = texture.width * scale;
    float totalHeight = texture.height * scale;
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}