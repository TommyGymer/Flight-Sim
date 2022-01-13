#include <iostream>
//import main raylib header file
#include <raylib-cpp.hpp>
//import chrono for timers to keep track of elapsed time
#include <chrono>

#include <math.h>

int main() {
    // Initialization
    int screenWidth = 1600;
    int screenHeight = 1200;

    auto start = std::chrono::high_resolution_clock::now();

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window window(screenWidth, screenHeight, "RC-PC");
    
    window.SetState(FLAG_WINDOW_RESIZABLE);

    //raylib::Mesh mesh("obj/cube.obj");
    //raylib::Model plane("D:\\RC-PC\\obj\\box plane.obj");
    raylib::Model plane("..\\obj\\materials.obj");

    raylib::Camera3D camera(
        raylib::Vector3(5.0f, 4.0f, 5.0f), //camera location
        raylib::Vector3(0.0f, 0.0f, 0.0f), //camera look
        raylib::Vector3(0.0f, 1.0f, 0.0f),
        60.0f, //fov
        CAMERA_PERSPECTIVE);

    camera.SetMode(CAMERA_ORBITAL);

    raylib::Shader shader("vendor\\raylib-cpp\\vendor\\raylib\\examples\\shaders\\resources\\shaders\\glsl330\\base.vs", "vendor\\raylib-cpp\\vendor\\raylib\\examples\\shaders\\resources\\shaders\\glsl330\\base.fs");
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

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);
            float obj_y = sin(duration.count() / 700.0f);
            float obj_x = sin(duration.count() / 350.0f);
            float obj_z = sin(duration.count() / 1400.0f);

            camera.SetTarget(raylib::Vector3(obj_x, obj_y, obj_z));

            camera.BeginMode();
            {
                DrawGrid(10, 1.0f);
                plane.Draw(raylib::Vector3(obj_x, obj_y, obj_z), 1.0f);
            }
            camera.EndMode();

            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    return 0;
}