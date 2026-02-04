#include "raylib.h"
#include "Particle.h"
#include "raymath.h"

Particle::Particle()
{
}

void Particle::tick(float deltaTime, float rightLeftDir)
{
    float goon = 0.f;
    if (rightLeftDir > 0)
    {
        goon = 70.f;
    }

    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame >= maxFramesDust)
            frame = 0;
    }
    Rectangle source{frame * width,
                     0.f,
                     (float)width,
                     (float)height * rightLeftDir};
    Rectangle dest{(float)1280 / 2.f - scale * (0.5f * width) - goon,
                   (float)720 / 2.f - scale * (0.5f * height) + 320.f,
                   (float)scale * width,
                   (float)scale * height};
    DrawTexturePro(run_dust,
                   source,
                   dest,
                   Vector2{},
                   -90.f,
                   WHITE);
}