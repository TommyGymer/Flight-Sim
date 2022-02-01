## Design
---
![[System overview.png]]

---
### Menus

#### Main Menu

![[Main Menu.png]]

- "Start Sim" button to open the location and plane select menu
- "Settings" button to open the settings menu
- "Exit" button to exit the application
- Use a render of the previous or default location as the background

#### Start Sim

![[Start Sim.png]]

- Show most commonly used in order
- Select a location and plane
- Add level from .obj
- Add plane from custom format
- Same background as main, possibly with blur or reduced alpha

#### Settings

![[Settings.png]]

By reducing and fully categorising all available options 

- Graphics
	- Texture quality
	- Model quality
- Audio
	- Audio device
	- Volume
- Controls
	- Input devices
	- Sensitivity
	- Channels
- Language?

#### 3D Simulator

- After selecting an aircraft and location, the simulator will be loaded
- This will be a rearrangement of the 3D scene used in the background of the menus
	- This will remove the need to either hide, or load, extra assets for the sim
	- This should help reduce load times into the sim once the application has been started

---
### Objects

#### Structure
- Movement
	- Vector3D: position
	- Vector3D: velocity
	- Vector3D: acceleration
- Rotation
	- Vector4D: rotation
	- Vector3D: angular velocity
- Size
	- Vector3D: scale
- Model
	- raylib::Model: model
		- Contains the mesh and other object data
		- Such as animations
		- And bones

#### Functions

- Initialiser
	- Take a string from which to load the object data into the model attribute
- Draw
	- Use the attributes to draw the object to the world
- Update
	- Use numerical integration on the movement attributes

#### Other

To make full use of the axis-angle rotation, quaternions will be required
This will allow full use of angular velocity and accelerations

While raylib already implements many of these, it may be beneficial to write my own vector and matrix lib to allow full use of all required overloads

---
### Algorithms

#### Vector and Matrix Maths Lib

```

```