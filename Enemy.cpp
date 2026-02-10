#include "Enemy.h"
#include "raymath.h"
#include <string>

Enemy::Enemy(Vector2 pos, Texture2D idle_Texture, Texture2D run_Texture) : worldPos(pos),
                                                                           texture(idle_Texture),
                                                                           idle(idle_Texture),
                                                                           run(run_Texture)
{
    width = texture.width / maxFrames;
    height = texture.height;
}
void Enemy::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    if (!getAlive())
        return;
    Vector2 CharacterScreenPos = target->getScreenPos();
    Vector2 EnemyScreenPos = getScreenPos();
    Vector2 CharacterCenterPos = Vector2Add(CharacterScreenPos, Vector2{target->width * target->scale / 2, target->height * target->scale / 2});
    Vector2 EnemyCenterPos = Vector2Add(EnemyScreenPos, Vector2{width * scale / 2, height * scale / 2});

    velocity = Vector2Subtract(CharacterCenterPos, EnemyCenterPos);
    DrawCircleV(CharacterCenterPos, 5, ORANGE);
    DrawCircleV(EnemyCenterPos, 5, PURPLE);
    DrawRectangleLinesEx(getCollisionRec(), 2.0f, YELLOW);
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
Vector2 Enemy::getScreenPos()
{
    return screenPos = Vector2Subtract(worldPos, target->getworldPos());
}