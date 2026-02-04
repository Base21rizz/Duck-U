#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale};
}

void BaseCharacter::tick(float deltaTime)
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
    if (Vector2Length(velocity) != 0.0)
    {

        // Set worldPos += velocity
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

        if (velocity.x < 0.f)
            rightLeft = -1.f;
        else if (velocity.x > 0.f)
            rightLeft = 1.f;

        if (velocity.y > 0.f)
        {
            texture = runDown;
        }
        else if (velocity.y < 0.f)
        {
            texture = runUp;
        }
        else
        {
            texture = run;
        }
    }
    else
    {
        // Animation selection
        texture = idle;
    }
    velocity = {};
    // Drawing character to the screen
    Rectangle source{frame * width,
                     0.f,
                     rightLeft * width,
                     height};
    Rectangle dest{getScreenPos().x,
                   getScreenPos().y,
                   scale * width,
                   scale * height};
    DrawTexturePro(texture,
                   source,
                   dest,
                   Vector2{},
                   0.f,
                   WHITE);
}