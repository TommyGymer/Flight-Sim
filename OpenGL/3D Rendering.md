## 3D Rendering
###### to be read using [Obsidian](https://obsidian.md/)
---
### Renderer

^9816ff

Using C++ and OpenGL for the heavy lifting will reduce the need to focus on the required parts of any 3D software

The camera will always be looking at the aircraft, so keyboard inputs for movement shouldn't be required

Although this might add another dimension to the experience if the user can  move their perspective around the map

### Object files

^8b37fe

Using OpenGL should allow the importing and displaying of .obj files with a bone structure for the active flight surfaces

### [[Flight Characteristics#^baking|Baked Flight Profiles]]

^9bc8fb

The same .obj should be used for calculation of flight characteristic baking; the results of baking will need to be stored in some kind of file format, probably an xml or JSON file

### Resources

^2d534d

---
[OpenGL Tutorial](http://www.opengl-tutorial.org/intermediate-tutorials/billboards-particles/particles-instancing/)
[OpenGL Bones](https://learnopengl.com/Guest-Articles/2020/Skeletal-Animation)
[GLSL Shaders](https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_on_the_web/GLSL_Shaders)