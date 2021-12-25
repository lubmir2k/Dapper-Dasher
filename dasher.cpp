#include "raylib.h"

int main()
{
    const int winWidth{512};
    const int winHeight{380};

    InitWindow(winWidth, winHeight, "Dapper Dasher");

    // Acceleration due to gravity (pixels/frame) per frame
    const int gravity{1};

    const int width{50};
    const int height{80};

    int pos_y {winHeight - height};
    int velocity{0};
    
    SetTargetFPS(30);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if(IsKeyPressed(KEY_SPACE))
        {
            velocity -= 10;
        }

        // Apply gravity
        velocity += gravity;
        
        // Update position
        pos_y += velocity;
        DrawRectangle(winWidth/2, pos_y, width, height, BLUE);
        EndDrawing();
    }
    CloseWindow();
}