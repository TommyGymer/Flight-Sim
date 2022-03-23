#include <iostream>
//import main raylib header file
#include <raylib-cpp.hpp>
//import chrono for timers to keep track of elapsed time
#include <chrono>
#include <string>
#include <math.h>

//local class file imports
#include "fullMatrix.cpp"

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