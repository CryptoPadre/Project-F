#include "raylib.h"
#include "BaseCharacter.h"
#include <string>
#include <vector> 

class NPC : public BaseCharacter{
    public:
    NPC(Vector2 pos, Texture2D texture, Texture2D interact);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    void addDialog(const std::string& dialog){ NPCDialog.push_back(dialog);};
    std::string talk();
    bool setIsHuman(){ return isHuman = true ? false : true;};
    int setInteractionCount();
    private:
    std::vector<std::string> NPCDialog;
    float radius{25.f};
    bool isHuman{};
    int interactionCount{0};
};