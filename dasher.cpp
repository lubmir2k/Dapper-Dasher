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

    // Nebula variables
    Texture2D nebulaTex = LoadTexture("assets/12_nebula_spritesheet.png");
    Rectangle nebRec{0, 0, nebulaTex.width / 8, nebulaTex.height / 8};
    Vector2 nebPos{window_width, window_height - nebRec.height};

    // Nebula animation variables
    int nebFrame{};
    const float nebUpdateTime{static_cast<float>(1.0 / 12.0)};
    float nebRunningTime{};

    // Nebula x velocity (pixels/second)
    int nebVel{-200};

    // Scarfy variables
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
        nebPos.x += nebVel * deltaTime;

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
        nebRunningTime += deltaTime;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if (nebFrame > 7)
            {
                nebFrame = 0;
            }
        }

        // Draw nebula
        DrawTextureRec(nebulaTex, nebRec, nebPos, WHITE);

        // Draw Scarfy
        DrawTextureRec(scarfyTex, scarfyData.rect, scarfyData.pos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfyTex);
    UnloadTexture(nebulaTex);
    CloseWindow();
}
