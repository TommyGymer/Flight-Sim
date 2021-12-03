#include <iostream>
#include <raylib-cpp.hpp>


int main() {
    // Initialization
    int screenWidth = 400;
    int screenHeight = 300;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window window(screenWidth, screenHeight, "RC-PC");
    
    window.SetState(FLAG_WINDOW_RESIZABLE);

    //raylib::Mesh mesh("obj/cube.obj");
    //raylib::Model plane("D:\\RC-PC\\obj\\box plane.obj");
    raylib::Model plane("..\\obj\\omega - testing.obj");    

    raylib::Camera3D camera(
        raylib::Vector3(5.0f, 4.0f, 5.0f),
        raylib::Vector3(0.0f, 0.0f, 0.0f),
        raylib::Vector3(0.0f, 1.0f, 0.0f),
        45.0f,
        CAMERA_PERSPECTIVE);

    camera.SetMode(CAMERA_ORBITAL);

    raylib::Shader shader("vendor\\raylib-cpp\\vendor\\raylib\\examples\\shaders\\resources\\shaders\\glsl330\\base.vs", "vendor\\raylib-cpp\\vendor\\raylib\\examples\\shaders\\resources\\shaders\\glsl330\\blur.fs");
    //raylib::Shader shader("D:\\RC-PC\\RC-PC\\vendor\\raylib-cpp\\vendor\\raylib\\examples\\shaders\\resources\\shaders\\glsl330\\base.vs", "D:\\RC-PC\\RC-PC\\vendor\\raylib-cpp\\vendor\\raylib\\examples\\shaders\\resources\\shaders\\glsl330\\grayscale.fs");

    for(int i = 0; i < plane.GetMaterialCount(); i++){
        plane.GetMaterials()[i].shader = shader;
    }

    // might need to set some of the shader values:
    //https://blog.weghos.com/raylib/raylib/examples/shaders/shaders_basic_lighting.c.html
    //https://github.com/MrOneTwo/Raylib-shaders/blob/master/src/main.cpp
    //https://github.com/MrOneTwo/Raylib-shaders/tree/master/build/resources/shaders

    //considering using tiny object loader to load in the objects as this seems to be more powerful
    //https://github.com/tinyobjloader/tinyobjloader

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

            camera.BeginMode();
            {
                DrawGrid(10, 1.0f);
                plane.Draw(raylib::Vector3(0.0f, 0.0f, 0.0f), 1.0f);
            }
            camera.EndMode();

            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    return 0;
}