## Research and Initial Development
---
#### First rendering
Due to my lack of previous experience with both OpenGL and C# for graphical rendering, I intend to first produce a simple application to learn how OpenGL can be used with imported .obj files and render them.

Once I have a better understanding of the architecture, I should be able to construct the application without the need for copying code directly.

I will be following an [OpenGL in C++](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/) tutorial to develop my first application in C++ and OpenGL. This covers the basics of C++ and OpenGL to be able render an object using shaders.

![[First cube.png]]

#### Loading from a .obj
[Tutorial](https://ogldev.org/www/tutorial22/tutorial22.html)

![[Cube points.png]]

A .obj stores the points within the mesh of an object. These can be extracted form the file using Assimp and then loaded into the mesh array for the renderer.