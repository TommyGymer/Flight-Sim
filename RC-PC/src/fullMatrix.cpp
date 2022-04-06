#include <iostream>
#include <math.h>
#include <raylib-cpp.hpp>
#include <assert.h>
#include <algorithm>
#include <iterator>

enum class MatrixType {Vector, Coord, Matrix};

/** Test of the fullMatrix class;
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

class fullMatrix {
    public:
        int m;
        int n;
        double* array;

        //1   2   3   ...   n
        //2     
        //3     
        //...   
        //m     

        /**
         *Returns the value at the given x, y in the matrix
         *
         *@param x the x coordinate in the matrix of n
         *@param y the y coordinate in the matrix of m
         *@returns the value at x, y in the matrix
         */
        double Get(const int x, const int y) {
            if(x >= m || y >= n){
                std::cout << "Invalid index (" << x << ", " << y << ") outside (" << m << ", " << n << ")\n";
                throw -1;
            }else{
                return array[x * n + y];
            }
        }

        double const w(){
            if((m == 4 && n ==1) || (m == 1 && n ==4)){
                return array[0];
            }else{
                std::cout << "Not a vector or coordinate\n";
                throw -1;
            }
        }

        double const x(){
            if((m == 3 && n == 1) || (m == 1 && n == 3)){
                return array[0];
            }else if((m == 4 && n ==1) || (m == 1 && n ==4)){
                return array[1];
            }else{
                std::cout << "Not a vector or coordinate\n";
                throw -1;
            }
        }

        double const y(){
            if((m == 3 && n == 1) || (m == 1 && n == 3)){
                return array[1];
            }else if((m == 4 && n ==1) || (m == 1 && n ==4)){
                return array[2];
            }else{
                std::cout << "Not a vector or coordinate\n";
                throw -1;
            }
        }

        double const z(){
            if((m == 3 && n == 1) || (m == 1 && n == 3)){
                return array[2];
            }else if((m == 4 && n == 1) || (m == 1 && n == 4)){
                return array[3];
            }else{
                std::cout << "Not a vector or coordinate\n";
                throw -1;
            }
        }

        void Set(const int x, const int y, const double val) {
            if(x >= m || y >= n){
                std::cout << "Invalid index during set, (" << x << ", " << y << ") outside (" << m << ", " << n << ")\n";
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

        //copy constructor
        fullMatrix(const fullMatrix& other){
            m = other.m;
            n = other.n;
            array = new double[m * n];
            //std::cout << "size at creation: " << sizeof(array) << " bytes m*n: " << m*n << "\n"; //array has length 72bytes
            //memcpy(&array, &(other.array), m*n*sizeof(array)+1);
            //std::copy(other.array, other.array + (n * m), array);
            //std::cout << "Pointer to prev data: " << &(other.array) << "\n";
            //std::cout << m*n << "\n";
            //std::cout << m << ", " << n << "\n";
            //std::cout << "Data from the copied array(" << &array << "): " << array[0] << ", " << array[1] << ", " << array[2] << "\n";
        }

        fullMatrix(raylib::Vector3 other){
            m = 3;
            n = 1;
            array = new double[m * n];
            array[0] = other.GetX();
            array[1] = other.GetY();
            array[2] = other.GetZ();
        }

        fullMatrix(raylib::Vector4 other){
            m = 4;
            n = 1;
            array = new double[m * n];
            array[0] = other.GetW();
            array[1] = other.GetX();
            array[2] = other.GetY();
            array[3] = other.GetZ();
        }

        raylib::Vector3 GetVec3(){
            if((m == 3 && n == 1) || (m == 1 && n == 3)){
                return raylib::Vector3(array[0], array[1], array[2]);
            }else{
                std::cout << "Matrix wrong size\n";
                throw -1;
            }
        }

        raylib::Vector4 GetVec4(){
            if((m == 4 && n == 1) || (m == 1 && n == 4)){
                return raylib::Vector4(array[1], array[2], array[3], array[0]);
            }else{
                std::cout << "Matrix wrong size\n";
                throw -1;
            }
        }

        fullMatrix(MatrixType type, const double x, const double y, const double z){
            int _m = 0;
            int _n = 0;
            if(type == MatrixType::Vector){
                _m = 3;
                _n = 1;
            }else if(type == MatrixType::Coord){
                _m = 1;
                _n = 3;
            }
            
            array = new double[_m * _n];
            m = _m;
            n = _n;
            array[0] = x;
            array[1] = y;
            array[2] = z;
            //std::cout << &array << "\n";
        }

        fullMatrix(MatrixType type, const double w, const double x, const double y, const double z){
            int _m = 0;
            int _n = 0;
            if(type == MatrixType::Vector){
                _m = 3;
                _n = 1;
            }else if(type == MatrixType::Coord){
                _m = 1;
                _n = 3;
            }

            array = new double[_m * _n];
            m = _m;
            n = _n;
            array[0] = w;
            array[1] = x;
            array[2] = y;
            array[3] = z;
        }

        ~fullMatrix() {
            //std::cout << "Deleting: " << &array << "\n";
            //std::cout << n << ", " << m << "\n";
            //std::cout << "Size: " << sizeof(array) << " bytes" << "\n";
            //std::cout << array[0] << ", " << array[1] << ", " << array[2] << ", " << array[3] << ", " << array[4] << ", " << array[5] << ", " << array[6] << "\n";
            delete[] array;
        }

        void Debug(){
            std::cout << "Dubugging " << this->m << " by " << this-> n << " matrix\n";
            for(int i = 0; i < this->m; i++){
                for(int j = 0; j < this->n; j++){
                    std::cout << this->Get(i, j) << " ";
                }
                std::cout << "\n";
            }
            std::cout << "Finished debug\n";
        }

        void flipMN(){
            //this is probably not sufficient for anything beyond vectors and coordinates
            int tmp = m;
            m = n;
            n = tmp;
        }

        fullMatrix operator+(fullMatrix other){
            if(m == other.m && n == other.n){
                fullMatrix rtn(m, n);
                other.Debug();
                std::cout << &(array) << "\n" << &(other.array) << "\n";
                std::cout << other.x() << ", " << other.y() << ", " << other.z() << "\n";
                for(int i = 0; i < m; i++){
                    for(int j = 0; j < n; j++){
                        //std::cout << Get(i, j) << " + " << other.Get(i, j);
                        rtn.Set(i, j, Get(i, j) + other.Get(i, j));
                        //std::cout << " = " << rtn.Get(i, j) << "\n";
                    }
                }
                rtn.Debug();
                //std::cout << &(rtn.array) << "\n";
                return rtn;
            }else{
                throw -1;
            }
        }

        fullMatrix operator-(fullMatrix other){
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

        fullMatrix operator*(fullMatrix other){
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
            bool a_inc = false;

            for(int i = 0; i < this->m; i++){
                for(int j = 0; j < this->n; j++){
                    if(!(x == i | y == j)){
                        minor.Set(a, b, this->Get(i, j));
                        b++;
                        a_inc = true;
                    }
                }
                if(a_inc){
                    a++;
                    a_inc = false;
                    b = 0;
                }
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
                            det -= this->Get(i, 0) * this->Minor(i, 0).Det();
                        }
                    }
                    return det;
                }
            }else{
                std::cout << "Matrix not square\n";
                return -1;
            }
        }

        fullMatrix MatOfMinors(){
            fullMatrix rtn(this->m, this->n);
            if(this->m == this->n){
                for(int i = 0; i < this->m; i++){
                    for(int j = 0; j < this->n; j++){
                        rtn.Set(i, j, this->Minor(i, j).Det());
                    }
                }
            }else{
                std::cout << "Matrix not square\n";
            }
            return rtn;
        }

        fullMatrix Cofactors(){
            fullMatrix rtn(this->m, this->n);
            if(this->m == this->n){
                fullMatrix minors = this->MatOfMinors();
                for(int i = 0; i < this->m; i++){
                    for(int j = 0; j < this->n; j++){
                        if((i * this->n + j) % 2 == 1){
                            rtn.Set(i, j, -minors.Get(j, i));
                        }else{
                            rtn.Set(i , j, minors.Get(j, i));
                        }
                    }
                }
            }else{
                std::cout << "Matrix not square\n";
            }
            return rtn;
        }

        fullMatrix Transpose(){
            fullMatrix rtn(this->Cofactors());
            if(this->n==this->m){
                //need to split down into recursive steps for 2.2 matrix transpose

                //1) Calculate determinant
                //2) Move and invert signs of elements
                //3) Multiply
                rtn = rtn * (1/this->Det());
            }else{
                std::cout << "Matrix not square\n";
            }
            return rtn;
        }

        float Magnitude(){
            return std::sqrt(std::pow(w(),2) + std::pow(x(),2) + std::pow(y(),2) + std::pow(z(),2));
        }

        fullMatrix Conjugate(){
            if((m == 4 && n == 1) || (m == 1 && n == 4)){
                fullMatrix rtn(*this);
                rtn = rtn * -1;
                rtn.Set(0, 0, rtn.w());
                return rtn;
            }else{
                std::cout << "Not a quaternion\n";
                throw -1;
            }
        }

        fullMatrix Inverse(){
            if((m == 4 && n == 1) || (m == 1 && n == 4)){
                fullMatrix rtn(Conjugate());
                rtn = rtn / rtn.Magnitude();
                return rtn;
            }else{
                std::cout << "Not a quaternion\n";
                throw -1;
            }
        }

        /*fullMatrix Update(fullMatrix update){

        }*/

        static void Test(){
            std::cout << "Testing fullMatrix\n";
            fullMatrix a = fullMatrix(MatrixType::Vector, 1, 2, 3);
            fullMatrix b = fullMatrix(MatrixType::Vector, 4, 5, 6);

            std::cout << "Vector get\n";
            assert(a.x() == 1);
            assert(a.y() == 2);
            assert(a.z() == 3);
            std::cout << "Vector get: checked\n";

            std::cout << "Vector add\n";
            b.Debug();
            fullMatrix c = a + b;
            std::cout << "Data from the returned array(" << &(c.array) << "): " << (c.array)[0] << ", " << (c.array)[1] << ", " << (c.array)[2] << "\n";
            std::cout << &(c.array) << "\n";
            c.Debug();
            assert(c.x() == 5);
            assert(c.y() == 7);
            assert(c.z() == 9);
            std::cout << "Testing complete\n";

            //assert(1 == 2);
        }
};