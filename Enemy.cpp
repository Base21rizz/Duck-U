#include "Enemy.h"
#include "raymath.h"
#include <string>

Enemy::Enemy(Vector2 pos, Texture2D idle_Texture, Texture2D run_Texture, float *Col) : texture(idle_Texture),
                                                                                       idle(idle_Texture),
                                                                                       run(run_Texture),
                                                                                       worldPos(pos),
                                                                                       HBCol(Col)
{
    width = texture.width / maxFrames;
    height = texture.height;
}
void Enemy::tick(float deltaTime)
{
    if (getAlive()) // Enemy is alive
    {
        std::string enemyHealth = "Enemy Health: ";
        enemyHealth.append(std::to_string(EnemyHealth), 0, 5);
        DrawText(enemyHealth.c_str(), 55.f, 45.f, 40, BLUE);
    }
    worldPosLastFrame = worldPos;

    if (!getAlive())
        return;
    Vector2 CharacterScreenPos = target->getScreenPos();
    Vector2 EnemyScreenPos = getScreenPos();
    Vector2 CharacterCenterPos = Vector2Add(CharacterScreenPos, Vector2{target->width * target->scale / 2, target->height * target->scale / 2});
    Vector2 EnemyCenterPos = Vector2Add(EnemyScreenPos, Vector2{width * scale / 2, height * scale / 2});

    velocity = Vector2Subtract(CharacterCenterPos, EnemyCenterPos);
    DrawRectangleLinesEx(getFixedCollisionRec(), 2.0f, BLUE);
    if (Vector2Length(velocity) < radius)
    {
        undoMovement();
        texture = idle;
        maxFrames = 2;
        velocity = {};
    }
    else
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed * deltaTime));
        texture = run;
        maxFrames = 4;
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
    }
    // BaseCharacter Ticking
    screenPos = Vector2Subtract(worldPos, target->getworldPos());
    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame >= maxFrames)
            frame = 0;
    }

    width = (float)texture.width / maxFrames;
    Rectangle source{frame * width,
                     0.f,
                     rightLeft * width,
                     height};
    Rectangle dest{screenPos.x,
                   screenPos.y,
                   scale * width,
                   scale * height};
    DrawTexturePro(texture,
                   source,
                   dest,
                   Vector2{},
                   0.f,
                   WHITE);
    velocity = {};

    if (CheckCollisionRecs(target->getFixedCollisionRec(), getFixedCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
        if (target->getHealth() == 100)
            *HBCol = 1;
        else if (target->getHealth() >= 83.33f)
            *HBCol = 2;
        else if (target->getHealth() >= 66.66f)
            *HBCol = 3;
        else if (target->getHealth() >= 50.f)
            *HBCol = 4;
        else if (target->getHealth() >= 33.33f)
            *HBCol = 5;
        else if (target->getHealth() >= 16.66f)
            *HBCol = 6;
        else if (target->getHealth() <= 0.f)
            *HBCol = 7;

        DrawText(std::to_string(*HBCol).c_str(), 200, 110, 20, BLUE);
    }
}
void Enemy::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle Enemy::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale};
}
Rectangle Enemy::getFixedCollisionRec()
{
    return Rectangle{
        getCollisionRec().x + 40,
        getCollisionRec().y + 60,
        width * 2 - 25,
        height * 2 - 5};
}

Vector2 Enemy::getScreenPos()
{
    return screenPos = Vector2Subtract(worldPos, target->getworldPos());
}

void Enemy::takeDamage(float damage)
{
    EnemyHealth -= damage;
    if (EnemyHealth <= 0)
    {
        setAlive(false);
    }
}