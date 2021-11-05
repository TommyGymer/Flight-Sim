## Project Proposal
---
#### Title: RC-PC

#### Language: C++
---
### Overview:
---
- Use of OpenGL for 3D rendering
- Inputs from joystick type controllers
- Definition of file formats to store aircraft .aircraft (.zip file)
	- Contains the .obj
	- Contains UV and texture data
	- Contains a self defined .bfp (.xml file) to store pre-baked flight profile arguments
- A method of editing the files

### Potential to add complexity
---
- Shaders
- Performance
- Calculate flight characteristics based on the 3D model file for use with the physics engine
- Editor for the new file types
- Support for the use of a VR headset using OpenVR

### Suitability
---
- 3D rendering and physics engine for flight should provide complexity
- Definition of file formats, reading and writing will add file handling
- Physics engine for the flight aspects will add physics beyond the rigid body engine built into one of the libraries I will use
- Interaction with different input devices will add the need for a number of configuration menus

### Success criteria
---
- Aircraft is simulated using predifined/prebaked characteristics from a file
- Aircraft is controlled using an input device besides a keyboard and mouse
- Aircraft is rendered in full colour from a .obj and related texture files
- Flight control surfaces can be moved and are animated beyond the simulation
- Users can follow documentation and be able to create their own .aircraft files using a .obj from Blender

### Documentation
- Use of GitHub for versioning
- Use Obsidian note taking software for documentation