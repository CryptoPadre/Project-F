#include "raylib.h"
#include <string>
#include <vector> 
#include "Character.h"


class NPC : public BaseCharacter{
    public:
    NPC(Vector2 pos, Texture2D idle_texture, Texture2D interact);
    void addDialog(const std::string& dialog){ NPCDialog.push_back(dialog);};
    void talk();
    void setInteractionCount();
    void setTarget(Character* character){hero = character;}
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    private:
    std::vector<std::string> NPCDialog;
    float radius{25.f};
    int interactionCount{0};
    Character* hero;

};