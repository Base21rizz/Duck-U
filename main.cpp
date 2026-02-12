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

    Enemy *enemies[]{
        &ducky};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&sil);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(sil.getworldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        if (!sil.getAlive()) // Character's Dead
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
        }
        else // Character's Alive
        {
            std::string silsHealth = "Health: ";
            silsHealth.append(std::to_string(sil.getHealth()), 0, 5);
            DrawText(silsHealth.c_str(), 55.f, 45.f, 40, BLUE);
        }

        sil.tick(GetFrameTime());

        ducky.tick(GetFrameTime());

        // Debug
        Rectangle weaponRec = sil.getWeaponCollisionRec();
        DrawRectangleLines(weaponRec.x, weaponRec.y, weaponRec.width, weaponRec.height, RED);

        for (auto enemy : enemies)
        {
            if (CheckCollisionRecs(enemy->getFixedCollisionRec(), sil.getWeaponCollisionRec()))
            {
                enemy->setAlive(false);
            }
        }
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}