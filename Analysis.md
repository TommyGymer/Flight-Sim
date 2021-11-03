## Analysis
---
### Overview
---
- RC-PC will be a model aircraft flight simulation.
- It is intended as both a game and a realistic simulator.
- It should be capable of allowing a user to create their own aircraft.
- This process should be possible using only knowledge of Blender.

#### Stakeholders

My target market will include:
- People interested in simulators as games (a similar demographic to Microsoft Flight Sim)
- People interested in realistic simulation for flight practice

### Existing products and projects
---
#### RC Desk Pilot

![[rc-desk-pilot.jpg]][image from "RC Desk Pilot"](https://www.google.com/url?sa=i&url=https%3A%2F%2Frcdeskpilot.com%2F&psig=AOvVaw3fUM5iRx5TZjbsY1iT7Jar&ust=1636021407916000&source=images&cd=vfe&ved=0CAsQjRxqFwoTCKC-6vb8-_MCFQAAAAAdAAAAABAU)
- Range of model aircraft available
- Tools to make your own aircraft
- Connects to a range of different controllers
- Weather features
- Sufficiently accurate physics

#### Microsoft Flight Sim 2020

![[ms-flight-sim.jpg]][image from "Rock Paper Shotgun"](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.rockpapershotgun.com%2Fall-341-photorealistic-cities-in-microsoft-flight-simulator-2020&psig=AOvVaw2-aPVRGJ0CPWs3C3HYoOUM&ust=1636021274292000&source=images&cd=vfe&ved=0CAsQjRxqFwoTCKj1par8-_MCFQAAAAAdAAAAABAE)
- Range of very detailed aircraft models available
- Highly detailed environment
- Unresonably accurate physics and weather
- Use of Windows libraries allows wide range of input device compatability

### Features
---
- Premade models available
- Tools to make new models
- Loading these models
- Animation of these models with the input
- Compatability with a number of input devices (including keyboard and mouse)
- Accurate physics while maintaining performance
- Resonable environment

### Implementaion
---
- OpenGL based rendering with C++/C#
- Using prebaked physics to remove the need for real time CFD
- GLFW input (or XInput for extra compatibility) API
- Models stored and loaded from a custom file format

#### Limitations of implementation
- Fairly resource intensive due to the full frame rate rendering
- Prebaked physics will be slightly inaccurate compared to a real time CFD simulation
- 

### Hardware requirements
---
- Capable of running an OpenGL application at a usable frame rate
- A compatable controller

### Brief
---
- Realistic flight performance of aircraft
- Can be controlled with a variety of different input devices
- Runs at least 30fps, prefereably more than 60fps
- Runs with sufficient resolusion to allow easy control of a distance aircraft
- Included or built in tools to make new aircraft models