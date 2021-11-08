## CFD
---
#### Computational fluid dynamics

CFD is a method of computationally solving the equations of fluid motion to compute the state of a fluid-solid system.

A full CFD simulation can be very slow when the fluid needs to interact with the solid, which must then interact with the fluid, which must then interact with the solid again; the recursive nature of the problem makes it very expensive.

As such, it would be preferable to either predefined constants for the physics engine to use, or use a CFD model to calculate these constants before use in the simulator. This allows the CFD model to be as accurate as required through reducing the time steps, in exchange for a longer compute time.

Microsoft Flight Simulator 2020 makes use of real time CFD for the physics of its sim, making it one of the best consumer simulators currently available in terms of physical accuracy.

RC Desk Pilot makes use of the predefined constant method by storing all the constants in a file and making calculations based off these. While this method is less accurate, it allows PC Desk Pilot to run at high frame rates on standard hardware.