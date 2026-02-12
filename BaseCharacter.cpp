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

    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame >= maxFrames)
            frame = 0;
    }
    // Debugging

    std::string worldPosText = "WorldPos: " + std::to_string((int)worldPos.x) + ", " + std::to_string((int)worldPos.y);
    DrawText(worldPosText.c_str(), 20, 20, 20, BLUE);
    DrawRectangleLinesEx(getFixedCollisionRec(), 2.0f, BLUE);
    if (Vector2Length(velocity) != 0.0)
    {

        // Set worldPos += velocity
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

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
            texture = runDown;
            upDown = -1.f;
        }
        else if (velocity.y < 0.f)
        {
            texture = runUp;
            upDown = 1.f;
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
    Vector2 origin{};
    Vector2 offset{};
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {

        if (rightLeft > 0.f && upDown == 0.f) // right looking
        {
            undoMovement();
            if (!getAlive())
                return;
            origin = {0.f, 0.f};
            offset = {44.f, 25.f};

            weaponCollisionRec = {
                getScreenPos().x + offset.x * scale,
                getScreenPos().y + offset.y * scale,
                weaponWidth,
                weaponHeight};
            texture = rightAttack;

            DrawRectangleLines(
                weaponCollisionRec.x,
                weaponCollisionRec.y,
                weaponCollisionRec.width,
                weaponCollisionRec.height,
                BLUE);
        }
        else if (rightLeft < 0.f && upDown == 0.f) // left looking
        {
            undoMovement();
            origin = {0.f, 0.f};
            offset = {10.f, 25.f};
            weaponCollisionRec = {
                getScreenPos().x + offset.x * scale,
                getScreenPos().y + offset.y * scale,
                weaponWidth,
                weaponHeight};
            texture = rightAttack;
            DrawRectangleLines(
                weaponCollisionRec.x,
                weaponCollisionRec.y,
                weaponCollisionRec.width,
                weaponCollisionRec.height,
                BLUE);
        }
        if (upDown > 0.f) // Up looking
        {
            undoMovement();
            if (!getAlive())
                return;
            origin = {0.f, 0.f};
            offset = {18.f, 15.f};
            weaponCollisionRec = {
                getScreenPos().x + offset.x * scale,
                getScreenPos().y + offset.y * scale,
                170,
                100};
            rightLeft = 1.f;
            texture = upAttack;
            DrawRectangleLines(
                weaponCollisionRec.x,
                weaponCollisionRec.y,
                weaponCollisionRec.width,
                weaponCollisionRec.height,
                BLUE);
        }
        else if (upDown < 0.f) // Down looking
        {
            undoMovement();
            origin = {0.f, 0.f};
            offset = {20.f, 33.f};
            weaponCollisionRec = {
                getScreenPos().x + offset.x * scale,
                getScreenPos().y + offset.y * scale,
                170,
                113};
            texture = downAttack;
            DrawRectangleLines(
                weaponCollisionRec.x,
                weaponCollisionRec.y,
                weaponCollisionRec.width,
                weaponCollisionRec.height,
                BLUE);
        }
        }
    else
    {
        // Reset the box so it disappears when not attacking
        weaponCollisionRec = {0, 0, 0, 0};
    }
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

    velocity = {};
}