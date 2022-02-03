#include <iostream>
//import main raylib header file
#include <raylib-cpp.hpp>
//import chrono for timers to keep track of elapsed time
#include <chrono>
#include <string>
#include <math.h>

class fullMatrix {
    private:
        double* array;
    public:
        int m;
        int n;

        double Get(const int x, const int y) {
            if(x >= m || y >= n){
                std::cout << "Invalid index (" << x << ", " << y << ") outside (" << m << ", " << n << ")\n";
                throw -1;
            }else{
                return array[x * n + y];
            }
        }

        void Set(const int x, const int y, const double val) {
            if(x >= m || y >= n){
                std::cout << m << " " << n << "\n";
                std::cout << x << " " << y << "\n";
                std::cout << "Invalid index (" << x << ", " << y << ") outside (" << m << ", " << n << ")\n";
                throw -1;
            }else{
                array[x * n + y] = val;
            }
        }

        fullMatrix(const int _m, const int _n) {
            array = new double[_m * _n];
            m = _m;
            n = _n;
            if(_m == _n){
                for(int i = 0; i < _m; i++){
                    this->Set(i, i, 1);
                }
            }
        }

        ~fullMatrix() {
            delete array;
        }

        void Debug(){
            for(int i = 0; i < this->m; i++){
                for(int j = 0; j < this->n; j++){
                    std::cout << this->Get(i, j) << " ";
                }
                std::cout << "\n";
            }
        }

        fullMatrix operator+(fullMatrix& other){
            if(this->m == other.m && this->n == other.n){
                fullMatrix rtn(this->m, this->n);
                for(int i = 0; i < this->m; i++){
                    for(int j = 0; j < this->n; j++){
                        rtn.Set(i, j, this->Get(i, j) + other.Get(i, j));
                    }
                }
                return rtn;
            }else{
                throw -1;
            }
        }

        fullMatrix operator-(fullMatrix& other){
            if(this->m == other.m && this->n == other.n){
                fullMatrix rtn(this->m, this->n);
                for(int i = 0; i < this->m; i++){
                    for(int j = 0; j < this->n; j++){
                        rtn.Set(i, j, this->Get(i, j) - other.Get(i, j));
                    }
                }
                return rtn;
            }else{
                throw -1;
            }
        }

        fullMatrix operator*(fullMatrix& other){
            if(this->n == other.m){
                fullMatrix rtn(this->m, this->n);
                for(int i = 0; i < this->m; i++){
                    for(int j = 0; j < this->n; j++){
                        double sum = 0;
                        for(int k = 0; k < this->n; k++){
                            sum += this->Get(k, j) * other.Get(i, k);
                        }
                        rtn.Set(i, j, sum);
                    }
                }
                return rtn;
            }else{
                throw -1;
            }
        }

        fullMatrix operator*(double scale){
            fullMatrix rtn(this->m, this->n);
            for(int i = 0; i < this->m; i++){
                for(int j = 0; j < this->n; j++){
                    rtn.Set(i, j, this->Get(i, j) * scale);
                }
            }
            return rtn;
        }

        fullMatrix operator/(double scale){
            fullMatrix rtn(this->m, this->n);
            for(int i = 0; i < this->m; i++){
                for(int j = 0; j < this->n; j++){
                    rtn.Set(i, j, this->Get(i, j) / scale);
                }
            }
            return rtn;
        }

        fullMatrix Minor(const int x, const int y){
            fullMatrix minor(this->m - 1, this->n - 1);

            int a = 0; //x-index into minor matrix
            int b = 0; //y-index into minor matrix

            for(int i = 0; i < this->m; i++){
                for(int j = 0; j < this->n; j++){
                    if(!(x == i | y == j | a >= minor.m | b >= minor.n)){
                        std::cout << a << ", " << b << " | " << i << ", " << j << "\n";
                        minor.Set(a, b, this->Get(i, j));
                        b++;
                    }
                }
                a++;
            }

            return minor;
        }

        double Det(){
            if(this->m == this->n){
                if(this->m == 2){
                    return (this->Get(0,0) * this->Get(1,1) - this->Get(0,1) * this->Get(1,0));
                }else{
                    //split down into reduced parts using each element in a row * its minor
                    double det = 0;
                    for(int i = 0; i < this->m; i++){
                        //alternates between adding and subtracting
                        if(i % 2 == 0){
                            //add
                            det += this->Get(i, 0) * this->Minor(i, 0).Det();
                        }else{
                            //sub
                        }
                    }
                    return det;
                }
            }else{
                return -1;
            }
        }

        fullMatrix Transpose(){
            if(this->n==this->m){
                //need to split down into recursive steps for 2.2 matrix transpose

                //1) Calculate determinant
                //2) Move and invert signs of elements
                //3) Multiply
            }
        }
};

class Object3D {
    public:
        //object
        raylib::Model* model;

        //physics
        raylib::Vector3 pos = raylib::Vector3(10, 1, 0);
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
            pos = pos + (vel.RotateByQuaternion(qRot) * dt); //rotates object space to global space

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

    Object3D obj("..\\obj\\materials.obj");
    Object3D artifact("..\\obj\\materials.obj");
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

    fullMatrix test(3, 3);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            test.Set(i, j, i * 3 + j);
        }
    }
    test.Debug();
    test.Minor(0, 0).Debug();

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

            obj.qRot = raylib::Vector4::FromMatrix(camera.GetMatrix());

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