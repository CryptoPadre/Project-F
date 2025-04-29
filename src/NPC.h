#include "raylib.h"
#include <string>
#include <vector> 
#include "Character.h"


class NPC : public BaseCharacter{
    public:
    NPC(Vector2 pos, Texture2D idle_texture, Texture2D interact, bool human);
    void addDialog(const std::string& dialog){ NPCDialog.push_back(dialog);};
    void talk();
    void setInteractionCount();
    void setTarget(Character* character){hero = character;}
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    bool isDay{};
    private:
    bool isHuman{};
    std::vector<std::string> NPCDialog;
    float radius{25.f};
    int interactionCount{0};
    Character* hero;
    int danceFrame = 0;
	float danceFrameTime = 0.0f;
	float danceFrameDuration = 0.3f;
	int danceTotalFrames = 0;
    int danceRows =0;

};