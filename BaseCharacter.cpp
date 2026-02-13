#include "BaseCharacter.h"
#include "raymath.h"
#include "Particle.h"
#include <string>

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
Rectangle BaseCharacter::getFixedCollisionRec()
{
    return Rectangle{
        getCollisionRec().x + 110,
        getCollisionRec().y + 70,
        width * 2 - 120,
        height * 2 - 50};
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    lastAttackTime += deltaTime;

    // Update direction based on velocity, even during attack
    if (Vector2Length(velocity) != 0.0)
    {
        if (velocity.x < 0.f)
        {
            rightLeft = -1.f;
            upDown = 0.f;
        }
        else if (velocity.x > 0.f)
        {
            rightLeft = 1.f;
            upDown = 0.f;
        }
        if (velocity.y > 0.f)
        {
            upDown = -1.f;
        }
        else if (velocity.y < 0.f)
        {
            upDown = 1.f;
        }
        else
        {
            upDown = 0.f;
        }
    }

    // Update normal animation frame only if not attacking
    if (!isAttacking)
    {
        runningTime += deltaTime;
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame >= maxFrames)
            {
                frame = 0;
            }
        }
    }

    // Start attack if not already attacking and mouse button pressed, with cooldown
    if (!isAttacking && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && lastAttackTime >= 0.2f)
    {
        isAttacking = true;
        attackFrame = 0;
        attackRunningTime = 0.f;
        lastAttackTime = 0.f;
        if (!IsSoundPlaying(slashSound) && !IsSoundPlaying(hitSound))
        {
            PlaySound(slashSound);
        }
    }

    // Handle attacking state
    if (isAttacking)
    {
        attackRunningTime += deltaTime;
        if (attackRunningTime >= updateTime)
        {
            attackFrame++;
            attackRunningTime = 0.f;
            if (attackFrame >= maxFrames)
            {
                isAttacking = false;
                attackFrame = 0;
            }
        }

        undoMovement();
        if (!getAlive())
            return;

        Vector2 origin{};
        Vector2 offset{};
        if (rightLeft > 0.f && upDown == 0.f) // right looking
        {
            origin = {0.f, 0.f};
            offset = {44.f, 25.f};

            weaponCollisionRec = {
                getScreenPos().x + offset.x * scale,
                getScreenPos().y + offset.y * scale,
                weaponWidth,
                weaponHeight};
            texture = rightAttack;
        }
        else if (rightLeft < 0.f && upDown == 0.f) // left looking
        {
            origin = {0.f, 0.f};
            offset = {10.f, 25.f};
            weaponCollisionRec = {
                getScreenPos().x + offset.x * scale,
                getScreenPos().y + offset.y * scale,
                weaponWidth,
                weaponHeight};
            texture = rightAttack;
        }
        else if (upDown > 0.f) // Up looking
        {
            origin = {0.f, 0.f};
            offset = {18.f, 15.f};
            weaponCollisionRec = {
                getScreenPos().x + offset.x * scale,
                getScreenPos().y + offset.y * scale,
                170,
                100};
            rightLeft = 1.f;
            texture = upAttack;
        }
        else if (upDown < 0.f) // Down looking
        {
            origin = {0.f, 0.f};
            offset = {20.f, 33.f};
            weaponCollisionRec = {
                getScreenPos().x + offset.x * scale,
                getScreenPos().y + offset.y * scale,
                170,
                113};
            texture = downAttack;
        }
    }
    else
    {
        // Reset the box so it disappears when not attacking
        weaponCollisionRec = {0, 0, 0, 0};

        if (Vector2Length(velocity) != 0.0)
        {
            // Set worldPos += velocity
            worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

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
    }

    // Drawing character to the screen
    Rectangle source{(isAttacking ? attackFrame : frame) * width,
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

    velocity = {};
}