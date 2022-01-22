#include "raylib.h"

int main()
{
    constexpr int window_width{512};
    constexpr int window_height{380};

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    InitWindow(window_width, window_height, "Dapper Dasher");

    // Acceleration due to gravity (pixels per second)
    const int gravity {1'000};

    // Nebula variables
    Texture2D nebulaTex = LoadTexture("assets/12_nebula_spritesheet.png");
    Rectangle nebRec{0, 0, nebulaTex.width / 8, nebulaTex.height / 8};
    Vector2 nebPos { window_width, window_height - nebRec.height};

    // Nebula x velocity (pixels/second)
    int nebVel { -600 };

    // Scarfy variables
    Texture2D scarfyTex = LoadTexture("assets/testA_Twirl hair_0deg.png");
    Rectangle scarfyRec;
    Vector2 frameSize {138, 197 };
    int framesWide { 59 };
    int maxFrame { 799 };
    
    scarfyRec.width = frameSize.x;
    scarfyRec.height = frameSize.y;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    
    scarfyPos.x = window_width / 2 - scarfyRec.width / 2;
    scarfyPos.y = window_height - scarfyRec.height;

    int frame{};
    
    // Amount of time before updating animation frame - one twelfth of a second
    const float updateTime{static_cast<float>(1.0 / 60.0)};
    float runningTime{};

    bool isInAir{};
    const int jumpVel{-600};

    int velocity{0};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        const float deltaTime{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        // Perform ground check
        if (scarfyPos.y >= window_height - scarfyRec.height)
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

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // Update nebula's position
        nebPos.x += nebVel * deltaTime;
        
        // Update Scarfy's position
        scarfyPos.y += velocity * deltaTime;

       if (!isInAir)
       {
           // Update running time
           runningTime += deltaTime;
           if (runningTime >= updateTime)
           {
               runningTime = 0.0;

               // Update the animation frame
               //scarfyRec.x = frame * scarfyRec.width;
               scarfyRec.x =(frame % framesWide) * frameSize.x;
               scarfyRec.y = (int)(frame / framesWide) * frameSize.y;
               frame++;
               if (frame > maxFrame)
               {
                   frame = 0;
               }
           }
       }
        // Draw nebula
        DrawTextureRec(nebulaTex, nebRec, nebPos, WHITE);

        // Draw Scarfy
        DrawTextureRec(scarfyTex, scarfyRec, scarfyPos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfyTex);
    UnloadTexture(nebulaTex);
    CloseWindow();
}