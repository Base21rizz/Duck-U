#pragma once
#include "raylib.h"

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getworldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }

protected:
    Texture2D texture{LoadTexture("Assets/Animation/idle_right.png")};
    Texture2D idle{LoadTexture("Assets/Animation/idle_right.png")};
    Texture2D run{LoadTexture("Assets/Animation/run_right.png")};
    Texture2D runDown{LoadTexture("Assets/Animation/run_down.png")};
    Texture2D runUp{LoadTexture("Assets/Animation/run_up.png")};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // Animation variable
    float runningTime{};
    int frame{};
    int maxFrames{8};
    float updateTime{1.f / 18.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{3.0f};
    Vector2 velocity{};

private:
    bool alive{true};
};
#endif
