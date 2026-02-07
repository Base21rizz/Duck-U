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
    DrawRectangle(
        getScreenPos().x,
        getScreenPos().y,
        5, 5, BLUE);
    DrawText("ScreenPos", getScreenPos().x, getScreenPos().y - 20, 10, BLUE);

    std::string worldPosText = "WorldPos: " + std::to_string((int)worldPos.x) + ", " + std::to_string((int)worldPos.y);
    DrawText(worldPosText.c_str(), 20, 20, 20, BLUE);
    DrawRectangleLinesEx(getCollisionRec(), 2.0f, GREEN);
    DrawCircleV(getScreenPos(), 5.f, RED);
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
            offset = {54.f, 40.f};
            weaponCollisionRec = {
                getScreenPos().x + offset.x * scale,
                getScreenPos().y + offset.y * scale,
                100,
                10};
            texture = rightAttack;

            DrawRectangleLines(
                weaponCollisionRec.x,
                weaponCollisionRec.y,
                weaponCollisionRec.width,
                weaponCollisionRec.height,
                RED);
        }
        else if (rightLeft < 0.f && upDown == 0.f) // left looking
        {
            undoMovement();
            origin = {0.f, 0.f};
            offset = {10.f, 40.f};
            weaponCollisionRec = {
                getScreenPos().x + offset.x * scale,
                getScreenPos().y + offset.y * scale,
                80,
                10};
            texture = rightAttack;
            DrawRectangleLines(
                weaponCollisionRec.x,
                weaponCollisionRec.y,
                weaponCollisionRec.width,
                weaponCollisionRec.height,
                RED);
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
                RED);
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
            std::string debugText = "Rotation: " + std::to_string(upDown) + ", " + std::to_string(upDown);
            DrawText(debugText.c_str(), 500, 280, 20, GREEN);
            DrawRectangleLines(
                weaponCollisionRec.x,
                weaponCollisionRec.y,
                weaponCollisionRec.width,
                weaponCollisionRec.height,
                RED);
        }
    }
    std::string debugText = "Rotation: " + std::to_string(rightLeft) + ", " + std::to_string(rightLeft);
    DrawText(debugText.c_str(), 500, 280, 20, GREEN);
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