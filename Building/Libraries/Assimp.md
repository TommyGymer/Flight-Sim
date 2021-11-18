## Assimp
---
Assimp (Asset importer) is an OpenGL library which enables the importing of a number of 3D object file formats.

[On GitHub](https://github.com/assimp/assimp)

[Building Asset Importer](https://github.com/assimp/assimp/blob/master)

[Open Asset Importer docs](https://assimp-docs.readthedocs.io/en/latest/API/API-Documentation.html)

### Usage
---
```c++
//create an instance of the importer
Assimp::Importer importer;

//read file and apply some post
const aiScene* scene = importer.ReadFile(pFile,
	aiProcess_CalcTangentSpace		|
	aiProcess_Triangulate			|
	aiProcess_JoinIdenticalVertices	|
	aiProcess_SortByPType
);

//check import for null
if(scene == nullptr){
	return false;
}

return true;
```

This will load in the aiScene object from the specified file and check that the object is there

[Using Assimp to import an object](https://ogldev.org/www/tutorial22/tutorial22.html)

### Creating a loader class
---
To create a loader class a number of imports are required:

```c++
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <gl/glew.h>
```

A header file is also required

```c++
#include "Loader.hpp"
```

A load mesh function is defined which takes a filepath and loads the object file at that filepath

```c++
bool Loader::LoadMesh(const std::string& filename)
{
	bool Ret = false;
	Assimp::Importer importer;

	const aiScene* pScene = importer.ReadFile(filename.c_str(),
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType
	);

	if (pScene) {
		Ret = InitFromScene(pScene, filename);
	}
	else {
		printf("failed to load file");
	}

	return Ret;
}
```

This also applies some postprocessing steps to clean up the loaded mesh and prepare for rendering

An init from scene function is required to extract the data at the returned pointer from the loading

```c++

```