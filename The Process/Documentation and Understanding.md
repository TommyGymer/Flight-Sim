## Documentation and Understanding
Documentation will be produced using [Obsidian](https://obsidian.md/)


---
### Raylib
---
#### Making a window

```#include "raylib.h"``` is required to make use of the raylib library

A standard C `int main(void){}` is defined as the program entry point

An OpenGL window can now be initialised using the raylib interface with

```InitWindow(screenWidth, screenHeight, "Window name");```

with screenWidth/Height as int's

```SetWindowState(FLAG_WINDOW_RESIZEABLE)``` for a resizable window

![[First window.png]]

---
#### C++ rather than C

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

[[Quaternions]]

Raylib contains some helpers for working with quaternions, such as a quaternion to axis-angle conversion, but will require the implementing of some way to integrate a quaternion velocity and possible quaternion acceleration

![[Quaternions complete.png]]

![[Rotation demo.mp4]]

Now able to rotate an object using an Euler 3D vector for angular velocity

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