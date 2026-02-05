#include "Enemy.h"

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
    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame >= maxFrames)
            frame = 0;
    }
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