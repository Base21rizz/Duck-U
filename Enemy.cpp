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

    velocity = Vector2Subtract(target->getworldPos(), worldPos);
    if (Vector2Length(velocity) < radius)
    {
        velocity = {};
        texture = idle;
        maxFrames = 2;
    }
    else
    {
        Vector2 direction = Vector2Normalize(velocity);
        worldPos = Vector2Add(worldPos, Vector2Scale(direction, speed * deltaTime));
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