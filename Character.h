#ifndef CHARACTER_H
#define CHARACTER_H

#pragma once
#include "raylib.h"
#include "BaseCharacter.h"
#include "Particle.h"

class Character : public BaseCharacter
{
public:
    Character(
        int winWidth,
        int winHeight,
        Particle dusty);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec; }
    float getHealth() const { return health; }
    void takeDamage(float damage);
    Particle dust;

private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};

#endif