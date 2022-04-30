## Developing a Coded Solution
---
### Setting up development environment

```#include "raylib.h"``` is required to make use of the raylib library

A standard C `int main(void){}` is defined as the program entry point

An OpenGL window can now be initialised using the raylib interface with

```InitWindow(screenWidth, screenHeight, "Window name");```

with screenWidth/Height as int's

```SetWindowState(FLAG_WINDOW_RESIZEABLE)``` for a resizable window

![[First window.png]]

---
#### Setting up [VSCodium](https://vscodium.com/) to facilitate development

![[Shapes.png]]

Added a shortcut to build and run the active file to allow for easier and quicker testing.

Above shows one of the RayLib examples I have used to test that the shortcut functions as expected.

---
#### First rendering
Due to my lack of previous experience with both OpenGL and C# for graphical rendering, I intend to first produce a simple application to learn how OpenGL can be used with imported .obj files and render them.

Once I have a better understanding of the architecture, I should be able to construct the application without the need for copying code directly.

I will be following an [OpenGL in C++](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/) tutorial to develop my first application in C++ and OpenGL. This covers the basics of C++ and OpenGL to be able render an object using shaders.

![[First cube.png]]

---
#### Loading from a .obj file
[Tutorial](https://ogldev.org/www/tutorial22/tutorial22.html)

![[Cube points.png]]

A .obj stores the points within the mesh of an object. These can be extracted form the file using Assimp and then loaded into the mesh array for the renderer.


---
### C++ rather than C

Using a port of raylib to c++ will provide access to the OOP features that will help to formalise the structure of the program

---
#### Setting up 3D rendering

```
Camera3D camera = {0};
camera.position = (Vector3){10.0f, 10.0f, 10.0f};
camera.target = (Vector3){0.0f, 0.0f, 0.0f};
camera.up = (Vector3){0.0f, 1.0f, 0.0f};
camera.fovy = 45.0f;
camera.type = CAMERA_PERSPECTIVE;
```

---
#### Shaders

![[Shaders.png]]

---
#### Object loading

Raylib contains helper methods for parsing .obj files and allows the easy import of a .obj and its related material files

```
raylib::Model plane("..\\obj\\materials.obj");
```

![[Imported cube.png]]

---
#### Object based rendering

![[OOP demo.mp4]]

Now making use of an object class and instancing to keep track of objects and render them

This will help keep the code clean, as it removes the need to hard code each object required

---
### Quaternions
---
To fully represent the required rotations for a plane in 3D, quaternions are required

A Quaternion is defined as a 4D vector

$$
\begin{pmatrix}
i \\
j \\
k \\
w \\
\end{pmatrix}
$$

Where i, j and k can be imagined as a 3D vector with w as a rotation around this 3D vector

Each of these can take a value between -1 and 1; that is, a quaternion is a 4D unit vector

As raylib  makes use of axis-angle, it is relatively simple to convert between quaternions and the format required by raylib

[source for below equations](https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToAngle/index.htm)

#### Quaternion to Axis-Angle

$$ \theta = 2 * \arccos(w) $$
$$ x = \frac{i}{\sqrt{1-w^2}} $$
$$ y = \frac{j}{\sqrt{1-w^2}} $$
$$ z = \frac{k}{\sqrt{1-w^2}} $$

#### Axis-Angle to Quaternion

$$ w = \cos{\frac{\theta}{2}} $$
$$ i = x\sin{\frac{\theta}{2}} $$
$$ j = y\sin{\frac{\theta}{2}} $$
$$ k = z\sin{\frac{\theta}{2}} $$

#### Multiplication

$$ w = w_1 w_2 - x_1 x_2 - y_1 y_2 - z_1 z_2 $$
$$ i = w_1 x_2 + x_1 w_2 + y_1 z_2 - z_1 y_2 $$
$$ j = w_1 y_2 - x_1 z_2 + y_1 w_2 + z_1 x_2 $$
$$ k = w_1 z_2 + x_1 y_2 - y_1 x_2 + z_1 w_2 $$
---

Raylib contains some helpers for working with quaternions, such as a quaternion to axis-angle conversion, but will require the implementing of some way to integrate a quaternion velocity and possible quaternion acceleration

![[Quaternions complete.png]]

![[Rotation demo.mp4]]

Now able to rotate an object using an Euler 3D vector for angular velocity

---
### Making a matrix class
---


---
### Pointers
---
#### Working with the copy object constructor
```
fullMatrix(const fullMatrix& other){
   m = other.m;
   n = other.n;
   array = new double[m * n];
   memcpy(&array, &(other.array), m*n);
   std::cout << m << ", " << n << "\n";
 }
```

When an object is passed into a function or returned from a function, the object is redecleared through the copy constructor

This caused a number of problems before I rewrote this function to correctly copy the attributes of the object. As the array was not being copied correctly, the data was lost seemingly without reason.

Making correct use of array copying gives:

```
fullMatrix(const fullMatrix& other){
   m = other.m;
   n = other.n;
   array = new double[m * n];
}
```

As this avoids the need to understand how many bytes each of the elements is using, along with the number and values of the bytes used to keep track of the array size used during delete[] array.

After these changes, the matrix class can now be used for vector addition.

Further unit tests need to be written before the use of the rest of the functions to ensure they are working correctly before attempting to implement anything complicated.

The matrix class' delete function, ``~fullMatrix``, simply calls delete[] on the object's array. This is probably not necessary as this should be the default behaviour.