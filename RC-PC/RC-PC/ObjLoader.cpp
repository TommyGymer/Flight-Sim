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

#include "ObjLoader.hpp"

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

bool ObjLoader::LoadMesh(const std::string& filename)
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

bool ObjLoader::InitFromScene(const aiScene *pScene, const std::string& filename) {
	m_Entries.resize(pScene->mNumMeshes);
	m_Textures.resize(pScene->mNumMaterials);

	//Init the meshes
	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(i, paiMesh);
	}

	return InitMaterials(pScene, filename);
}

void ObjLoader::InitMesh(unsigned int Index, const aiMesh* paiMesh) {
	m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

	std::vector<int> Verticies;
	std::vector<int> Indices;

	const aiVector3D Origin(0.0f, 0.0f, 0.0f);

	//loop through each vertex in the mesh and extract it's data
	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = paiMesh->HasNormals() ? &(paiMesh->mNormals[i]) : &Origin;
		const aiVector3D* pTexture = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Origin;

		cout << "(" << pPos->x << ", " << pPos->y << ", " << pPos->z << ")\n";

		//Vertex v(aiVector3D)
	}
}

bool ObjLoader::InitMaterials(const aiScene* aiScene, const std::string& filename) {
	return false;
}