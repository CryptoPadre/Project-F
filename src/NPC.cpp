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
    if (interactionCount != NPCDialog.size())
    {
        interactionCount++;
    }
}

void NPC::talk()
{
    
    if (Vector2Distance(getScreenPos(), hero->getScreenPos()) > 150.f)
    {
        isTalking = false;
    }

    else
    {
       isTalking = true;
    }
}

void NPC::tick(float deltaTime)
{
    if (!getAlive())
    {

        // Freeze velocity to stop movement
        velocity = {};
        texture = interact;
        if (!deathAnimStarted)
        {
            currentFrame = 6;
            deathAnimStarted = true;
        }

        // Play death animation
        if (!deathAnimDone)
        {
            deathAnimTime += deltaTime;
            if (deathAnimTime >= deathAnimSpeed)
            {
                currentFrame--;
                deathAnimTime = 0.f;

                if (currentFrame <= 2)
                {
                    currentFrame = 2;
                    deathAnimDone = true;
                }
            }
        }
        float frameWidth = texture.width / 7.f;
        float frameHeight = texture.height / 4.f;
        Rectangle source{frameWidth * currentFrame, frameHeight * currentRow, frameWidth, frameHeight};
        Rectangle dest{getScreenPos().x, getScreenPos().y, frameWidth * scale, frameHeight * scale};
        DrawTexturePro(texture, source, dest, {0, 0}, 0.f, WHITE);
        return;
    }

    if (!isInTemple)
    {
        if (abs(hero->getWorldPos().x) > abs(getScreenPos().x))
        {
            currentRow = 3;
        }
        else
        {
            currentRow = 1;
        }
    }
    if (isTalking && interactionCount != NPCDialog.size() && Vector2Distance(getScreenPos(), hero->getScreenPos()) < 150.f)
    {
        conversation(NPCDialog[interactionCount], getScreenPos().x, getScreenPos().y);
    }

    if (canAttack)
    {
        if (isTalking && interactionCount != NPCDialog.size() && Vector2Distance(getScreenPos(), hero->getScreenPos()) < 150.f)
        {
            conversation(NPCDialog[interactionCount], getScreenPos().x, getScreenPos().y);
        }
        if (willAttack)
        {
            velocity = Vector2Subtract(hero->getScreenPos(), getScreenPos());
            if (fabs(velocity.x) > fabs(velocity.y))
            {
                currentRow = (velocity.x > 0) ? 3 : 1; // Right or Left
            }
            else
            {
                currentRow = (velocity.y > 0) ? 2 : 0; // Down or Up
            }
            if (Vector2Length(velocity) < radius)
            {
                velocity = {};
                texture = die;
                attackTimer += GetFrameTime();
                if (attackTimer >= attackFrameDuration)
                {
                    attackTimer = 0.0f;
                    attackFrame++;
                    if (attackFrame <= attackTotalFrames)
                    {
                        isAttacking = false;

                        texture = walk;
                    }
                }
                Rectangle source{
                    width * attackFrame,
                    currentRow * height,
                    width,
                    height};

                Rectangle dest{
                    getScreenPos().x,
                    getScreenPos().y,
                    width * scale,
                    height * scale};

                DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.f, WHITE);

                return;
            }
            else
            {
                texture = walk;
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

        // Determine animation row based on direction
        if (fabs(velocity.x) > fabs(velocity.y))
        {
            currentRow = (velocity.x > 0) ? 3 : 1; // Right or Left
        }
        else
        {
            currentRow = (velocity.y > 0) ? 2 : 0; // Down or Up
        }
    }
    if (isInHouse && isHuman)
    {

        texture = interact;
        float frameWidth = (float)texture.width / 6;
        float frameHeight = (float)texture.height;

        Rectangle source{frameWidth * currentFrame, 0, frameWidth, frameHeight};
        Rectangle dest{getScreenPos().x, getScreenPos().y, frameWidth * scale, frameHeight * scale};
        DrawTexturePro(texture, source, dest, Vector2{0, 0}, 0.f, WHITE);
    }
    else
    {
        // move the NPC
        BaseCharacter::tick(deltaTime);
    }
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

void NPC::advanceDialogue()
{
    if (!finishedTalking && isTalking)
    {
        currentDialogIndex++;
    }
}

void NPC::resetDialogue()
{
    currentDialogIndex = 0;
    finishedTalking = false;
    interactionCount = -1;
}