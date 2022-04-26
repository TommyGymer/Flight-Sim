#include <iostream>
//import main raylib header file
#include <raylib-cpp.hpp>
//import chrono for timers to keep track of elapsed time
#include <chrono>
#include <string>
#include <math.h>

//local class file imports
#include "object.cpp"

enum class GameState{Menu, Playing, Paused};

int main() {
    //tests
    fullMatrix::Test();

    // Initialization
    int screenWidth = 1600;
    int screenHeight = 1200;
    
    auto start = std::chrono::high_resolution_clock::now();
    float total = 0;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window window(screenWidth, screenHeight, "RC-PC");
    
    window.SetState(FLAG_WINDOW_RESIZABLE);

    Object3D obj("..\\obj\\materials.obj");
    Object3D artifact("..\\obj\\materials.obj");
    artifact.scale = raylib::Vector3(0.5, 1, 0.5);
    artifact.qOme = raylib::Vector3(0, 1, 0);

    obj.debug = true;

    raylib::Camera3D camera(
        raylib::Vector3(10.0f, 2.0f, 10.0f), //camera location
        raylib::Vector3(0.0f, 0.0f, 0.0f), //camera look
        raylib::Vector3(0.0f, 1.0f, 0.0f),
        60.0f, //fov
        CAMERA_PERSPECTIVE);

    raylib::Shader shader(
        "vendor\\raylib-cpp\\vendor\\raylib\\examples\\shaders\\resources\\shaders\\glsl330\\base.vs",
        "vendor\\raylib-cpp\\vendor\\raylib\\examples\\shaders\\resources\\shaders\\glsl330\\base.fs"
        );

    // might need to set some of the shader values:
    //https://blog.weghos.com/raylib/raylib/examples/shaders/shaders_basic_lighting.c.html
    //https://github.com/MrOneTwo/Raylib-shaders/blob/master/src/main.cpp
    //https://github.com/MrOneTwo/Raylib-shaders/tree/master/build/resources/shaders

    //considering using tiny object loader to load in the objects as this seems to be more powerful
    //https://github.com/tinyobjloader/tinyobjloader

    SetTargetFPS(120);

    std::cout << "Entering event loop\n";

    GameState state = GameState::Paused;

    HideCursor();
    DisableCursor();
    raylib::Mouse::SetPosition(window.GetWidth()/2, window.GetHeight()/2);

    // Main game loop
    while (!window.ShouldClose()) // Detect window close button or ESC key
    {
        // Update
        camera.Update();
        // Draw
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            /**
             *keyboard and mouse control scheme
             *- mouse horizontal for alieron role
             *- mouse vertical for elevator role
             *    - mouse top-left justified
             *- a and d for rudder
             *- w and s for throttle
             *    - throttle as accerleration along with air resistance proportianal to square of velocity
             */

            //get mouse pos
            if((state == GameState::Playing) && total > 0.5){
                raylib::Vector2 mouse = raylib::Mouse::GetPosition() - raylib::Vector2(window.GetWidth()/2, window.GetHeight()/2);
                //std::cout << "(" << mouse.GetX() << ", " << mouse.GetY() << ")\n";

                obj.qOme.SetY(-mouse.GetX() * 0.1f);
                obj.qOme.SetX(-mouse.GetY() * 0.1f);

                obj.test_angV.y(-mouse.GetX() * 0.1f);
                obj.test_angV.x(-mouse.GetY() * 0.1f);
            }

            if(IsCursorOnScreen() && (state == GameState::Playing)){
                raylib::Mouse::SetPosition(window.GetWidth()/2, window.GetHeight()/2);
                HideCursor();
                DisableCursor();
            }else{
                ShowCursor();
                EnableCursor();
            }

            if(IsKeyDown(32)){ //space
                if(obj.pos.y() < 1.01){
                    //obj.vel.SetY(10);

                    obj.vel.y(10);
                }
            }

            if(state == GameState::Paused){
                if(IsKeyPressed(80)){ //p
                    raylib::Mouse::SetPosition(window.GetWidth()/2, window.GetHeight()/2);
                    state = GameState::Playing;
                }
            }else{
                if(IsKeyPressed(80)){ //p
                    state = GameState::Paused;
                }
            }

            //obj.vel.SetX(obj.vel.GetX() * 0.95);
            //obj.vel.SetZ(obj.vel.GetZ() * 0.95);
            obj.vel.x(obj.vel.x() * 0.95);
            obj.vel.z(obj.vel.z() * 0.95);
            //obj.qOme.SetX(0);
            //obj.qOme.SetY(0);
            obj.qOme.SetZ(0);
            obj.test_angV.z(0);
            if(IsKeyDown(65)){ //a
                //obj.vel.SetX(-10);
                obj.vel.x(-10);
                //obj.qOme.SetY(2);
            }
            if(IsKeyDown(68)){ //d
                //obj.vel.SetX(10);
                obj.vel.x(10);
                //obj.qOme.SetY(-2);
            }
            if(IsKeyDown(83)){ //s
                //obj.vel.SetZ(10);
                obj.vel.z(10);
            }
            if(IsKeyDown(87)){ //w
                //obj.vel.SetZ(-10);
                obj.vel.z(-10);
            }

            if(IsKeyDown(69)){
                obj.pos.x(0);
                obj.pos.z(0);
            }

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
            float dt = duration.count() / 1000000.0f;
            total += dt;
            start = std::chrono::high_resolution_clock::now();
                
            obj.Update(dt);
            artifact.Update(dt);

            //std::cout << obj.look.GetX() << ", " << obj.look.GetY() << ", " << obj.look.GetZ() << "\n";

            if(true){
                camera.SetPosition(raylib::Vector3(10, 10, 0));
                camera.SetTarget(raylib::Vector3(0, 0, 0));
            }else{
                camera.SetPosition(obj.pos.GetVec3());
                camera.SetTarget(obj.pos.GetVec3() + obj.look);
                camera.up = obj.up;
            }

            camera.BeginMode();
            {
                DrawGrid(1000, 1.0f);

                DrawLine3D(obj.pos.GetVec3(), (obj.pos + (obj.acc - fullMatrix(MatrixType::Vector, 0, -9.81, 0)) * 1000).GetVec3(), RED);
                DrawLine3D(obj.pos.GetVec3(), (obj.pos + obj.vel).GetVec3(), GOLD);

                obj.Draw();
                artifact.Draw();
            }
            camera.EndMode();

            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    return 0;
}