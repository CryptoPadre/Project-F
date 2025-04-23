#include "raylib.h"

class Enemy{
    public:
    Enemy(Vector2 pos, Texture2D idle_texture);
    Vector2 getWorldPos() { return worldPos; }
	void tick(float deltaTime);
	void undoMovement();
	Rectangle GetCollisionRec();
    private:
    Texture2D texture{LoadTexture("hero-walk.png")};
	Vector2 screenPos{};
	Vector2 worldPos{};
	Vector2 worldPosLastFrame{}; 
	// animation for character
	int totalColumns = 5;
	int totalRows = 3;
	int currentFrame = 0; // column (frame within the animation)
	int currentRow = 1;	  // row for direction: 0-back, 1-right, 2-front,3-left.
	float frameTime = 0.0f;
	float frameDuration = 0.1f; // slower = bigger number
	const float speed{3.f};
	float width{};
	float height{};
	float scale{2.0f};
};