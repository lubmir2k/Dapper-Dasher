#include "raylib.h"

int main()
{
    const int winWidth{512};
    const int winHeight{380};

    InitWindow(winWidth, winHeight, "Dapper Dasher");

    // Acceleration due to gravity (pixels per second)
    const int gravity{1'000};

    Texture2D scarfy = LoadTexture("assets/testA_Twirl hair_0deg.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width / 59;
    scarfyRec.height = scarfy.height / 21;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = winWidth / 2 - scarfyRec.width / 2;
    scarfyPos.y = winHeight / 2 - scarfyRec.height;

    bool isInAir{};
    const int jumpVel{-600};
    
    int velocity{0};
    
    SetTargetFPS(30);

    while(!WindowShouldClose())
    {
        const float deltaTime{GetFrameTime()};
        
        BeginDrawing();
        ClearBackground(WHITE);

        // Perform ground check
        if(scarfyPos.y >= winHeight - scarfyRec.height)
        {
            // Rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // Rectangle is in the air - apply gravity
            velocity += gravity * deltaTime;
            isInAir = true;
        }

        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

       
        
        // Update position
        scarfyPos.y += velocity * deltaTime;
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}