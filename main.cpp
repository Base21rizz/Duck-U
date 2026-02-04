#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include <string>

int main()
{
    SetTargetFPS(60);
    int windowWidth{600};
    int windowHeight{400};
    InitWindow(windowWidth, windowHeight, "Duck U");

    // Map
    Texture2D map = LoadTexture("Assets/map.jpg");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{1.f};

    // Character
    Character sil{windowWidth, windowHeight};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(sil.getworldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        sil.tick(GetFrameTime());

        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}