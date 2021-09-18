## Opening a Window
---
Using glfw:
1. Initialise glfw and confirm initialisation
```C++
if( !glfwInit() )
{
	fprintf( stderr, "Failed to initialize GLFW\n" );
	getchar();
	return -1;
}
```
3. Apply window hints `glfwWindowHint({hint}, {value})`
	1. `GLFW_SAMPLES`: `4`
	2. `GLFW_CONTEXT_VERSION_MAJOR`:`3`/`4`
	3. `GLFW_CONTEXT_VERSION_MINOR`:`3`/`2`
	4. `GLFW_OPENGL_FORWARD_COMPAT`:`GL_TRUE`
	5. `GLFW_OPENGL_PROFILE`:`GLFW_OPENGL_CORE_PROFILE`
4. Create the window and confirm creation
	- Width
	- Height
	- Title
	- Screen if fullscreen
	- Window if this is a child window
```C++
if( window == NULL){
	fprintf( stderr, "Failed to open GLFW window.\n" );
	getchar();
	glfwTerminate();
	return -1;
}
```
5. Bind the window to the current thread
```C++
glfwMakeContextCurrent(window);
```
7. Initialise glew and confirm initialisation
```C++
if (glewInit() ¬= GLEW_OK){
	fprintf(stderr, "Failted to initialise GLEW.\n");
	getchar();
	glfwTerminate();
	return -1;
}
```
9. Set the glfw input modes for the window
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
```C++
glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

glfwPollEvents();
glfwSetCursorPos(window, 1024/2, 768/2);
```
10. Set the window to a known blank state
```C++
glClearColor(0.8f, 0.8f, 1.0f, 0.0f); //RGBA
```
12. Enter the draw loop until exit or close event
	1. Clear the draw buffer `glClear(GL_COLOR_BUFFER_BIT)`
	2. Drawing and shaders
	3. Swap the display and draw buffers
	4. Poll for events
```C++
do{
	glClear( GL_COLOR_BUFFER_BIT );
	
	glfwSwapBuffers(window);
	glfwPollEvents();
}while( glfwGetKey(window, GLFW__KEY_ESCAPE) != GLFW_PRESS &&
	glfwWindowShouldCLose(window) == 0);
```
13. Terminate glfw
```C++
glfwTerminate();

return 0;
```