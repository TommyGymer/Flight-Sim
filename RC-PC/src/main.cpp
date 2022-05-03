#include <iostream>
//import main raylib header file
#include <raylib-cpp.hpp>
//import chrono for timers to keep track of elapsed time
#include <chrono>
#include <string>
#include <math.h>

//local class file imports
//#include "object.cpp"

enum class GameState{Menu, Playing, Paused};
enum class CameraState{First, Third};

//currently documenting: https://github.com/TommyGymer/Flight-Sim/commits/main?before=3745b21ce89bc7fbb89dfa7a8cf0cbd1ce6c7727+140&branch=main


class Object3D {
    public:
        //object
        raylib::Model* model;

        //physics
        raylib::Vector3 pos = raylib::Vector3(0, 1, 0);
        raylib::Vector3 vel = raylib::Vector3(0, 0, 0);
        raylib::Vector3 acc = raylib::Vector3(0, -9.81, 0);

        //rotation
        raylib::Vector4 qRot = raylib::Vector4(0, 0, 0, 1);
        raylib::Vector3 qOme = raylib::Vector3(0, 0, 0);

        //scale
        raylib::Vector3 scale = raylib::Vector3(1, 1, 1);

        Object3D(const std::string& fileName) {
            model = new raylib::Model(fileName.c_str());
        }

        //posistion, rotation axis, rotation angle, scale
        void Draw(){
            qRot = qRot.Normalize();
            std::pair<raylib::Vector3, float> rot = qRot.ToAxisAngle();
            model->Draw(pos, std::get<0>(rot), (std::get<1>(rot) * 180)/PI, scale);
        }

        void Update(float dt){
            vel = vel + (acc * dt);
            pos = pos + (vel * dt);

            //update quaternion with the angular velocity
            float angle = cos((qOme.Length() * dt)/2);
            raylib::Vector3 v = qOme.Normalize().Scale(sin((qOme.Length() * dt)/2));
            raylib::Vector4 update(v.GetX(), v.GetY(), v.GetZ(), angle);
            qRot = qRot * update;

            //temporary collision detection
            if(pos.GetY() < 1){
                pos.SetY(1);
                //vel.SetY(-vel.GetY() * 0.25);
                vel.SetY(0);
            }
        }
};

int main() {
    // Initialization
    int screenWidth = 1600;
    int screenHeight = 1200;

    auto start = std::chrono::high_resolution_clock::now();
    float total = 0;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window window(screenWidth, screenHeight, "RC-PC");
    
    window.SetState(FLAG_WINDOW_RESIZABLE);

    Object3D obj("obj\\materials.obj");
    Object3D artifact("obj\\materials.obj");
    artifact.scale = raylib::Vector3(0.5, 1, 0.5);
    artifact.qOme = raylib::Vector3(0, 1, 0);

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

    // Main game loop
    while (!window.ShouldClose()) // Detect window close button or ESC key
    {
        // Update
        camera.Update();
        // Draw
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            if(IsKeyDown(32)){
                if(obj.pos.GetY() < 1.01){
                    obj.vel.SetY(10);
                }
            }

            obj.vel.SetX(obj.vel.GetX() * 0.8);
            obj.vel.SetZ(obj.vel.GetZ() * 0.8);
            if(IsKeyDown(65)){ //a
                obj.vel.SetX(-10);
            }
            if(IsKeyDown(68)){ //d
                obj.vel.SetX(10);
            }
            if(IsKeyDown(83)){ //s
                obj.vel.SetZ(10);
            }
            if(IsKeyDown(87)){ //w
                obj.vel.SetZ(-10);
            }

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
            float dt = duration.count() / 1000000.0f;
            total += dt;
            start = std::chrono::high_resolution_clock::now();
                
            obj.Update(dt);
            artifact.Update(dt);

            //camera.SetTarget(obj.pos);
            camera.SetPosition(obj.pos);

            camera.BeginMode();
            {
                DrawGrid(1000, 1.0f);
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

// int main() {
//     //tests
//     fullMatrix::Test(true);

//     SetTraceLogLevel(LOG_WARNING); //add LOG_INFO to show detailed debug

//     // Initialization
//     int screenWidth = 1600;
//     int screenHeight = 1200;
    
//     auto start = std::chrono::high_resolution_clock::now();
//     float total = 0;

//     raylib::Color textColor(LIGHTGRAY);
//     raylib::Window window(screenWidth, screenHeight, "RC-PC");
    
//     window.SetState(FLAG_WINDOW_RESIZABLE);

//     Object3D obj(".\\obj\\materials.obj");
//     Object3D ground(".\\obj\\surface.obj");
//     ground.scale = raylib::Vector3(10, 10, 10);
//     ground.pos.y(0);

//     obj.debug = true;

//     raylib::Camera3D camera(
//         raylib::Vector3(10.0f, 2.0f, 10.0f), //camera location
//         raylib::Vector3(0.0f, 0.0f, 0.0f), //camera look
//         raylib::Vector3(0.0f, 1.0f, 0.0f), //camera up
//         60.0f, //fov
//         CAMERA_PERSPECTIVE);

//     raylib::Shader shader(
//         "shaders\\base.vs",
//         "shaders\\base.fs"
//         );

//     Material* mats = ground.model->GetMaterials();
//     int n_mats = ground.model->GetMaterialCount();
//     for(int i = 0; i < n_mats; i++){
//         mats[i].shader = shader;
//     }

//     // might need to set some of the shader values:
//     //https://blog.weghos.com/raylib/raylib/examples/shaders/shaders_basic_lighting.c.html
//     //https://github.com/MrOneTwo/Raylib-shaders/blob/master/src/main.cpp
//     //https://github.com/MrOneTwo/Raylib-shaders/tree/master/build/resources/shaders

//     //considering using tiny object loader to load in the objects as this seems to be more powerful
//     //https://github.com/tinyobjloader/tinyobjloader

//     SetTargetFPS(120);

//     std::cout << "Entering event loop\n";

//     GameState state = GameState::Paused;
//     CameraState cState = CameraState::Third;

//     HideCursor();
//     DisableCursor();
//     raylib::Mouse::SetPosition(window.GetWidth()/2, window.GetHeight()/2);

//     // Main game loop
//     while (!window.ShouldClose()) // Detect window close button or ESC key
//     {
//         // Update
//         camera.Update();
//         // Draw
//         BeginDrawing();
//         {
//             ClearBackground(RAYWHITE);

//             /**
//              *keyboard and mouse control scheme
//              *- mouse horizontal for alieron role
//              *- mouse vertical for elevator role
//              *    - mouse top-left justified
//              *- a and d for rudder
//              *- w and s for throttle
//              *    - throttle as accerleration along with air resistance proportianal to square of velocity
//              */

//             obj.angV.x(0);
//             obj.angV.y(0);
//             obj.angV.z(0);
//             //get mouse pos
//             if((state == GameState::Playing) && total > 0.5){
//                 raylib::Vector2 mouse = raylib::Mouse::GetPosition() - raylib::Vector2(window.GetWidth()/2, window.GetHeight()/2);

//                 obj.angV.y(-mouse.GetX() * 0.1f);
//                 obj.angV.x(-mouse.GetY() * 0.1f);
//             }

//             if(IsCursorOnScreen() && (state == GameState::Playing)){
//                 raylib::Mouse::SetPosition(window.GetWidth()/2, window.GetHeight()/2);
//                 HideCursor();
//                 DisableCursor();
//             }else{
//                 ShowCursor();
//                 EnableCursor();
//             }

//             if(IsKeyDown(32)){ //space
//                 if(obj.pos.y() < 1.01){
//                     obj.gvel.y(10);
//                 }
//             }

//             if(state == GameState::Paused){
//                 if(IsKeyPressed(80)){ //p
//                     raylib::Mouse::SetPosition(window.GetWidth()/2, window.GetHeight()/2);
//                     state = GameState::Playing;
//                 }
//             }else{
//                 if(IsKeyPressed(80)){ //p
//                     state = GameState::Paused;
//                 }
//             }

//             if(cState == CameraState::First){
//                 if(IsKeyPressed(70)){
//                     cState = CameraState::Third;
//                 }
//             }else{
//                 if(IsKeyPressed(70)){
//                     cState = CameraState::First;
//                 }
//             }

//             obj.vel.x(obj.vel.x() * 0.95);
//             obj.vel.z(obj.vel.z() * 0.95);
//             obj.gvel.x(obj.gvel.x() * 0.95);
//             obj.gvel.z(obj.gvel.z() * 0.95);
//             if(IsKeyDown(65)){ //a
//                 obj.vel.x(-10);
//             }
//             if(IsKeyDown(68)){ //d
//                 obj.vel.x(10);
//             }
//             if(IsKeyDown(83)){ //s
//                 obj.vel.z(10);
//             }
//             if(IsKeyDown(87)){ //w
//                 obj.vel.z(-10);
//             }

//             if(IsKeyDown(69)){ //e
//                 obj.pos.x(0);
//                 obj.pos.z(0);
//                 obj.vel.x(0);
//                 obj.vel.z(0);
//             }

//             auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
//             float dt = duration.count() / 1000000.0f;
//             total += dt;
//             start = std::chrono::high_resolution_clock::now();
                
//             obj.Update(dt);

//             if(cState == CameraState::Third){
//                 camera.SetPosition(raylib::Vector3(10, 10, 0));
//                 camera.SetTarget(raylib::Vector3(0, 0, 0));
//             }else{
//                 camera.SetPosition(obj.pos.GetVec3());
//                 camera.SetTarget(obj.pos.GetVec3() + obj.look);
//                 camera.up = obj.up;
//             }

//             camera.BeginMode();
//             {
//                 DrawGrid(1000, 1.0f);

//                 obj.Draw();
//                 ground.Draw();
//             }
//             camera.EndMode();

//             DrawFPS(10, 10);
//         }
//         EndDrawing();
//     }

//     return 0;
// }