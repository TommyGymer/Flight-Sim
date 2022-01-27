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

---
### Objects

#### Structure
- Movement
	- Vector3D: position
	- Vector3D: velocity
	- Vector3D: acceleration
- Rotation
	- Vector3D: axis
	- Float: angle
- Size
	- Vector3D: scale
- Model
	- raylib::Model model

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