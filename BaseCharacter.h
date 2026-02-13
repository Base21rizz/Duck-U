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
    Rectangle getFixedCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }
    float getRightLeft() { return rightLeft; }
    void stopSlashSound() { StopSound(slashSound); }
    float width{};
    float height{};
    float scale{3.0f};
    // Weapon dimensions
    float weaponWidth = 130.f;
    float weaponHeight = 80.f;

    Sound hitSound = LoadSound("Assets/sound/Sword_Whoosh_03.wav");
    Sound slashSound = LoadSound("Assets/sound/whoosh_2.wav");
    bool hitSoundPlaying{false};

protected:
    // Animation
    Texture2D texture{LoadTexture("Assets/Animation/idle_right.png")};
    Texture2D idle{LoadTexture("Assets/Animation/idle_right.png")};
    Texture2D run{LoadTexture("Assets/Animation/run_right.png")};
    Texture2D runDown{LoadTexture("Assets/Animation/run_down.png")};
    Texture2D runUp{LoadTexture("Assets/Animation/run_up.png")};
    Texture2D rightAttack{LoadTexture("Assets/Animation/attack1_right.png")};
    Texture2D leftAttack{LoadTexture("Assets/Animation/attack1_left.png")};
    Texture2D upAttack{LoadTexture("Assets/Animation/attack1_up.png")};
    Texture2D downAttack{LoadTexture("Assets/Animation/attack1_down.png")};

    Vector2 worldPos{};
    Rectangle weaponCollisionRec{};
    Vector2 worldPosLastFrame{};
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    float upDown{0.f};
    Vector2 directional{rightLeft, upDown};
    // Animation variable
    float runningTime{};
    int frame{};
    int maxFrames{8};
    float updateTime{1.f / 18.f};
    float speed{4.f};
    Vector2 velocity{};
    float soundTime{0.f};
    // Attack animation
    bool isAttacking{false};
    float attackRunningTime{};
    int attackFrame{};
    float lastAttackTime{};

private:
    bool alive{true};
};
#endif
