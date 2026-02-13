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
    Music bgm = LoadMusicStream("Assets/sound/Suspense.wav");
    SetMusicVolume(bgm, 0.1f);
    PlayMusicStream(bgm);
    bool deathSoundPlayed = false;

    // Character's Health Bar
    Texture2D healthBar = LoadTexture("Assets/04.png");
    float HealthRow = 14;
    float HealthCol = 7;
    float HealthWidth = healthBar.width / HealthCol;
    float HealthHeight = healthBar.height / HealthRow;
    float curCol{1};
    float row{0};

    // Map
    Texture2D map = LoadTexture("Assets/map.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{2.f};

    // Debug

    // Character
    Particle dust;
    Character sil{windowWidth, windowHeight, dust};

    std::vector<Enemy> enemies;
    const int MAX_ENEMIES = 0;
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
        UpdateMusicStream(bgm);
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
            DrawRectangleLines(enemy.getFixedCollisionRec().x, enemy.getFixedCollisionRec().y, enemy.getFixedCollisionRec().width, enemy.getFixedCollisionRec().height, BLUE);
        }
        if (!sil.getAlive()) // Character's Dead
        {
            StopMusicStream(bgm);
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
        // MapBoundaries
        if (sil.getworldPos().x < 0.f ||
            sil.getworldPos().y < 0.f ||
            sil.getworldPos().x + windowWidth > map.width * mapScale ||
            sil.getworldPos().y + windowHeight > map.height * mapScale)
        {
            sil.undoMovement();
        }
        if (((sil.getworldPos().y <= 2177 && sil.getworldPos().y >= 820) &&
             (sil.getworldPos().x <= 1878 && sil.getworldPos().x >= 609)))
        {
            sil.undoMovement();
        }
        if (((sil.getworldPos().y <= 1041 && sil.getworldPos().y >= 275) &&
             (sil.getworldPos().x <= 3115 && sil.getworldPos().x >= 2356)))
        {
            sil.undoMovement();
        }
        if (((sil.getworldPos().y <= 1922 && sil.getworldPos().y >= 1754) &&
             (sil.getworldPos().x <= 3380 && sil.getworldPos().x >= 2948)))
        {
            sil.undoMovement();
        }
        if (((sil.getworldPos().y <= 1019 && sil.getworldPos().y >= 0) &&
             (sil.getworldPos().x <= 4225 && sil.getworldPos().x >= 3449)))
        {
            sil.undoMovement();
        }
        if (((sil.getworldPos().y <= 1840 && sil.getworldPos().y >= 1019) &&
             (sil.getworldPos().x <= 4225 && sil.getworldPos().x >= 3644)))
        {
            sil.undoMovement();
        }
        if (((sil.getworldPos().y <= 2355 && sil.getworldPos().y >= 2119) &&
             (sil.getworldPos().x <= 4225 && sil.getworldPos().x >= 2276)))
        {
            sil.undoMovement();
        }

        EndDrawing();
    }
    UnloadMusicStream(bgm);
    UnloadTexture(map);
    CloseWindow();
}