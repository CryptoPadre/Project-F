#include "NPC.h"
#include <string>
#include "raylib.h"
#include "raymath.h"

NPC::NPC(Vector2 pos, Texture2D idle_texture, Texture2D interact, bool human)
{
    worldPos = pos;
    texture = idle_texture;
    walk = idle_texture;
    this->interact = interact;
    width = (float)texture.width / totalColumns;
    height = (float)texture.height / totalRows;
    speed = 1.f;
    isHuman = human;
}

void NPC::setInteractionCount()
{
    if (interactionCount != NPCDialog.size() - 1)
    {
        interactionCount++;
    }
}

void NPC::talk()
{
    DrawText(NPCDialog[interactionCount].c_str(), worldPos.x, worldPos.y - 30, 30, RED);
    if (interactionCount == NPCDialog.size() - 1)
    {
        DrawText(NPCDialog[interactionCount].c_str(), worldPos.x, worldPos.y - 30, 30, RED);
    }
}

void NPC::tick(float deltaTime)
{

    if (interactionCount == 0 && isHuman)
    {
        currentRow = 1;
    }
    if (!isHuman)
    { 
        if (!isDay)
        {
            texture = interact; // Set texture to dance
            danceFrameTime += deltaTime;

            if (danceFrameTime >= danceFrameDuration)
            {
                danceFrame++;
                danceFrameTime = 0.f;

                if (danceFrame >= 5) // 5 columns
                {
                    danceFrame = 0;
                    danceRows++;
                }

                if (danceRows >= 4) // 4 rows
                {
                    danceRows = 0;
                }
            }
            // Match BaseCharacter expectations
            currentFrame = danceFrame;
            currentRow = danceRows;
        }
    }

    if (interactionCount == 0 && !isHuman && isDay)
    {   
        texture = walk;
        velocity = Vector2Subtract(hero->getScreenPos(), getScreenPos());
        if (Vector2Length(velocity) < radius)
        {
            velocity = {};
            // Conversation bubble
            /* Rectangle conversation{
                getScreenPos().x,
                getScreenPos().y - 50,
                100,
                100
            };
            DrawRectangleRounded(conversation, 0.2f, 6, LIGHTGRAY);
            DrawRectangleRoundedLines(conversation, 0.2f, 6, DARKGRAY); 
            */
            DrawText("Anghkooey", 40, 40, 40, RED);
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
