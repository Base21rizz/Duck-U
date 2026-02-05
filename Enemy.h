#include "raylib.h"

class Enemy
{
public:
    Enemy(Vector2 pos, Texture2D idle_Texture, Texture2D run_Texture);
    Vector2 getworldPos() { return worldPos; }
    void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRec();

private:
    Texture2D texture{LoadTexture("Assets/Animation/idle_right.png")};
    Texture2D idle{LoadTexture("Assets/Animation/idle_right.png")};
    Texture2D run{LoadTexture("Assets/Animation/run_right.png")};

    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1 : facing right, -1 : facing left
    float rightLeft{1.f};
    // Animation variable
    float runningTime{};
    int frame{};
    int maxFrames{2};
    float updateTime{1.f / 6.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{3.0f};
};