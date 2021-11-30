#include <raylib-cpp.hpp>

int main() {
    
    // Initialization
    int screenWidth = 400;
    int screenHeight = 300;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window window(screenWidth, screenHeight, "RC-PC");
    
    window.SetState(FLAG_WINDOW_RESIZABLE);

    raylib::Camera camera(
        raylib::Vector3(5.0f, 4.0f, 5.0f),
        raylib::Vector3(0.0f, 2.0f, 0.0f),
        raylib::Vector3(0.0f, 1.0f, 0.0f),
        45.0f,
        CAMERA_PERSPECTIVE);

    camera.SetMode(CAMERA_ORBITAL);

    SetTargetFPS(60);

    // Main game loop
    while (!window.ShouldClose()) // Detect window close button or ESC key
    {
        // Update
        camera.Update();
        // Draw
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    return 0;
}