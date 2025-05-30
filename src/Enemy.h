#ifndef ENEMY_H
#define ENEMY_H
#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter{
    public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D attack, bool type);
	virtual void tick(float deltaTime) override;
    void setTarget(Character* character){target = character;}
    virtual Vector2 getScreenPos() override;
    bool isCaveMonster{};
    private:
    Character* target;
    float radius{25.f};
    int awakeningFrame = 5;
	float awakeningFrameTime = 0.0f;
	float awakeningFrameDuration = 0.8f;
	bool awakeningAnimDone = false;
    bool isAwake{};
    int awakeningTrigger = 150;
    
};

#endif