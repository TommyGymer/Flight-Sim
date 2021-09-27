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