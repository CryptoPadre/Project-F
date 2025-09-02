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
	void incrementScreenPosWidth(){if (screenPosWidth < 6.f && IsKeyDown(KEY_A)){ screenPosWidth += 0.05;};}
	void descreaseScreenPosWidth(){if (screenPosWidth > -6.f && IsKeyDown(KEY_D)){ screenPosWidth -= 0.05;};}
	void resetScreenPosWidth();
	void setScreenPosWidth(){ screenPosWidth = 0.5;}
	void incrementScreenPosHeight(){if(screenPosHeight < 2.5 && IsKeyDown(KEY_W)){ screenPosHeight += 0.05;};}
	void descreaseScreenPosHeight(){if(screenPosHeight > -2.5 && IsKeyDown(KEY_S)){ screenPosHeight -= 0.05;};}
	void resetScreenPosHeight();
	void setScreenPosHeight(){ screenPosHeight = 0.5;}
	float getScreenPosWidth(){return screenPosWidth;}
	float getScreePosHeight(){return screenPosHeight;}


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
	float screenPosWidth = 0.5;
	float screenPosHeight = 0.5;

};

#endif