#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
	Character(int winWidth, int winHeight);
	Vector2 getWorldPos() { return worldPos; }
	void tick(float deltaTime);
	void undoMovement();
	Rectangle GetCollisionRec();

private:
	Texture2D texture{LoadTexture("hero-walk.png")};
	Texture2D interact{LoadTexture("hero-interact.png")};
	Texture2D die{LoadTexture("hero-hurt.png")};
	Vector2 screenPos{};
	Vector2 worldPos{};
	Vector2 worldPosLastFrame{}; 
	// animation for character
	int totalColumns = 9;
	int totalRows = 4;
	int currentFrame = 0; // column (frame within the animation)
	int currentRow = 2;	  // row for direction: 0-back, 1-right, 2-front,3-left.
	float frameTime = 0.0f;
	float frameDuration = 0.1f; // slower = bigger number
	const float speed{3.f};
	float width{};
	float height{};
	float scale{2.0f};
};