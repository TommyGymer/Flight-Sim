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
        fullMatrix pos = fullMatrix(MatrixType::Vector, 0, 1, 0);

        //global space
        fullMatrix gvel = fullMatrix(MatrixType::Vector, 0, 0, 0);
        fullMatrix gacc = fullMatrix(MatrixType::Vector, 0, -9.81, 0);

        //local space
        fullMatrix vel = fullMatrix(MatrixType::Vector, 0, 0, 0);
        fullMatrix acc = fullMatrix(MatrixType::Vector, 0, 0, 0);

        //rotation
        fullMatrix test_qRot = fullMatrix(MatrixType::Vector, 1, 0, 0, 0);
        fullMatrix test_angV = fullMatrix(MatrixType::Vector, 0, 0, 0);

        //scale
        raylib::Vector3 scale = raylib::Vector3(0.1, 0.1, 0.1);

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
            std::pair<raylib::Vector3, float> rot = test_qRot.GetVec4().ToAxisAngle();
            model->Draw(pos.GetVec3(), std::get<0>(rot), (std::get<1>(rot) * 180)/PI, scale);
            if(debug){
                DrawLine3D(pos.GetVec3(), (pos + vel + gvel).GetVec3(), GOLD);
                DrawLine3D(pos.GetVec3(), (pos + test_qRot.ToAxisAngle().GetComplex()).GetVec3(), LIME);
                DrawLine3D(pos.GetVec3(), (pos + look).GetVec3(), BLUE);
                DrawLine3D(pos.GetVec3(), (pos + up).GetVec3(), RED);
            }
        }

        void Update(float dt){
            //update quaternion with the angular velocity

            if(debug){
                //std::cout << qOme.GetX() << ", " << qOme.GetY() << ", " << qOme.GetZ() << "\n";
                //std::cout << qRot.GetX() << ", " << qRot.GetY() << ", " << qRot.GetZ() << ", " << qRot.GetW() << "\n";
                //std::cout << "(" << vel.GetX() << ", " << vel.GetY() << ", " << vel.GetZ() << ")" << "\n";
                //(fullMatrix(vel.RotateByQuaternion(qRot)) * dt).Debug();
                //std::cout << "(" << pos.GetVec3().GetX() << ", " << pos.GetVec3().GetY() << ", " << pos.GetVec3().GetZ() << ")" << "\n";
                //std::cout << "(" << pos.x() << ", " << pos.y() << ", " << pos.z() << ")" << "\n";
                //std::cout << pos.x() << ", " << pos.y() << ", " << pos.z() << "\n";
                //std::cout << vel.x() << ", " << vel.y() << ", " << vel.z() << "\n";
            }

            if(test_angV.Length() != 0){
                test_angV = test_angV.DeRotateByQuaternion(test_qRot);
                float theta = test_angV.Length() * dt;
                fullMatrix u(test_angV.Normalize());
                fullMatrix update(MatrixType::Vector, cos(theta/2), u.x() * sin(theta/2), u.y() * sin(theta/2), u.z() * sin(theta/2));

                test_qRot = test_qRot * update;
                test_qRot = test_qRot.Normalize();
            }

            //integrating
            vel = vel + (acc * dt); //local space integration
            gvel = gvel + (gacc * dt); //global space integration
            pos = pos + ((vel.RotateByQuaternion(test_qRot) + gvel) * dt); //rotates object space to global space

            look = fullMatrix(MatrixType::Vector, 0, 0, -1).RotateByQuaternion(test_qRot).GetVec3();
            up = fullMatrix(MatrixType::Vector, 0, 1, 0).RotateByQuaternion(test_qRot).GetVec3();

            //temporary collision detection
            if(pos.y() < 1){
                pos.y(1);
                vel.y(0);
                gvel.y(0);
            }
        }
};