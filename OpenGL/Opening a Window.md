## Opening a Window
---
Using glfw:
1. Initialise glfw and confirm initialisation `if(!glfwInit())`
2. Apply window hints `glfwWindowHint({hint}, {value})`
	1. `GLFW_SAMPLES`: `4`
	2. `GLFW_CONTEXT_VERSION_MAJOR`:`3`/`4`
	3. `GLFW_CONTEXT_VERSION_MINOR`:`3`/`2`
	4. `GLFW_OPENGL_FORWARD_COMPAT`:`GL_TRUE`
	5. `GLFW_OPENGL_PROFILE`:`GLFW_OPENGL_CORE_PROFILE`
3. Create the window and confirm creation
	- Width
	- Height
	- Title
	- Screen if fullscreen
	- Window if this is a child window
4. Bind the window to the current thread
5. Initialise glew and confirm initialisation
6. Set the glfw input modes for the window
	- `GLFW_CURSOR` for the cursor modes
		- `GLFW_CURSOR_NORMAL`
		- `GLFW_CURSOR_HIDDEN`
		- `GLFW_CURSOR_DISABLED`
	- `GLFW_STICKY_KEYS`
		- `GL_FALSE`: returns `GLFW_PRESS` or `GLFW_RELEASE` once per action
		- `GL_TRUE`: returns `GLFW_PRESS` or `GLFW_RELEASE` while true
	- `GLFW_STICKY_MOUSE_BUTTONS`
		- `GL_FALSE`: returns `GLFW_PRESS` or `GLFW_RELEASE` once per action
		- `GL_TRUE`: returns `GLFW_PRESS` or `GLFW_RELEASE` while true
7. Set the window to a known blank state
8. Enter the draw loop until exit or close event
	1. Clear the draw buffer `glClear(GL_COLOR_BUFFER_BIT)`
	2. Drawing and shaders
	3. Swap the display and draw buffers
	4. Poll for events
9. Terminate glfw