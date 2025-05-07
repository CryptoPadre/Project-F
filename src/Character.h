#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
	Character(int winWidth, int winHeight);
	virtual void tick(float deltaTime) override;
	virtual Vector2 getScreenPos() override;
	void setWorldPos(float x, float y) { worldPos = {x, y}; }

private:
	int windowWidth{};
	int windowHeight{};
	// Texture2D talisman{LoadTexture("talisman.png")};
	// Rectangle talismanCollisionRec{};
	int deathFrame = 0;
	float deathFrameTime = 0.0f;
	float deathFrameDuration = 0.5f;
	int deathTotalFrames = 6;
	bool deathAnimDone = false;
};

#endif