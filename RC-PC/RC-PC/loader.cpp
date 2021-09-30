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
#include <gl/glew.h>
#include "Loader.hpp"

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

bool Loader::InitFromScene(const aiScene*, const std::string& filename) {
	return 0;
}