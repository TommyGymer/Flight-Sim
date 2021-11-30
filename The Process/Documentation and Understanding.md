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
#### Setting up 3D rendering

```Camera3D camera = {0};
camera.position = (Vector3){10.0f, 10.0f, 10.0f};
camera.target = (Vector3){0.0f, 0.0f, 0.0f};
camera.up = (Vector3){0.0f, 1.0f, 0.0f};
camera.fovy = 45.0f;
camera.type = CAMERA_PERSPECTIVE;
```

---
#### Shaders

![[Shaders.png]]