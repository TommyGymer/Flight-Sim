#include "raylib.h"

int main(void)
{
    InitWindow(400, 300, "RC-PC");

    SetWindowState(FLAG_WINDOW_RESIZABLE);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        EndDrawing();
    }
}