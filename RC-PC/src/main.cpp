#include <raylib-cpp.hpp>

int main() {
    
    // Initialization
    int screenWidth = 400;
    int screenHeight = 300;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window window(screenWidth, screenHeight, "RC-PC");
    
    window.SetState(FLAG_WINDOW_RESIZABLE);

    SetTargetFPS(60);

    // Main game loop
    while (!window.ShouldClose()) // Detect window close button or ESC key
    {
        // Update

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);



        EndDrawing();
    }

    return 0;
}