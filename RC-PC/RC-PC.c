#include "raylib.h"

int main(void)
{
    const int screenWidth = 2000;
    const int screenHeight = 1200;

    InitWindow(screenWidth, screenHeight, "RC PC");

    Camera camera = {{16.0f, 14.0f, 16.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, 45.0f, 0};

    Mesh mesh = 
}