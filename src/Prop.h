#include "raylib.h"

class Prop
{

public:
    Prop(Vector2 pos,
         Texture2D tex, float scale, bool building, int heightA, int heightB, int widthA, int widthB);
    void Render(Vector2 heroPos);
    Rectangle GetCollisionRec(Vector2 heroPos);
    bool isBuilding{};
    void RenderOnScreen(Vector2 screenPos);
    Texture2D GetTexture() const { return texture; }
    float GetScale() const { return scale; }
private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{};
    int adjustmentHeightA{};
    int adjustmentHeightB{};
    int adjustmentWidthA{};
    int adjustmentWidthB{};
};