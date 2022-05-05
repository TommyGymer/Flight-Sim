#include <iostream>
//import main raylib header file
#include <raylib-cpp.hpp>
//import chrono for timers to keep track of elapsed time
#include <chrono>
#include <string>
#include <math.h>
#include <vector>

//local class file imports
#include "fullMatrix.cpp"

/*
|Variable name|Type|Usage|
|:---|:---|:---|
|model|raylib::model*|mesh and material data for the object|
|pos|raylib::Vector3|location of the object in 3D space|
|vel|raylib::Vector3|velocity of the object in 3D space|
|acc|raylib::Vector3|acceleration of the object in 3D space|
|qRot|raylib::Vector4|quaternion representing the rotation of the object in 3D space|
|qOme|raylib::Vector3|angular velocity of the object|
|scale|raylib::Vector3|scale factor of the model|
|look|raylib::Vector3|the look vector of the object|
*/

class Object3D {
    private:
        std::vector<Object3D> collides;
    public:
        //object
        raylib::Model* model;

        //physics
        fullMatrix pos = fullMatrix(MatrixType::Vector, 0, 1, 0);
        fullMatrix cvel = fullMatrix(MatrixType::Vector, 0, 0, 0);

        //global space
        fullMatrix gvel = fullMatrix(MatrixType::Vector, 0, 0, 0);
        fullMatrix gacc = fullMatrix(MatrixType::Vector, 0, -9.81, 0);

        //local space
        fullMatrix vel = fullMatrix(MatrixType::Vector, 0, 0, 0);
        fullMatrix acc = fullMatrix(MatrixType::Vector, 0, 0, 0);

        //rotation
        fullMatrix qRot = fullMatrix(MatrixType::Vector, 1, 0, 0, 0);
        fullMatrix angV = fullMatrix(MatrixType::Vector, 0, 0, 0);

        //scale
        raylib::Vector3 scale = raylib::Vector3(0.1, 0.1, 0.1);

        //look and up vectors
        raylib::Vector3 look = raylib::Vector3(0, 0, -1);
        raylib::Vector3 up = raylib::Vector3(0, -1, 0);

        //debug
        bool debug = false;

        void CollidesWith(Object3D* other){
            collides.push_back(*other);
        }

        Object3D(const std::string& fileName) {
            model = new raylib::Model(fileName.c_str());
            GenMeshTangents(model->GetMeshes());
            GenMeshBinormals(model->GetMeshes());
            collides = {};
        }

        //posistion, rotation axis, rotation angle, scale
        void Draw(){
            std::pair<raylib::Vector3, float> rot = qRot.GetVec4().ToAxisAngle();
            //model->Draw(pos.GetVec3(), std::get<0>(rot), (std::get<1>(rot) * 180)/PI, scale);
            model->Draw(raylib::Vector3(0,0,0), std::get<0>(rot), (std::get<1>(rot) * 180)/PI, raylib::Vector3(1.0, 1.0, 1.0));
            if(debug){
                DrawLine3D(pos.GetVec3(), (pos + vel + gvel).GetVec3(), GOLD);
                DrawLine3D(pos.GetVec3(), (pos + qRot.ToAxisAngle().GetComplex()).GetVec3(), LIME);
                DrawLine3D(pos.GetVec3(), (pos + look).GetVec3(), BLUE);
                DrawLine3D(pos.GetVec3(), (pos + up).GetVec3(), RED);
            }
        }

        void Update(float dt){
            //update quaternion with the angular velocity

            fullMatrix angVGlob(MatrixType::Vector, 0, angV.y(), 0);
            fullMatrix angVLocl(MatrixType::Vector, angV.x(), 0, 0);

            if(angVGlob.Length() != 0){
                float thetaGlob = angVGlob.Length() * dt;
                fullMatrix uGlob(angVGlob.Normalize());
                fullMatrix updateGlob(MatrixType::Vector, cos(thetaGlob/2), uGlob.x() * sin(thetaGlob/2), uGlob.y() * sin(thetaGlob/2), uGlob.z() * sin(thetaGlob/2));

                //update first for global, update second for local
                //rotate around z needs to be global, while rotation around x/y needs to be local
                qRot = updateGlob * qRot;
                qRot = qRot.Normalize();
            }

            if(angVLocl.Length() != 0){
                float thetaLolc = angVLocl.Length() * dt;
                fullMatrix uLocl(angVLocl.Normalize());
                fullMatrix updateLocl(MatrixType::Vector, cos(thetaLolc/2), uLocl.x() * sin(thetaLolc/2), uLocl.y() * sin(thetaLolc/2), uLocl.z() * sin(thetaLolc/2));

                //update first for global, update second for local
                //rotate around z needs to be global, while rotation around x/y needs to be local
                qRot = qRot * updateLocl;
                qRot = qRot.Normalize();
            }

            //integrating
            vel = vel + (acc * dt); //local space integration
            gvel = gvel + (gacc * dt); //global space integration

            //velocity damping/friction
            vel = vel * 0.8;
            // gvel = gvel * 0.8;

            

            //call collides here
            for(int i = 0; i < collides.size(); i++){
                Collide(collides[i], dt);
            }

            //cvel = vel.RotateByQuaternion(qRot) + gvel;

            pos = pos + (cvel * dt); //rotates object space to global space

            Matrix mat = model->GetTransform();
            Matrix s(mat);
            Matrix t(mat);
            s.m0 = scale.GetX();
            s.m5 = scale.GetY();
            s.m10 = scale.GetZ();
            t.m3 = pos.x();
            t.m7 = pos.y();
            t.m11 = pos.z();
            model->SetTransform((fullMatrix(t) * fullMatrix(s)).GetMatrix());

            look = fullMatrix(MatrixType::Vector, 0, 0, -1).RotateByQuaternion(qRot).GetVec3();
            up = fullMatrix(MatrixType::Vector, 0, 1, 0).RotateByQuaternion(qRot).GetVec3();

            //temporary collision detection
            if(pos.y() < 1){
                pos.y(1);
                vel.y(0);
                gvel.y(0);
            }
        }

        void Collide(Object3D other, float dt){
            if((vel.RotateByQuaternion(qRot) + gvel).Length() != 0){
                raylib::Ray ray((pos - other.pos).GetVec3(), cvel.GetVec3());
                raylib::RayCollision collision = ray.GetCollision(*other.model);
                if(collision.GetHit() && collision.GetDistance() <= (vel.RotateByQuaternion(qRot) + gvel).Length() * dt){
                    fullMatrix normal(collision.GetNormal());
                    // vel = vel.RotateByQuaternion(qRot).RemoveComponent(normal).DeRotateByQuaternion(qRot);
                    // gvel = gvel.RemoveComponent(normal);
                    cvel = gvel.RemoveComponent(normal) + vel.RotateByQuaternion(qRot).RemoveComponent(normal).DeRotateByQuaternion(qRot);
                    gvel = gvel - (gacc * dt);
                    // cvel = (cvel - (normal * cvel.Dot(normal)));// * 0.9;
                    std::cout << cvel.x() << ", " << cvel.y() << ", " << cvel.z() << "\n";
                    //std::cout << collision.GetDistance() << "\n";
                }else{
                    cvel = vel.RotateByQuaternion(qRot) + gvel;
                }
            }
        }
};