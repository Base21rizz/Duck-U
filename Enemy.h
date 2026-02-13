#include "raylib.h"
#include "Character.h"

class Enemy
{
public:
    Enemy(Vector2 pos, Texture2D idle_Texture, Texture2D run_Texture, float *Col);
    void tick(float deltaTime);
    Vector2 getworldPos() { return worldPos; }
    Vector2 getScreenPos();
    void setTarget(Character *character) { target = character; }
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }
    void undoMovement();
    Rectangle getCollisionRec();
    Rectangle getFixedCollisionRec();
    float getHealth() const { return EnemyHealth; }
    void takeDamage(float damage);
    float width{};
    float height{};
    float scale{3.0f};

private:
    Character *target;
    Texture2D texture{LoadTexture("Assets/Animation/idle_right.png")};
    Texture2D idle{LoadTexture("Assets/Animation/idle_right.png")};
    Texture2D run{LoadTexture("Assets/Animation/run_right.png")};
    Texture2D healthBar = LoadTexture("Assets/04.png");
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
    float speed{100.f};

    Vector2 velocity{};
    float radius{50.f};
    bool alive{true};
    float damagePerSec{3.f};
    float *HBCol;
    float EnemyHealth{50.f};
    float EnemyHealthRow = 14;
    float EnemyHealthCol = 7;
    float EnemyHealthWidth = healthBar.width / EnemyHealthCol;
    float EnemyHealthHeight = healthBar.height / EnemyHealthRow;
    float curEnemyCol{1.f};
};