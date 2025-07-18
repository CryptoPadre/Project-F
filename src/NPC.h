#include "raylib.h"
#include <string>
#include <vector>
#include "Character.h"

class NPC : public BaseCharacter
{
public:
    NPC(Vector2 pos, Texture2D idle_texture, Texture2D interact, Texture2D special, bool human, bool danger);
    // void addDialog(const std::string& dialog){ NPCDialog.push_back(dialog);};
    void addDialog(const std::vector<std::string> &dialogs);
    void talk();
    void setInteractionCount();
    void clearInteractionCount() { interactionCount = 0; }
    void setTarget(Character *character) { hero = character; }
    void setAttack() { willAttack = true; }
    bool getAttack(){return willAttack;}
    void setCurrentFrame(int frame) { currentFrame = frame; }
    void advanceDialogue();
    void resetDialogue();
    const std::vector<std::string> &getDialogues() const { return NPCDialog; }
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    bool isDay{};
    int getInteractionCount() { return interactionCount; }
    bool isInHouse{};

private:
    int currentDialogIndex = 0;
    bool finishedTalking = false;
    bool isHuman{};
    bool canAttack{};
    bool isTalking{};
    std::vector<std::string> NPCDialog;
    float radius{50.f};
    int interactionCount{-1};
    Character *hero;
    int danceFrame = 0;
    float danceFrameTime = 0.0f;
    float danceFrameDuration = 0.3f;
    int danceTotalFrames = 0;
    int danceRows = 0;
    int yellowStartFrame = 0;
    float yellowInteractFrameTime = 0.0f;
    float yellowInteractFrameDuration = 0.5f;
    int yellowInteractColumns = 7;
    int yellowInteractRows = 4;
    int yellowAttackColumns = 6;
    int yellowAttackRows = 4;
    bool willAttack{};
    float deathAnimTime = 0.f;
    float deathAnimSpeed = 1.f;
    bool deathAnimDone{};
    bool deathAnimStarted{};
};