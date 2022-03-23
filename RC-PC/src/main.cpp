#include <iostream>
//import main raylib header file
#include <raylib-cpp.hpp>
//import chrono for timers to keep track of elapsed time
#include <chrono>
#include <string>
#include <math.h>

//local class file imports
#include "fullMatrix.cpp"

enum class GameState{Menu, Playing, Paused};

class Object3D {
    public:
        //object
        raylib::Model* model;

        //physics
        fullMatrix pos = fullMatrix(MatrixType::Vector, 10, 1, 0);
        fullMatrix test_vel = fullMatrix(MatrixType::Vector, 0, 0, 0);
        
        //raylib::Vector3 pos = raylib::Vector3(10, 1, 0);
        raylib::Vector3 vel = raylib::Vector3(0, 0, 0);
        raylib::Vector3 acc = raylib::Vector3(0, -9.81, 0);

        //rotation
        fullMatrix test_qRot = fullMatrix(MatrixType::Vector, 1, 0, 0, 0);
        fullMatrix test_angV = fullMatrix(MatrixType::Vector, 0, 0, 0);

        raylib::Vector4 qRot = raylib::Vector4(0, 0, 0, 1);
        raylib::Vector3 qOme = raylib::Vector3(0, 0, 0);

        //scale
        raylib::Vector3 scale = raylib::Vector3(1, 1, 1);

        //look and up vectors
        raylib::Vector3 look = raylib::Vector3(0, 0, -1);
        raylib::Vector3 up = raylib::Vector3(0, -1, 0);

        //debug
        bool debug = false;

        Object3D(const std::string& fileName) {
            model = new raylib::Model(fileName.c_str());
        }

        //posistion, rotation axis, rotation angle, scale
        void Draw(){
            qRot = qRot.Normalize();
            std::pair<raylib::Vector3, float> rot = qRot.ToAxisAngle();
            model->Draw(pos.GetVec3(), std::get<0>(rot), (std::get<1>(rot) * 180)/PI, scale);
        }

        void Update(float dt){
            //update quaternion with the angular velocity

            if(debug){
                //std::cout << qOme.GetX() << ", " << qOme.GetY() << ", " << qOme.GetZ() << "\n";
                std::cout << qRot.GetX() << ", " << qRot.GetY() << ", " << qRot.GetZ() << ", " << qRot.GetW() << "\n";
            }

            if(qOme.Length() != 0){
                float theta = qOme.Length() * dt;
                raylib::Vector3 u = qOme.Normalize();
                raylib::Vector4 update(u.GetX() * sin(theta/2), u.GetY() * sin(theta/2), u.GetZ() * sin(theta/2), cos(theta/2));
                qRot = qRot * update;
                qRot = qRot.Normalize();
            }

            vel = vel + (acc.RotateByQuaternion(qRot.Invert()) * dt);
            //std::cout << vel.GetX() << ", " << vel.GetY() << ", " << vel.GetZ() << "\n";
            pos = pos + (fullMatrix(vel.RotateByQuaternion(qRot)) * dt); //rotates object space to global space

            look = raylib::Vector3(0, 0, -1).RotateByQuaternion(qRot);
            up = raylib::Vector3(0, 1, 0).RotateByQuaternion(qRot);

            //temporary collision detection
            if(pos.y() < 1){
                pos.Set(1, 0, 1);
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

    /**
     *fullMatrix test(3, 3);
     *test.Set(0, 0, 1);
     *test.Set(0, 1, -1);
     *test.Set(0, 2, 0);
     *
     *test.Set(1, 0, 1);
     *test.Set(1, 1, 1);
     *test.Set(1, 2, 1);
     *
     *test.Set(2, 0, 1.01);
     *test.Set(2, 1, 1.025);
     *test.Set(2, 2, 0.985);
     *
     *fullMatrix test2(test.Transpose());
     *test2.Debug();
     */

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
            if((state == GameState::Playing) && total > 1){
                raylib::Vector2 mouse = raylib::Mouse::GetPosition() - raylib::Vector2(window.GetWidth()/2, window.GetHeight()/2);
                //std::cout << "(" << mouse.GetX() << ", " << mouse.GetY() << ")\n";

                obj.qOme.SetY(-mouse.GetX() * 0.1f);
                obj.qOme.SetX(-mouse.GetY() * 0.1f);
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
                    obj.vel.SetY(10);
                }
            }

            if(state == GameState::Paused){
                if(IsKeyPressed(80)){ //p
                    state = GameState::Playing;
                }
            }else{
                if(IsKeyPressed(80)){ //p
                    state = GameState::Paused;
                }
            }

            obj.vel.SetX(obj.vel.GetX() * 0.95);
            obj.vel.SetZ(obj.vel.GetZ() * 0.95);
            //obj.qOme.SetX(0);
            //obj.qOme.SetY(0);
            obj.qOme.SetZ(0);
            if(IsKeyDown(65)){ //a
                obj.vel.SetX(-10);
                //obj.qOme.SetY(2);
            }
            if(IsKeyDown(68)){ //d
                obj.vel.SetX(10);
                //obj.qOme.SetY(-2);
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

            //std::cout << obj.look.GetX() << ", " << obj.look.GetY() << ", " << obj.look.GetZ() << "\n";

            camera.SetPosition(obj.pos.GetVec3());

            camera.SetTarget(obj.pos.GetVec3() + obj.look);
            camera.up = obj.up;

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