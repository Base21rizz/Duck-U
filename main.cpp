#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include <string>
#include "Particle.h"
#include "Enemy.h"
int main()
{
    SetTargetFPS(60);
    int windowWidth{1280};
    int windowHeight{720};
    InitWindow(windowWidth, windowHeight, "Duck U");

    // Map
    Texture2D map = LoadTexture("Assets/map.jpg");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{1.5f};
    // Character
    Particle dust;
    Character sil{windowWidth, windowHeight, dust};

    // Enemy
    Enemy ducky{
        Vector2{},
        LoadTexture("Assets/Animation/Ducky/ducky-idle.png"),
        LoadTexture("Assets/Animation/Ducky/ducky-walk.png")};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(sil.getworldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        sil.tick(GetFrameTime());

        ducky.tick(GetFrameTime());
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}