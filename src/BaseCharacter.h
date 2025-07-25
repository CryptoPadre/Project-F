#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter{
    public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
	void resolveCollision(Vector2 otherPos);
	Rectangle GetCollisionRec();
    virtual void tick(float deltaTime);
	virtual Vector2 getScreenPos() = 0;
	bool getAlive() {return alive;}
	bool getDeatFrameAnim() { return deathAnimDone;}
	void setAlive(bool isAlive) {alive = isAlive;}
	void setWorldPos(float x, float y) { worldPos = {x, y}; }
	void setCurrentRow(int row) { currentRow = row; }
	void setCurrentFrame(int frame) {currentFrame = frame;};
	void setIsGettingUp(bool fellDown) {isGettingUp = fellDown;}
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
	int deathFrame = 0;
	float deathFrameTime = 0.0f;
	float deathFrameDuration = 0.5f;
	int deathTotalFrames = 6;
	bool deathAnimDone = false;
	bool isGettingUp{};
	int getUpFrame = 5;
};

#endif