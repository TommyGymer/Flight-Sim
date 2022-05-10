
## Developing a Coded Solution

---

### Setting up development environment

```#include "raylib.h"``` is required to make use of the raylib library

A standard C `int main(void){}` is defined as the program entry point

An OpenGL window can now be initialised using the raylib interface with

```InitWindow(screenWidth, screenHeight, "Window name");```

with screenWidth/Height as int's

```SetWindowState(FLAG_WINDOW_RESIZEABLE)``` for a resizable window

![](Images/First_window.png)

---

#### Setting up [VSCodium](https://vscodium.com/) to facilitate development

![](Images/Shapes.png)

Added a shortcut to build and run the active file to allow for easier and quicker testing.

Above shows one of the RayLib examples I have used to test that the shortcut functions as expected.

---

#### First rendering
Due to my lack of previous experience with both OpenGL and C# for graphical rendering, I intend to first produce a simple application to learn how OpenGL can be used with imported .obj files and render them.

Once I have a better understanding of the architecture, I should be able to construct the application without the need for copying code directly.

I will be following an [OpenGL in C++](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/) tutorial to develop my first application in C++ and OpenGL. This covers the basics of C++ and OpenGL to be able render an object using shaders.

![](Images/First_cube.png)

---

#### Loading from a .obj file

[Tutorial](https://ogldev.org/www/tutorial22/tutorial22.html)

![](Images/Cube_points.png)

A .obj stores the points within the mesh of an object. These can be extracted form the file using Assimp and then loaded into the mesh array for the renderer.


---

### C++ rather than C

Using a port of raylib to c++ will provide access to the OOP features that will help to formalise the structure of the program

As I will still be using raylib and the change is only from C to C++, much of the code remains the same

---

#### Setting up C++

Starting with simply opening a window using C++ rather than C

![](Images/First_C++_window_code.png)

The above shows a demo I found which simply opens a windows and displays some text on it

![](Images/First_C++_window.png)

Allowing window resizing
![](Images/Window_resizing.png)

---

#### Setting up 3D rendering

![](Images/First_render_code.png)

Not currently rendering anything
![](Images/First_render.png)

---

### Example shaders

![](Images/Shaders.png)

Testing one of the example shaders with an object made in Blender

---

### Shaders

[GLSL Tutorial](https://learnopengl.com/Getting-started/Shaders)
[OpenGL Shader documentation](https://www.khronos.org/opengl/wiki/OpenGL_Shading_Language)

#### Fragment Shaders

Fragment shaders handle the shading of material in between vertices by either interpolating the vertex colours, or using a UV map

This is where ambient, diffuse and specular lighting and reflections are calculated

#### Vertex Shaders

Vertex shaders handle the rendering of vertices and their location within a UV map

They take the location of each vertex within object space and convert this to world space using the camera position and orientation

They also handle light location and normals for standard shading

---

### Object loading

Raylib contains helper methods for parsing .obj files and allows the easy import of a .obj and its related material files

![](Images/Cube_loading_code.png)

![](Images/Loading_a_cube.png)

---

### Shaders

Shaders must then be set for each material to allow the renderer to know what to draw to the screen
![](Images/Material shaders.png)
The object can then be drawn during the loop
![](Images/first_draw_object.png)
A grid can also be rendered to show y=0
![](Images/Cube_rendered_with_grid.png)
![](Images/Render_grid.png)

---

### Updating location during runtime
![](Images/Moving_object_at_runtime.mp4)
![](Images/Start_time.png)
![](Images/Total_time.png)
By re-coding the start time of the program, the total run time can be determined
This can then be used as a parameter of some function to determine location

---

### Object tracking

![](Images/Tracking_and_parametrics.mp4)
A more complex movement can be traced by changing all three x, y and z components of the object's location
![](Images/parametric_location.png)
The object can then be tracked by pointing the camera at this location
![](Images/Camera_targeting.png)

---

### Gravity

![](Images/SUVAT_gravity.mp4)
Gravity can then be implemented using a SUVAT and the total elapsed time
![](Images/SUVAT_gravity_implementation.png)

---

### Moving the model data to an object

![](Images/OOP_demo.mp4)

Now making use of an object class and instancing to keep track of objects and render them
This will help keep the code clean, as it removes the need to hard code each object required

![](Images/First_object_class.png)

Object definition

|Variable name|Type|Usage|
|:---|:---|:---|
|model|raylib::model*|mesh and material data for the object|
|pos|raylib::Vector3|location of the object in 3D space|
|vel|raylib::Vector3|velocity of the object in 3D space|
|rot|raylib::Vector3|axis around which to rotate|
|angle|float|the angle to rotate around the above axis|
|scale|raylib::Vector3|scale factor of the model|

This initial design simply holds the data required for rendering the object

It would be better to implement a number of the required function which are currently within the main function into this class as any object that needs rendering would require them
Many of these attributes would also have standard values, which would be useful not to need to initialize for every object

---

### Numerical integration

Rather than using a predefined SUVAT for movement, integrating an acceleration for velocity and then integrating velocity for position allows the changing of both acceleration and velocity during runtime

This can be easily achieved by tracking the previous frame time and subtracting this from the current time to find the change in time between the two frames
This will make any physics based off this time entirely frame independent

![](Images/Finding_dt.png)

The first version of this missed setting start to the current time at the end of dt, resulting in dt being found as the total time since the program started

![](Images/First_pos_based_on_integration.mp4)

---

### Moving per object functions to the Object class

![](Images/Public_draw_function.png)

Moving the draw function to within the class allows the use of the local object variables without the need to first extract the required data for drawing from the object

This also allows for the code within the main loop to be kept simpler as each object only requires a single function call to draw

---

#### Per Object physics

![](Images/First_update_function.png)

By moving the physics updating to a function, the code in the main loop can be further simplified to only require an update call and a draw call per object

This new implementation also features a collision detection with y=0 to allow the cube to stop falling at this plane

![](Images/Cube_collide_with_y0.mp4)

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

![](Images/Quaternion.png)
The above is the rotation quaternion within the object class

By modifying the draw function, the new quaternion representation of the rotation can be used

![](images/Quat_draw.png)

![](Images/Quaternions_complete.png)

![](Images/Rotation_demo.mp4)

Now able to rotate an object using an Euler 3D vector for angular velocity

![](Images/Angular_vel.png)

Along with an integrator from the update angular velocity to the rotation quaternion

![](Images/Quat_integration.png)

---

### Adding simple movement input

![](Images/Movement.mp4)

![](Images/Keyboard_input.png)

By damping the x-y velocity, an effect similar to friction can be achieved
The velocity is set to a particular amount in a particular direction when one of the "wasd" keys is pressed
As the velocity is already being integrated for position, the implantation of this user input is trivial

---

### First person

By moving the camera to the player object's location and rotation, first person gameplay is achieved
As both the object location and rotation are already available from the object, they can simply be set as the camera location and rotation

![](Images/Set_camera_pos.png)

As the camera is set to the object's location, the target can no longer be the object itself
This will need to be a unit vector rotated by the quaternion to be in front of the camera

![](Images/First_first_person.mp4)

For debugging purposes, the camera target is set to another object's location with is placed at the origin

---

#### Rotating the velocity with the quaternion

![](Images/Vel_rot_by_quat.mp4)

By rotating the velocity be the quaternion, the look direction of the camera can be kept consistent with the direction of movement caused by the keyboard input

![](Images/Set_quat_with_camera.png)

In this case, for debugging, the object quaternion is set using the camera's quaternion as this can be easily updated using the `SetTarget` function

---

### Making a matrix class

The matrix class begins with a simple double array and two integers to define the width and height of the matrix

![](Images/Start_of_matrix_class.png)

This will be the base data structure used to store all data about the matrix

A get and set function are required to translate an x,y position in the matrix into the required index in the double array

![](Images/Get_matrix.png)

![](Images/Set_matrix.png)

If the position is outside of the matrix, the function will throw an error after printing an out-of-bounds message

With these two functions, all matrix operations can be derived

![](Images/Matrix_sum.png)

Until all functions shown in the algorithms section of Design are complete and tested

The raylib::Vector4 quaternion class currently in use appears to have some problems with my current aim which is to rotate the camera using the mouse for debugging rotation, movement and rendering

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

---

### Look vector camera movement

![](Images/Look_vector.png)

A look vector is defined in the object class and is updated in the update function

![](Images/Update_look_vector.png)

The camera can then target its position plus this look vector

![](Images/Camera_look_vector.png)

Bellow is a demo of this

![](Images/Look_vector_demo.mp4)

The camera is rotated with a and d with forward and backward motion on w and s

![](Images/Rotation_input.png)

---

### Mouse input

First the mouse must be setup by hiding it

![](Images/Mouse_setup.png)

The change in mouse location is then calculated and a sensitivity factor is used
The mouse is then moved back to the center to allow the next mouse change to be calculated

![](Images/Find_change_in_mouse_location.png)

A pause button to allow moving the mouse away from the program 

![](Images/Pausing.png)

A pause toggle button is added to p

![](Images/Pause_button_on_p.png)

---

### Camera up vector

Currently, the object drifts as the velocity and acceleration are not being correctly rotated

Adding the camera up vector will allow easier debugging of this by displaying the problem

![](Images/Up_vector_def.png)

The up vector is defined within the object class

![](Images/Updating_the_up_vector.png)

The up vector is updated within the update function

![](Images/Setting_camera_up_vector.png)

The camera up vector is then set to the object's up vector

![](Images/Demo_of_the_tilt.mp4)

---

### Splitting classes into files

![](Images/Split_files.png)

Splitting the classes into separate files will clean up the main file and make it easier to keep the code organized

---

### Replacing boolean game state with an enum

This will allow easier reading as well as easy addition of new game states, such as main menu or other specific menu area

![](Images/Game_state_enum.png)

---

### Transferring physics to the matrix class

Most of the code remains the same beside the class names used at initialization

![](Images/Object_with_matrix_class.png)

Now using an explicit definition of the update quaternion

![](Images/Updating_the_quaternion.png)

This also checks for a 0 length angular velocity which would result in a divide by zero error when normalizing if left

The formula for the update quaternion is from [this lecture from Stanford University](https://stanford.edu/class/ee267/lectures/lecture10.pdf)

---

### Correcting use of global and local space

![](Images/New_object_with_matrix_class.png)

Added new global versions of acceleration and velocity to remove the reliance on the rotation quaternion and to reduce the time complexity

![](Images/Split_global_and_local_angv.png)

Splitting of the angular velocity into global and local movements allows the rotation required for use with a mouse

This solution also ensures that any combination of global and local rotation transformations can be easily tested and achieved

When used with a controller, most of the inputs will need to be local and the control surfaces of an aircraft act on along the axis of the plane

---

### Shaders

![](Images/Colouring_of_surface.png)

By using the dot product of the normal of the surface and a direction from which to project light, the surface can be coloured with an effect similar to shadows within a single convex shape

![](Images/Normal_based_shadow_shader.png)

Scaling a shade of green with the dot product of the vertex and an arbitrary direction for the light source

---

### Shaders finished

![](Images/Final_shaders.png)

The shaders now simulate shadows relatively well with the runway correctly colourised

![](Images/Final_shaders_runway.png)

---

### Debugging an array deletion

![](Images/Delete_crash_debug_log.png)

The above debug log shows the use of the debug function in debugging an array deletion error in which an array used by an instance of the fullMatrix class is deleted more than once, resulting in an uncatchable crash

Problem found to be the result of using `rtn = rtn * dA` where `rtn` is the fullMatrix matrix containing the inverse matrix to be returned and `dA` is the inverse of the determinant of the matrix.
This version appeared to result in the deletion of one of the required arrays while the version used while testing the `fullMatrix * double` function performed as expected.
By changing over to using the version from the scale test, `fullMatrix rtn(cofacts * dA)`, the inverse matrix function now performs as expected.

---

### Overloading the assignment operator

![](Images/Assignment_operator_overloaded.png)

Explicitly defining the assignment (=) operator appears to have fixed many of the issues that randomly appeared while trying to debug the random crashes from the matrix testing