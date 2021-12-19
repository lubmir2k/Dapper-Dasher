#include "raylib.h"

int main()
{
    const int winWidth{512};
    const int winHeight{380};

    InitWindow(winWidth, winHeight, "Dapper Dasher");
    
    SetTargetFPS(30);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
    CloseWindow();
}