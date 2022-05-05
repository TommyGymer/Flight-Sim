#include <iostream>
#include <math.h>
#include <raylib-cpp.hpp>
#include <assert.h>
#include <algorithm>
#include <iterator>

enum class MatrixType {Vector, Coord, Matrix};

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
                std::cout << "Not a quaternion\n";
                throw -1;
            }
        }

        void const w(double val){
            if((m == 4 && n ==1) || (m == 1 && n ==4)){
                array[0] = val;
            }else{
                std::cout << "Not a quaternion\n";
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

        void const x(double val){
            if((m == 3 && n == 1) || (m == 1 && n == 3)){
                array[0] = val;
            }else if((m == 4 && n ==1) || (m == 1 && n ==4)){
                array[1] = val;
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

        void const y(double val){
            if((m == 3 && n == 1) || (m == 1 && n == 3)){
                array[1] = val;
            }else if((m == 4 && n ==1) || (m == 1 && n ==4)){
                array[2] = val;
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

        void const z(double val){
            if((m == 3 && n == 1) || (m == 1 && n == 3)){
                array[2] = val;
            }else if((m == 4 && n ==1) || (m == 1 && n ==4)){
                array[3] = val;
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
                    this->Set(i, i, 0);
                }
            }
        }

        fullMatrix(raylib::Matrix mat){
            m = 4;
            n = 4;
            array = new double[m * n];

            array[0] = mat.m0;
            array[1] = mat.m1;
            array[2] = mat.m2;
            array[3] = mat.m3;

            array[4] = mat.m4;
            array[5] = mat.m5;
            array[6] = mat.m6;
            array[7] = mat.m7;

            array[8] = mat.m8;
            array[9] = mat.m9;
            array[10] = mat.m10;
            array[11] = mat.m11;

            array[12] = mat.m12;
            array[13] = mat.m13;
            array[14] = mat.m14;
            array[15] = mat.m15;
        }

        raylib::Matrix GetMatrix(){
            return raylib::Matrix(
                array[0],
                array[1],
                array[2],
                array[3],

                array[4],
                array[5],
                array[6],
                array[7],

                array[8],
                array[9],
                array[10],
                array[11],

                array[12],
                array[13],
                array[14],
                array[15]
            );
        }

        //copy constructor
        fullMatrix(const fullMatrix& other){
            m = other.m;
            n = other.n;
            array = new double[m * n];
            std::copy(other.array, other.array + (n * m), array);
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
        }

        fullMatrix(MatrixType type, const double w, const double x, const double y, const double z){
            int _m = 0;
            int _n = 0;
            if(type == MatrixType::Vector){
                _m = 4;
                _n = 1;
            }else if(type == MatrixType::Coord){
                _m = 1;
                _n = 4;
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
            try{
                delete[] array;
            }catch(...){
                std::cout << "unable to delete this array\n";
            }
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

        double Dot(fullMatrix other){
            if(n==1){
                double total = 0;
                for(int i = 0; i < m; i++){
                    total += array[i] * other.array[i];
                }
                return total;
            }else{
                std::cout << "Not a vector\n";
                throw -1;
            }
        }

        fullMatrix operator+(fullMatrix other){
            if(m == other.m && n == other.n){
                fullMatrix rtn(m, n);
                for(int i = 0; i < m; i++){
                    for(int j = 0; j < n; j++){
                        rtn.Set(i, j, Get(i, j) + other.Get(i, j));
                    }
                }
                return rtn;
            }else{
                std::cout << "Dimention error\n";
                Debug();
                other.Debug();
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
                std::cout << "Dimention error\n";
                throw -1;
            }
        }

        fullMatrix operator*(fullMatrix other){
            //quaternion multiplication
            if((this->n == 1 && this->m == 4) && (other.n==1 && other.m == 4)){
                fullMatrix rtn(this->m, this->n);

                rtn.w(w() * other.w() - x() * other.x() - y() * other.y() - z() * other.z());
                rtn.x(w() * other.x() + x() * other.w() + y() * other.z() - z() * other.y());
                rtn.y(w() * other.y() - x() * other.z() + y() * other.w() + z() * other.x());
                rtn.z(w() * other.z() + x() * other.y() - y() * other.x() + z() * other.w());

                return rtn;
            }
            //generic matrix multiplication
            else if(this->n == other.m){
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
                throw -1;
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
                rtn.w(-rtn.w());
                return rtn;
            }else{
                std::cout << "Not a quaternion\n";
                throw -1;
            }
        }

        fullMatrix Inverse(){
            if((m == 4 && n == 1) || (m == 1 && n == 4)){
                fullMatrix rtn(Conjugate());
                rtn = rtn / pow(rtn.Length(), 2);
                return rtn;
            }else{
                std::cout << "Not a quaternion\n";
                throw -1;
            }
        }

        fullMatrix RotateByQuaternion(fullMatrix quat){
            if(m == 3 && n ==1){
                fullMatrix p(MatrixType::Vector, 0, x(), y(), z());

                fullMatrix i(quat.Conjugate());

                fullMatrix res((quat * p) * i);

                fullMatrix rtn(MatrixType::Vector, res.x(), res.y(), res.z());

                return rtn;
            }else{
                std::cout << "Not a vector\n";
                throw -1;
            }
        }

        fullMatrix DeRotateByQuaternion(fullMatrix quat){
            if(m == 3 && n ==1){
                fullMatrix p(MatrixType::Vector, 0, x(), y(), z());

                fullMatrix i(quat.Conjugate());

                fullMatrix res((i * p) * quat);

                fullMatrix rtn(MatrixType::Vector, res.x(), res.y(), res.z());

                return rtn;
            }else{
                std::cout << "Not a vector\n";
                throw -1;
            }
        }

        double Length(){
            double sqrSum = 0;
            for(int i = 0; i < m*n; i++){
                sqrSum += pow(array[i], 2);
            }
            return sqrt(sqrSum);
        }

        fullMatrix Normalize(){
            double l = Length();
            fullMatrix rtn(*this);
            return (rtn / l);
        }

        fullMatrix ToAxisAngle(){
            if(m == 4 && n ==1){
                fullMatrix rtn(MatrixType::Vector, 0, 0, 0, 0);
                rtn.w(2 * acos(w()));
                rtn.x(x() / sqrt(1-w()*w()));
                rtn.y(y() / sqrt(1-w()*w()));
                rtn.z(z() / sqrt(1-w()*w()));
                return rtn;
            }else{
                std::cout << "Not a quaternion\n";
                throw -1;
            }
        }

        fullMatrix GetComplex(){
            if(m == 4 && n ==1){
                return fullMatrix(MatrixType::Vector, x(), y(), z());
            }else{
                std::cout << "Not a quaternion\n";
                throw -1;
            }
        }

        /*fullMatrix Update(fullMatrix update){

        }*/

        static void Test(bool output){
            if(output)std::cout << "\n\n┏Testing fullMatrix\n";
            {
                fullMatrix a = fullMatrix(MatrixType::Vector, 7, 8, 9);
                fullMatrix b = fullMatrix(MatrixType::Vector, 4, 5, 6);

                if(output)std::cout << "┣━Vector get\n";
                {
                    assert(a.x() == 7);
                    assert(a.y() == 8);
                    assert(a.z() == 9);
                }
                if(output)std::cout << "┣━Vector get: checked\n";

                if(output)std::cout << "┣━Vector set\n";
                {
                    a.x(1);
                    a.y(2);
                    a.z(3);

                    assert(a.x() == 1);
                    assert(a.y() == 2);
                    assert(a.z() == 3);
                }
                if(output)std::cout << "┣━Vector set: checked\n";

                if(output)std::cout << "┣━Vector add\n";
                {
                    fullMatrix c = a + b;
                    assert(c.x() == 5);
                    assert(c.y() == 7);
                    assert(c.z() == 9);
                }
                if(output)std::cout << "┣━Vector add: checked\n";

                if(output)std::cout << "┣━Vector subtract\n";
                {
                    fullMatrix c = b - a;
                    assert(c.x() == 3);
                    assert(c.y() == 3);
                    assert(c.z() == 3);
                }
                if(output)std::cout << "┣━Vector subtract: checked\n";

                fullMatrix quatA(MatrixType::Vector, 9, 10, 11, 12);
                fullMatrix quatB(MatrixType::Vector, 5, 6, 7, 8);

                if(output)std::cout << "┣━Quaternion get\n";
                {
                    assert(quatA.w() == 9);
                    assert(quatA.x() == 10);
                    assert(quatA.y() == 11);
                    assert(quatA.z() == 12);
                }
                if(output)std::cout << "┣━Quaternion get: checked\n";

                if(output)std::cout << "┣━Quaternion set\n";
                {
                    quatA.w(1);
                    quatA.x(2);
                    quatA.y(3);
                    quatA.z(4);

                    assert(quatA.w() == 1);
                    assert(quatA.x() == 2);
                    assert(quatA.y() == 3);
                    assert(quatA.z() == 4);
                }
                if(output)std::cout << "┣━Quaternion set: checked\n";

                if(output)std::cout << "┣━Matrix multiply\n";
                {
                    fullMatrix matA(3, 3);
                    fullMatrix matB(3, 3);

                    double valuesA[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
                    double valuesB[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

                    std::copy(valuesA, valuesA + 9, matA.array);
                    std::copy(valuesB, valuesB + 9, matB.array);

                    fullMatrix matC(matA * matB);

                    for(int i = 0; i < 9; i++){
                        assert(matC.array[i] == valuesB[i]);
                    }
                }
                if(output)std::cout << "┣━Matrix multiply: checked\n";

                if(output)std::cout << "┣━Matrix scale\n";
                {
                    fullMatrix mat(3, 3);

                    double values[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                    double correct[9] = {2, 4, 6, 8, 10, 12, 14, 16, 18};

                    std::copy(values, values + 9, mat.array);

                    fullMatrix matS(mat * 2);

                    for(int i = 0; i < 9; i++){
                        assert(matS.array[i] == correct[i]);
                    }
                }
                if(output)std::cout << "┣━Matrix scale: checked\n";

                if(output)std::cout << "┣━Matrix transpose\n";
                {
                    fullMatrix mat(3, 3);

                    if(output)std::cout << "┣━━Testing identity mat\n";
                    {
                        double values[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
                        std::copy(values, values + 9, mat.array);
                        
                        fullMatrix inv(mat.Transpose());
                        
                        for(int i = 0; i < 9; i++){
                            assert(mat.array[i] == values[i]);
                        }
                        if(output)std::cout << "┣━━━Testing identity mat: mat asserts finished\n";
                    }
                    if(output)std::cout << "┣━━Testing identity mat: checked\n";

                    if(output)std::cout << "┣━━Testing a matrix\n";
                    {
                        double values[9] = {-3, 0, -1, 0, 1, 0, 1, 0, 2};
                        std::copy(values, values + 9, mat.array);

                        fullMatrix inv(mat.Transpose());
                        double correct[9] = {-0.4, 0, -0.2, 0, 1, 0, 0.2, 0, 0.6};
                        for(int i = 0; i < 9; i++){
                            assert(abs(inv.array[i] - correct[i]) < 0.0001);
                        }
                    }
                    if(output)std::cout << "┣━━Testing a matrix: checked\n";
                }
                if(output)std::cout << "┣━Matrix transpose: checked\n";

                if(output)std::cout << "┣━Testing quaternion operations\n";
                {
                    if(output)std::cout << "┣━━Quaternion addition\n";
                    {
                        fullMatrix quatA(MatrixType::Vector, 1, 2, 3, 4);
                        fullMatrix quatB(MatrixType::Vector, 5, 6, 7, 8);

                        fullMatrix quatC(quatA + quatB);

                        assert(quatC.w() == 6);
                        assert(quatC.x() == 8);
                        assert(quatC.y() == 10);
                        assert(quatC.z() == 12);
                    }
                    if(output)std::cout << "┣━━Quaternion addition:checked\n";

                    if(output)std::cout << "┣━━Quaternion multiply\n";
                    {
                        fullMatrix quatA(MatrixType::Vector, 1, 2, 3, 4);
                        fullMatrix quatB(MatrixType::Vector, 5, 6, 7, 8);

                        fullMatrix result(quatA * quatB);

                        //-60,12,30,24
                        assert(result.w() == -60);
                        assert(result.x() == 12);
                        assert(result.y() == 30);
                        assert(result.z() == 24);
                    }
                    if(output)std::cout << "┣━━Quaternion multiply: checked\n";

                    if(output)std::cout << "┣━━Quaternion multiply negative\n";
                    {
                        fullMatrix quatA(MatrixType::Vector, 0, 1, 0, 0);
                        fullMatrix quatB(MatrixType::Vector, 0.707, 0.0,  0.707, 0.0);

                        fullMatrix result(quatB * quatA);

                        //0.0, 0.707, 0.0, -0.707
                        assert(result.w() == 0);
                        assert(result.x() == 0.707);
                        assert(result.y() == 0);
                        assert(result.z() == -0.707);
                    }
                    if(output)std::cout << "┣━━Quaternion multiply negative: checked\n";

                    if(output)std::cout << "┣━━Quaternion rotate\n";
                    {
                        fullMatrix p(MatrixType::Vector, 1, 0, 0);
                        fullMatrix quat(MatrixType::Vector, cos(PI/4), 0.0,  sin(PI/4), 0.0);
                        quat.Normalize();

                        fullMatrix np(p.RotateByQuaternion(quat));
                        
                        assert(np.x() == 0);
                        assert(np.y() == 0);
                        assert(abs(np.z() + 1) < 0.000001);
                    }
                    if(output)std::cout << "┣━━Quaternion rotate\n";

                    if(output)std::cout << "┣━━Quaternion rotate continuity\n";
                    {
                        fullMatrix p(MatrixType::Vector, 0, 10, 0);
                        fullMatrix quat(MatrixType::Vector, cos(PI/4), 0.0,  sin(PI/4), 0.0);
                        quat.Normalize();
                        
                        fullMatrix np(p.DeRotateByQuaternion(quat).RotateByQuaternion(quat));
                        
                        assert(abs(np.x() - 0) < 0.000001);
                        assert(abs(np.y() - 10) < 0.000001);
                        assert(abs(np.z() - 0) < 0.000001);
                    }
                    if(output)std::cout << "┣━━Quaternion rotate continuity: checked\n";
                }
                if(output)std::cout << "┣━Testing quaternion operations: checked\n";
            }
            if(output)std::cout << "┗Testing complete\n";
            std::cout << "\n\n";

            //assert(1 == 2);
        }
};