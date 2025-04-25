#include "raylib.h"

class Prop {

    public:
    Prop(Vector2 pos,
    Texture2D tex, float scale );
    void Render(Vector2 heroPos);
    Rectangle GetCollisionRec(Vector2 heroPos);

    private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{};

};