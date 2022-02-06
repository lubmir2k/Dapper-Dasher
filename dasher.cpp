#include "raylib.h"

struct AnimData
{
    Rectangle rect;
    Vector2 pos;
    Vector2 frameSize;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    constexpr int window_width{512};
    constexpr int window_height{380};

    //SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(window_width, window_height, "Dapper Dasher");

    // Acceleration due to gravity (pixels per second)
    const int gravity{1'000};

    // Nebula x velocity (pixels/second)
    int nebVel{-200};
    
    Texture2D nebulaTex = LoadTexture("assets/12_nebula_spritesheet.png");
    Vector2 nebFrameSize{100, 100};
    int nebFramesWide{8}; // TODO add to struct
    int nebMaxFrame{61}; // TODO add to struct
    AnimData nebData;
    nebData.rect.width = nebFrameSize.x;
    nebData.rect.height = nebFrameSize.y;
    nebData.rect.x = 0;
    nebData.rect.y = 0;
    nebData.pos.x = window_width  + 300;
    nebData.pos.y = window_height - nebData.rect.height;
    nebData.frame = 0;
    nebData.updateTime = 1.0/16.0;
    nebData.runningTime = 0.0;
    

    // Scarfy variables
    bool isInAir{};
    int velocity{0};
    const int jumpVel{-600};
    
    Texture2D scarfyTex = LoadTexture("assets/testA_Twirl hair_0deg.png");
    Vector2 frameSize{138, 197};
    int framesWide{59}; // TODO add to struct
    int maxFrame{799}; // TODO add to struct
    AnimData scarfyData;
    scarfyData.rect.width = frameSize.x;
    scarfyData.rect.height = frameSize.y;
    scarfyData.rect.x = 0;
    scarfyData.rect.y = 0;
    scarfyData.pos.x = window_width / 2 - scarfyData.rect.width / 2;
    scarfyData.pos.y = window_height - scarfyData.rect.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/60.0;
    scarfyData.runningTime = 0.0;

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        const float deltaTime{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        // Perform ground check
        if (scarfyData.pos.y >= window_height - scarfyData.rect.height)
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
        nebData.pos.x += nebVel * deltaTime;

        // Update Scarfy's position
        scarfyData.pos.y += velocity * deltaTime;

        // Update Scarfy's animation frame
        if (!isInAir)
        {
            // Update running time
            scarfyData.runningTime += deltaTime;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;

                // Update the animation frame
                //scarfyRec.x = frame * scarfyRec.width;
                scarfyData.rect.x = (scarfyData.frame % framesWide) * frameSize.x;
                scarfyData.rect.y = (int)(scarfyData.frame / framesWide) * frameSize.y;
                scarfyData.frame++;
                if (scarfyData.frame > maxFrame)
                {
                    scarfyData.frame = 0;
                }
            }
        }
        // Update nebula animation frame
        nebData.runningTime += deltaTime;
        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0.0;
            
            nebData.rect.x = (nebData.frame % nebFramesWide) * nebFrameSize.x;
            nebData.rect.y = (int)(nebData.frame / nebFramesWide) * nebFrameSize.y;
            nebData.frame++;
            if (nebData.frame > nebMaxFrame)
            {
                nebData.frame = 0;
            }
        }

        // Draw nebula
        DrawTextureRec(nebulaTex, nebData.rect, nebData.pos, WHITE);

        // Draw Scarfy
        DrawTextureRec(scarfyTex, scarfyData.rect, scarfyData.pos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfyTex);
    UnloadTexture(nebulaTex);
    CloseWindow();
}
