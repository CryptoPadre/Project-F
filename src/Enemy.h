#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter{
    public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D attack, Texture2D death, bool type);
	virtual void tick(float deltaTime) override;
    void setTarget(Character* character){target = character;}
    bool hasAwaken(){return isAwake;}
    virtual Vector2 getScreenPos() override;
    bool isCaveMonster{};
    bool isStanding{};
    private:
    Character* target;
    float radius{25.f};
    int awakeningFrame = 5;
	float awakeningFrameTime = 0.0f;
	float awakeningFrameDuration = 0.4f;
	bool awakeningAnimDone = false;
    bool isAwake{};
    int awakeningTrigger = 150;
    
};

#endif