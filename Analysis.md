## Analysis
---
### Overview
---
#### A market gap for a model flight sim

The available flight sims currently on the market are designed with full scale aircraft in mind, making them unsuitable for people wishing to increase their flight hours on model aircraft.

All currently available model flight sims are either designed for Windows XP or require proprietary hardware.

A modern flight sim designed on a base of OpenGL 4.0 and C++ will provide full performance on modern hardware and sufficient resolution for flying a model aircraft.

To fill this market space, the sim will need to have sufficient game textures available to approach the detail of a modern sim and sufficiently accurate physics to act as practice for flying read model aircraft.

#### Extracted points

- RC-PC will be a model aircraft flight simulation.
- It is intended as both a game and a realistic simulator.
- To fit as a game, it may be beneficial to add some form of competition
- It should be capable of allowing a user to create their own aircraft.
- This process should be possible using only knowledge of Blender.
- It will be built in C++ using OpenGL

#### Stakeholders

My target market will include:
- People interested in simulators as games (a similar demographic to Microsoft Flight Sim)
	- They would be looking for a simulator with a range of features beyond an accurate physics engine
	- A lighter flight sim or one with options which allow the application to run without requiring cutting edge hardware would be preferable for this market to allow a wider demographic
	- A mostly seamless experience without needing to fiddle with settings for setup
	- A range of pre-made aircraft, preventing the need to understand how to define their own
	- A multiplayer aspect would be preferable to fit this demographic, though adds significant complexity with the need for a fast server along with a domain
- People interested in realistic simulation for flight practice
	- Mainly focused on the accuracy and realism of the simulator
	- Completely robust through all orientations and movements
	- Tools to represent their own aircraft in the sim

As such, I intend to ask a few people in each demographic to gauge usability and satisfaction with the physics and visuals of the application

I also plan to ask some people outside of this target market to gauge usability and to possible add some form of tutorial
- To expand this, the tutorial could try to detect the type of input device in use and tailor the information to fit the input device

#### First steps
- Find similar products
- Build an application in C++ and OpenGL following tutorials to gain an understanding of the architecture
- Document the architecture to begin work on the application

### Existing products and projects
---
#### RC Desk Pilot

![[Pasted image 20211116205330.png]]

- Range of model aircraft available
- Tools to make your own aircraft
- Connects to a range of different controllers
- Weather features
- Sufficiently accurate physics

#### Microsoft Flight Sim 2020

![[ms-flight-sim.jpg]][image from "Rock Paper Shotgun"](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.rockpapershotgun.com%2Fall-341-photorealistic-cities-in-microsoft-flight-simulator-2020&psig=AOvVaw2-aPVRGJ0CPWs3C3HYoOUM&ust=1636021274292000&source=images&cd=vfe&ved=0CAsQjRxqFwoTCKj1par8-_MCFQAAAAAdAAAAABAE)
- Range of very detailed aircraft models available
- Highly detailed environment
- Unreasonably accurate physics and weather
- Use of Windows libraries allows wide range of input device compatibility

### Features
---
- Pre-made models available
- Tools to make new models
- Loading these models
- Animation of these models with the input
- Compatibility with a number of input devices (including keyboard and mouse)
- Accurate physics while maintaining performance
- Reasonable environment

### Implementation
---
- OpenGL based rendering with C++/C#
- Using pre-baked physics to remove the need for real time [[CFD]]
- GLFW input (or XInput for extra compatibility) API
- Models stored and loaded from a custom file format

#### Limitations of implementation
- Fairly resource intensive due to the full frame rate rendering
- Pre-baked physics will be slightly inaccurate compared to a real time [[CFD]] simulation
- 

### Hardware requirements
---
- Capable of running an OpenGL application at a usable frame rate
- A compatible controller

### Brief
---
- Realistic flight performance of aircraft
- Can be controlled with a variety of different input devices
- Runs at least 30fps, preferably more than 60fps
- Runs with sufficient resolution to allow easy control of a distance aircraft
- Included or built in tools to make new aircraft models