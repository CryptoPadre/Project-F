#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter{
    public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
	Rectangle GetCollisionRec();
    virtual void tick(float deltaTime);
	virtual Vector2 getScreenPos() = 0;
	bool getAlive() {return alive;}
	void setAlive(bool isAlive) {alive = isAlive;}
	void setWorldPos(float x, float y) { worldPos = {x, y}; }
	void setCurrentRow(int row) { currentRow = row; }
    protected:
    Texture2D texture{LoadTexture("hero-walk.png")};
	Texture2D walk{LoadTexture("hero-walk.png")};
	Texture2D interact{LoadTexture("hero-interact.png")};
	Texture2D die{LoadTexture("hero-hurt.png")};
	Vector2 worldPos{};
	Vector2 worldPosLastFrame{}; 
	// animation for character
	int totalColumns = 9;
	int totalRows = 4;
	int currentFrame = 0; // column (frame within the animation)
	int currentRow = 2;	  // row for direction: 0-back, 1-right, 2-front,3-left.
	float frameTime = 0.0f;
	float frameDuration = 0.1f; // slower = bigger number
	float speed{3.f};
	float width{};
	float height{};
	float scale{2.0f};
	Vector2 velocity{};
    private:
	bool alive{true};
};

#endif