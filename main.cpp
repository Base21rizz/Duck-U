#include "raylib.h"

int main()
{
    int windowWidth{600};
    int windowHeight{400};
    InitWindow(windowWidth, windowHeight, "Duck U");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RED);
        EndDrawing();
    }
    CloseWindow();
}