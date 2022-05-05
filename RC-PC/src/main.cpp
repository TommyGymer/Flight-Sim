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
enum class CameraState{First, Third};
enum class Key{A=65,B=66,C=67,D=68,E=69,F=70,G=71,H=72,I=73,J=74,K=75,L=76,M=77,N=78,O=79,P=80,Q=81,R=82,S=83,T=84,U=85,V=86,W=87,X=88,Y=89,Z=90};

//currently documenting: https://github.com/TommyGymer/Flight-Sim/commits/main?before=3745b21ce89bc7fbb89dfa7a8cf0cbd1ce6c7727+35&branch=main

int main() {
    //tests
    fullMatrix::Test(false);

    SetTraceLogLevel(LOG_WARNING); //add LOG_INFO to show detailed debug

    // Initialization
    int screenWidth = 1600;
    int screenHeight = 1200;
    
    auto start = std::chrono::high_resolution_clock::now();
    float total = 0;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window window(screenWidth, screenHeight, "RC-PC");
    
    window.SetState(FLAG_WINDOW_RESIZABLE);

    Object3D obj("obj\\materials.obj");
    Object3D ground("obj\\surface.obj");
    ground.scale = raylib::Vector3(200, 100, 200);
    ground.pos.y(0);
    obj.CollidesWith(&ground);
    obj.pos.x(200);
    obj.pos.y(10);
    ground.Update(0);

    // std::cout << ground.model->GetTransform().m0 << " " << ground.model->GetTransform().m1 << " " << ground.model->GetTransform().m2 << " " << ground.model->GetTransform().m3 << "\n";
    // std::cout << ground.model->GetTransform().m4 << " " << ground.model->GetTransform().m5 << " " << ground.model->GetTransform().m6 << " " << ground.model->GetTransform().m7 << "\n";
    // std::cout << ground.model->GetTransform().m8 << " " << ground.model->GetTransform().m9 << " " << ground.model->GetTransform().m10 << " " << ground.model->GetTransform().m11 << "\n";
    // std::cout << ground.model->GetTransform().m12 << " " << ground.model->GetTransform().m13 << " " << ground.model->GetTransform().m14 << " " << ground.model->GetTransform().m15 << "\n";

    obj.debug = false;

    raylib::Camera3D camera(
        raylib::Vector3(10.0f, 2.0f, 10.0f), //camera location
        raylib::Vector3(0.0f, 0.0f, 0.0f), //camera look
        raylib::Vector3(0.0f, 1.0f, 0.0f), //camera up
        60.0f, //fov
        CAMERA_PERSPECTIVE);

    raylib::Shader shader(
        "shaders\\base.vs",
        "shaders\\base.fs"
        );

    Material* mats = ground.model->GetMaterials();
    int n_mats = ground.model->GetMaterialCount();
    for(int i = 0; i < n_mats; i++){
        mats[i].shader = shader;
    }

    // might need to set some of the shader values:
    //https://blog.weghos.com/raylib/raylib/examples/shaders/shaders_basic_lighting.c.html
    //https://github.com/MrOneTwo/Raylib-shaders/blob/master/src/main.cpp
    //https://github.com/MrOneTwo/Raylib-shaders/tree/master/build/resources/shaders

    //considering using tiny object loader to load in the objects as this seems to be more powerful
    //https://github.com/tinyobjloader/tinyobjloader

    SetTargetFPS(120);

    std::cout << "Entering event loop\n";

    GameState state = GameState::Paused;
    CameraState cState = CameraState::First;

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

            obj.angV.x(0);
            obj.angV.y(0);
            obj.angV.z(0);
            //get mouse pos
            if((state == GameState::Playing) && total > 0.5){
                raylib::Vector2 mouse = raylib::Mouse::GetPosition() - raylib::Vector2(window.GetWidth()/2, window.GetHeight()/2);

                obj.angV.y(-mouse.GetX() * 0.1f);
                obj.angV.x(-mouse.GetY() * 0.1f);
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
                    obj.gvel.y(10);
                }
            }

            if(state == GameState::Paused){
                if(IsKeyPressed(static_cast<int>(Key::P))){
                    raylib::Mouse::SetPosition(window.GetWidth()/2, window.GetHeight()/2);
                    state = GameState::Playing;
                }
            }else{
                if(IsKeyPressed(static_cast<int>(Key::P))){
                    state = GameState::Paused;
                }
            }

            if(cState == CameraState::First){
                if(IsKeyPressed(static_cast<int>(Key::F))){
                    cState = CameraState::Third;
                }
            }else{
                if(IsKeyPressed(static_cast<int>(Key::F))){
                    cState = CameraState::First;
                }
            }

            if(IsKeyDown(static_cast<int>(Key::A))){
                obj.vel.x(-10);
            }
            if(IsKeyDown(static_cast<int>(Key::D))){
                obj.vel.x(10);
            }
            if(IsKeyDown(static_cast<int>(Key::S))){
                obj.vel.z(10);
            }
            if(IsKeyDown(static_cast<int>(Key::W))){
                obj.vel.z(-10);
            }

            if(IsKeyDown(static_cast<int>(Key::E))){
                obj.pos.x(0);
                obj.pos.z(0);
                obj.vel.x(0);
                obj.vel.z(0);
            }

            //calculating dt
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
            float dt = duration.count() / 1000000.0f;
            total += dt;
            start = std::chrono::high_resolution_clock::now();
            
            obj.Update(dt);

            if(cState == CameraState::Third){
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

                obj.Draw();
                ground.Draw();
            }
            camera.EndMode();

            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    return 0;
}