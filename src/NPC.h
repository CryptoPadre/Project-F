#include "raylib.h"
#include "BaseCharacter.h"
#include <string>
#include <vector> 
#include "Enemy.h"

class NPC: public BaseCharacter{
    public:
    NPC(Vector2 pos, Texture2D texture, Texture2D interact);
    void addDialog(const std::string& dialog){ NPCDialog.push_back(dialog);};
    void talk();
    void setInteractionCount();
    void setTarget(Character* character){target = character;}
    virtual Vector2 getScreenPos() override;
    virtual void tick(float deltaTime) override;
    private:
    std::vector<std::string> NPCDialog;
    float radius{25.f};
    int interactionCount{0};
    Character* target;

};