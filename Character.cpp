#include "Character.h"
#include "raymath.h"
#include "Particle.h"
#include <string>

Character::Character(int winWidth, int winHeight, Particle dusty) : windowWidth(winWidth),
                                                                    windowHeight(winHeight),
                                                                    dust(dusty)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float deltaTime)
{
    if (!getAlive())
    {
        return;
    }

    // Animation Variable
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    dust.tick(GetFrameTime(), getRightLeft(), velocity);
    BaseCharacter::tick(deltaTime);
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0)
    {
        setAlive(false);
    }
}