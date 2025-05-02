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
    if (interactionCount != NPCDialog.size() - 1 && isTalking)
    {
        interactionCount++;
    }
}

void NPC::talk()
{   
    isTalking = true;
    if(Vector2Distance(getScreenPos(), hero->getScreenPos()) > 150.f){
        isTalking = false;
    }
}

void NPC::tick(float deltaTime)
{
    if (isHuman)
    {
        currentRow = 1;
        if (isTalking && interactionCount < NPCDialog.size())
        {
            std::string dialogText = NPCDialog[interactionCount];
            int fontSize = 15;
            int padding = 10;

            // Measure the width of the text
            int textWidth = MeasureText(dialogText.c_str(), fontSize);

            // Set minimum width and height for the bubble
            int minWidth = 100;
            int minHeight = 40;

            // Final width and height with padding
            int bubbleWidth = std::max(minWidth, textWidth + 2 * padding);
            int bubbleHeight = minHeight; 

            // Build the rectangle based on text size
            Rectangle conversation{
                getScreenPos().x - bubbleWidth / 2,
                getScreenPos().y - 40,
                static_cast<float>(bubbleWidth),
                static_cast<float>(bubbleHeight)};

            // Draw the bubble and the text
            if(Vector2Distance(getScreenPos(), hero->getScreenPos()) < 150.f){
            DrawRectangleRounded(conversation, 0.2f, 6, WHITE);
            DrawText(dialogText.c_str(), conversation.x + padding, conversation.y + padding, fontSize, BLACK);
            }
        }
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

    if (interactionCount > 0 && !isHuman && isDay)
    {
        texture = walk;
        velocity = Vector2Subtract(hero->getScreenPos(), getScreenPos());
        if (isTalking && interactionCount < NPCDialog.size())
        {
            std::string dialogText = NPCDialog[interactionCount];
            int fontSize = 15;
            int padding = 10;

            // Measure the width of the text
            int textWidth = MeasureText(dialogText.c_str(), fontSize);

            // Set minimum width and height for the bubble
            int minWidth = 100;
            int minHeight = 40;

            // Final width and height with padding
            int bubbleWidth = std::max(minWidth, textWidth + 2 * padding);
            int bubbleHeight = minHeight; 

            // Build the rectangle based on text size
            Rectangle conversation{
                getScreenPos().x - bubbleWidth / 2,
                getScreenPos().y - 40,
                static_cast<float>(bubbleWidth),
                static_cast<float>(bubbleHeight)};

            // Draw the bubble and the text
            if(Vector2Distance(getScreenPos(), hero->getScreenPos()) < 150.f){
            DrawRectangleRounded(conversation, 0.2f, 6, WHITE);
            DrawText(dialogText.c_str(), conversation.x + padding, conversation.y + padding, fontSize, BLACK);
            }
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
