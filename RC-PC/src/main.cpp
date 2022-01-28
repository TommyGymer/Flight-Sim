#include <iostream>
//import main raylib header file
#include <raylib-cpp.hpp>
//import chrono for timers to keep track of elapsed time
#include <chrono>
#include <string>
#include <math.h>

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
        raylib::Vector3 qOme = raylib::Vector3(1, 1, 0);

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
                vel.SetY(-vel.GetY() * 0.25);
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

    Object3D obj("..\\obj\\materials.obj");

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

            if(IsKeyPressed(32)){
                if(obj.pos.GetY() < 1.01){
                    obj.vel.SetY(10);
                }
            }
            obj.vel.SetX(0);
            obj.vel.SetZ(0);
            if(IsKeyDown(65)){
                obj.vel.SetX(-10);
            }
            if(IsKeyDown(68)){
                obj.vel.SetX(10);
            }
            if(IsKeyDown(83)){
                obj.vel.SetZ(10);
            }
            if(IsKeyDown(87)){
                obj.vel.SetZ(-10);
            }

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
            float dt = duration.count() / 1000000.0f;
            total += dt;
            start = std::chrono::high_resolution_clock::now();
                
            obj.Update(dt);

            camera.SetTarget(obj.pos);

            camera.BeginMode();
            {
                DrawGrid(1000, 10.0f);
                obj.Draw();
            }
            camera.EndMode();

            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    return 0;
}