#include "NPC.h"
#include <string>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "Conversation.h"

NPC::NPC(Vector2 pos, Texture2D idle_texture, Texture2D interact, Texture2D special, bool human, bool danger)
{
    worldPos = pos;
    texture = idle_texture;
    walk = idle_texture;
    this->interact = interact;
    die = special;
    width = (float)texture.width / totalColumns;
    height = (float)texture.height / totalRows;
    speed = 1.f;
    isHuman = human;
    canAttack = danger;
}

void NPC::setInteractionCount()
{
    if (interactionCount != NPCDialog.size() && isTalking)
    {
        interactionCount++;
    }
}

void NPC::talk()
{
    isTalking = true;
    if (Vector2Distance(getScreenPos(), hero->getScreenPos()) > 150.f)
    {
        isTalking = false;
    }
}

void NPC::tick(float deltaTime)
{
    if (isHuman && !canAttack)
    {
        if (hero->getWorldPos().x > getScreenPos().x)
        {
            currentRow = 3;
        }
        else
        {
            currentRow = 1;
        }
        if (isTalking && interactionCount < NPCDialog.size() - 1 && Vector2Distance(getScreenPos(), hero->getScreenPos()) < 150.f)
        {
            conversation(NPCDialog[interactionCount], getScreenPos().x, getScreenPos().y);
        }
    }
    if (canAttack)
    {
        currentRow = 0;
        if (isTalking && interactionCount < NPCDialog.size() && Vector2Distance(getScreenPos(), hero->getScreenPos()) < 150.f)
        {
            conversation(NPCDialog[interactionCount], getScreenPos().x, getScreenPos().y);
        }
        if (willAttack)
        {
            velocity = Vector2Subtract(hero->getScreenPos(), getScreenPos());
            if(Vector2Length(velocity) < radius){
            texture = die;
            };
            if (fabs(velocity.x) > fabs(velocity.y))
            {
                currentRow = (velocity.x > 0) ? 3 : 1; // Right or Left
            }
            else
            {
                currentRow = (velocity.y > 0) ? 2 : 0; // Down or Up
            }
        }
    }
    /* if (!isHuman)
   {
       if (!isDay)
       {
           texture = interact; // Set texture to dance
           danceFrameTime += deltaTime;

           if (danceFrameTime >= danceFrameDuration)
           {
               danceFrame++;
               danceFrameTime = 0.f;

               if (danceFrame >= 5)
               {
                   danceFrame = 0;
                   danceRows++;
               }

               if (danceRows >= 4)
               {
                   danceRows = 0;
               }

           // Match BaseCharacter expectations
           currentFrame = danceFrame;
           currentRow = danceRows;
       }
   } */

    if (interactionCount > 0 && !isHuman)
    {
        texture = walk;
        velocity = Vector2Subtract(hero->getScreenPos(), getScreenPos());
        if (isTalking && interactionCount < NPCDialog.size() && Vector2Distance(getScreenPos(), hero->getScreenPos()) < 150.f)
        {
            conversation(NPCDialog[interactionCount], getScreenPos().x, getScreenPos().y);
        }
        if (velocity.x > velocity.y)
        {
            // Horizontal movement dominates
            if (velocity.x > 0)
                currentRow = 3; // Right
            else
                currentRow = 1; // Left
        }
        else
        {
            // Vertical movement dominates
            if (velocity.y > 0)
                currentRow = 2; // Down
            else
                currentRow = 0; // Up
        }
    }
    // move the NPC
    BaseCharacter::tick(deltaTime);
}

Vector2 NPC::getScreenPos()
{
    return Vector2Subtract(worldPos, hero->getWorldPos());
}

void NPC::addDialog(const std::vector<std::string> &dialogs)
{
    for (const auto &dialog : dialogs)
        NPCDialog.push_back(dialog);
}