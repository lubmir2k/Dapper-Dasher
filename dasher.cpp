#include "raylib.h"

constexpr int window_width{512};
constexpr int window_height{380};

struct AnimData
{
    Rectangle rect;
    Vector2 pos;
    Vector2 frameSize;
    int frame;
    int maxFrame;
    int framesWide;
    double updateTime;
    float runningTime;
};

bool isOnGround(AnimData scarfyData)
{
    return scarfyData.pos.y >= window_height - scarfyData.rect.height;
}

AnimData updateAnimData(AnimData data, float deltaTime)
{
    // Update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
         data.runningTime = 0.0;

        // Update the animation frame
        data.rect.x = data.frame % data.framesWide * data.frameSize.x;
        data.rect.y = data.frame / data.framesWide * data.frameSize.y;
        data.frame++;
        if (data.frame > data.maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    //SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(window_width, window_height, "Dapper Dasher");

    // Acceleration due to gravity (pixels per second)
    const int gravity{1'000};

    // Nebula x velocity (pixels/second)
    int nebVel{-200};

    Texture2D nebulaTex = LoadTexture("assets/12_nebula_spritesheet.png");

    const int sizeOfNebulae{2};
    AnimData nebData[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebData[i].frameSize.x = 100;
        nebData[i].frameSize.y = 100;
        nebData[i].framesWide = 8;
        nebData[i].maxFrame = 61;
        nebData[i].rect.width = nebData[i].frameSize.x;
        nebData[i].rect.height = nebData[i].frameSize.y;
        //nebData.rect.x = 0;
        //nebData.rect.y = 0;
        nebData[i].pos.x = window_width + 300;
        nebData[i].pos.y = window_height - nebData[i].rect.height;
        nebData[i].frame = 0;
        nebData[i].updateTime = 1.0 / 16.0;
        nebData[i].runningTime = 0.0;
    }

    nebData[1].pos.x = window_width + 600;
    nebData[1].pos.y = window_height / 4 - nebData[1].rect.height;
 
    // Scarfy variables
    bool isInAir{};
    float velocity{0};
    const int jumpVel{-600};
    
    Texture2D scarfyTex = LoadTexture("assets/testA_Twirl hair_0deg.png");
    AnimData scarfyData;
    scarfyData.frameSize.x = 138;
    scarfyData.frameSize.y = 197;
    scarfyData.framesWide= 59;
    scarfyData.maxFrame = 799;
    scarfyData.rect.width = scarfyData.frameSize.x;
    scarfyData.rect.height = scarfyData.frameSize.y;
    //scarfyData.rect.x = 0;
    //scarfyData.rect.y = 0;
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
        if (isOnGround(scarfyData))
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
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebData[i].pos.x += nebVel * deltaTime;
        }

        // Update Scarfy's position
        scarfyData.pos.y += velocity * deltaTime;

        // Update Scarfy's animation frame
        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, deltaTime);
        }

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebData[i] = updateAnimData(nebData[i], deltaTime);

            // Draw nebulae
            DrawTextureRec(nebulaTex, nebData[i].rect, nebData[i].pos, WHITE);
        }


        // Draw Scarfy
        DrawTextureRec(scarfyTex, scarfyData.rect, scarfyData.pos, WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfyTex);
    UnloadTexture(nebulaTex);
    CloseWindow();
}
