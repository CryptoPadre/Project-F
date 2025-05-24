#include "raylib.h"

class Prop {

    public:
    Prop(Vector2 pos,
    Texture2D tex, float scale, bool building, int height, int widthA, int widthB);
    void Render(Vector2 heroPos);
    Rectangle GetCollisionRec(Vector2 heroPos);
    bool isBuilding{};

    private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{};
    int adjustmentHeight{};
    int adjustmentWidthA{};
    int adjustmentWidthB{};

};