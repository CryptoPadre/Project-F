#include <string>
#include "raylib.h"

inline void conversation(std::string text, float width, float height){
    // Measure the width of the text
			int padding = 10;
			int fontSize = 15;
            int textWidth = MeasureText(text.c_str(), fontSize);
			// Set minimum width and height for the bubble
            int minWidth = 100;
            int minHeight = 40;

            // Final width and height with padding
            int bubbleWidth = std::max(minWidth, textWidth + 2 * padding);
            int bubbleHeight = minHeight; 
			// Build the rectangle based on text size
            Rectangle conversation{
               width - bubbleWidth / 2,
                height - 40,
                static_cast<float>(bubbleWidth),
                static_cast<float>(bubbleHeight)};
			DrawRectangleRounded(conversation, 0.2f, 6, WHITE);
            DrawText(text.c_str(), conversation.x + padding, conversation.y + padding, 15, BLACK);
};
