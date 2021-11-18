## Using vcpkg
---
vcpkg is a package manager maintained by Microsoft

It allows the installing of, and importing of, many C++ libraries

All the required libraries for this project are available on it, so this project will make use of it rather than CMake

### Installation
---
```batch
git clone https://github.com/microsoft/vcpkg
.\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg install [packages to install]:x64-windows
...
.\vcpkg\vcpkg integrate install
```

This sets up the vcpkg environment for the user

The required libraries are
- assimp:x64-windows
- glew:x64-windows
- glm:x64-windows
- imgui:x64-windows
- glfw3:x64-windows