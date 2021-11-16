## Shaders
---
[GLSL Tutorial](https://learnopengl.com/Getting-started/Shaders)
[OpenGL Shader documentation](https://www.khronos.org/opengl/wiki/OpenGL_Shading_Language)

### Fragment Shaders
---
Fragment shaders handle the shading of material in between vertices by either interpolating the vertex colours, or using a UV map

This is where ambient, diffuse and specular lighting and reflections are calculated

### Vertex Shaders
---
Vertex shaders handle the rendering of vertices and their location within a UV map

They take the location of each vertex within object space and convert this to world space using the camera position and orientation

They also handle light location and normals for standard shading

