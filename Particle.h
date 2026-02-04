#pragma once
#include "raylib.h"

#ifndef PARTICLE_H
#define PARTICLE_H
class Particle
{
public:
    Particle();
    Texture2D run_dust{LoadTexture("Assets/Animation/Dust/Dash_Dust_Down.png")};
    float maxFramesDust{8};
    float updateTime{1.f / 15.f};
    float runningTime{};
    float frame{};
    float rightLeft{1.f};
    float scale{5.f};
    float width{(float)run_dust.width / maxFramesDust};
    float height{(float)run_dust.height};
    void tick(float deltaTime, float rightLeftDir);
    float rightLeftDir;

private:
};
#endif
