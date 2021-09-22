## Build Requirements
---
#### Programs
1. [[CMake]]
2. Visual Studio

#### Libraries
1. [[AntTweakBar]]
2. [[assimp]]
3. [[bullet]]
4. [[glew]]
5. [[glfw]]
6. [[glm]]

These are imported from a local `/external` folder using
```C++
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
```

This also includes the standard C++ libraries for IO and other basic methods

### vcpkg
---
Vcpkg is a package manager maintained by Microsoft which allows the installing a linking of C++ libraries