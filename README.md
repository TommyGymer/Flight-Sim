# Flight-Sim
---
 A CS project that will contain:
 - [[3D Rendering]](https://github.com/TommyGymer/Flight-Sim/blob/main/OpenGL/3D%20Rendering.md)
 - [[Baked Physics Format|File reading and writing]](https://github.com/TommyGymer/Flight-Sim/blob/main/Physics/Baked%20Physics/Baked%20Physics%20Format.md)
 - [[XInput|Controls from different input devices]](https://github.com/TommyGymer/Flight-Sim/blob/main/Input/XInput.md)
 
Written in C++ and compiled using CMake using OpenGL

Documentation written in MarkDown using the [Obsidian](https://obsidian.md/) note taker

## Project Outline
---

#### Title: RC-PC

#### Language: C++

### Overview

- Use of OpenGL for 3D rendering
- Inputs from joystick type controllers
- Definition of file formats to store aircraft .aircraft (.zip file)
    - Contains the .obj
    - Contains UV and texture data
    - Contains a self defined .bpf (.xml file) to store pre-baked flight profile arguments
- A method of editing the files

### Potential to add complexity
- Shaders
- Performance
- Calculate flight characteristics based on the 3D model file
- Editor for the new file types
- Support for the use of a VR headset using OpenVR

### Suitability
- 3D rendering and physics engine for flight should provide complexity
- Definition of file formats, reading and writing will add file handling
- Physics engine for the flight aspects will add physics beyond the rigid body engine built into one of the libraries I will use
- Interaction with different input devices will add the need for a number of configuration menus

### Success criteria
- Aircraft is simulated using predefined/pre-baked characteristics from a file
- Aircraft is controlled using an input device besides a keyboard and mouse
- Aircraft is rendered in full colour from a .obj and related texture files
- Flight control surfaces can be moved and are animated beyond the simulation
- Users can follow documentation and be able to create their own .aircraft files using a .obj from Blender

### Documentation
- Use of GitHub for versioning
- Use Obsidian note taking software for documentation
