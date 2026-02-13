#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include <string>
#include "Particle.h"
#include "Enemy.h"
#include <vector>

static Vector2 GetRandomSpawnPos()
{
    float x = (float)GetRandomValue(0, 5000);
    float y = (float)GetRandomValue(0, 3000);
    return {x, y};
}

int main()
{
    SetTargetFPS(60);
    int windowWidth{1280};
    int windowHeight{720};

    // Init
    InitWindow(windowWidth, windowHeight, "Duck U");
    InitAudioDevice();

    // Font
    Font customFont = LoadFontEx("Assets/DungeonFont.ttf", 64, 0, 0);

    // Sound
    Sound deathSound = LoadSound("Assets/sound/lose.wav");

    // Character's Health Bar
    Texture2D healthBar = LoadTexture("Assets/04.png");
    float HealthRow = 14;
    float HealthCol = 7;
    float HealthWidth = healthBar.width / HealthCol;
    float HealthHeight = healthBar.height / HealthRow;
    float curCol{1};
    float row{0};

    // Debug
    bool deathSoundPlayed = false;

    // Map
    Texture2D map = LoadTexture("Assets/map.jpg");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{1.5f};

    // Character
    Particle dust;
    Character sil{windowWidth, windowHeight, dust};

    std::vector<Enemy> enemies;
    const int MAX_ENEMIES = 1;
    Texture2D enemIdle = LoadTexture("Assets/Animation/Ducky/ducky-idle.png");
    Texture2D enemWalk = LoadTexture("Assets/Animation/Ducky/ducky-walk.png");
    // Enemy
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        Enemy e(
            GetRandomSpawnPos(),
            enemIdle, enemWalk,
            &curCol);
        e.setTarget(&sil);
        enemies.push_back(e);
    }
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        Vector2 textPosition = {110.f, 47.f};

        Rectangle HR{
            curCol * HealthWidth,
            row * HealthHeight,
            HealthWidth,
            HealthHeight};
        Rectangle DT{
            50,
            60,
            4 * HealthWidth,
            4 * HealthHeight};

        mapPos = Vector2Scale(sil.getworldPos(), -1.f);

        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);
        DrawTexturePro(healthBar, HR, DT, Vector2{20, 40}, 0.f, WHITE);

        for (auto &ducky : enemies)
        {
            ducky.tick(GetFrameTime());
        }

        /* // Debug
        Rectangle weaponRec = sil.getWeaponCollisionRec();
        DrawRectangleLines(weaponRec.x, weaponRec.y, weaponRec.width, weaponRec.height, RED); */

        for (auto &enemy : enemies)
        {
            if (CheckCollisionRecs(enemy.getFixedCollisionRec(), sil.getWeaponCollisionRec()))
            {
                enemy.takeDamage(sil.damagePerSec * GetFrameTime());
                if (!IsSoundPlaying(sil.hitSound))
                {
                    PlaySound(sil.hitSound);
                    StopSound(sil.slashSound);
                }
            }
        }
        if (!sil.getAlive()) // Character's Dead
        {
            if (!deathSoundPlayed)
            {
                PlaySound(deathSound);
                deathSoundPlayed = true;
            }
            DrawTextEx(customFont, "Game Over!", Vector2{0.4f * windowWidth, 0.4f * windowHeight}, 60, 2, RED);
            if (!IsSoundPlaying(deathSound))
            {
                break;
            }
        }
        else // Character's Alive
        {
            sil.tick(GetFrameTime());
            std::string silsHealth = "";
            silsHealth.append(std::to_string((int)sil.getHealth()), 0, 5);
            DrawTextEx(customFont, silsHealth.c_str(), textPosition, 15, 2, WHITE);
        }
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}