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
	void setHasDagger(bool foundDagger) { hasDagger = foundDagger; }
	Rectangle getDaggerCollisionRec(){ return daggerCollisionRec;}

private:
	int windowWidth{};
	int windowHeight{};
	Texture2D dagger{LoadTexture("dagger.png")};
	Texture2D daggerRight{LoadTexture("dagger-right.png")};
	Texture2D daggerLeft{LoadTexture("dagger-left.png")};
	Texture2D daggerUp{LoadTexture("dagger-up.png")};
	Rectangle daggerCollisionRec{};
	bool hasDagger{};
	bool isAttacking{};
	float attackTimer = 0.0f;
	int attackFrame = 5;
	int attackTotalFrames = 6;
	float attackFrameDuration = 0.2f;
};

#endif