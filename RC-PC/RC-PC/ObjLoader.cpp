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

bool ObjLoader::DebugMaterial()
{
	cout << "Is this being run?\n";
	int length = m_Entries[0].Vertices->size();
	cout << length;
	for (int i = 0; i < length; i++) {
		vector<float> pPos = m_Entries[0].Vertices->at(i);
		cout << "(" << pPos[0] << ", " << pPos[1] << ", " << pPos[2] << ")\n";
	}
	cout << "It was runned\n";
	return false;
}

bool ObjLoader::InitFromScene(const aiScene *pScene, const std::string& filename) {
	m_Entries.resize(pScene->mNumMeshes);
	m_Textures.resize(pScene->mNumMaterials);

	//cout << m_Entries.size();

	//Init the meshes
	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(i, paiMesh);
	}

	return InitMaterials(pScene, filename);
}

void ObjLoader::InitMesh(unsigned int Index, const aiMesh* paiMesh) {
	m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

	std::vector<std::vector<float>> _Verticies{ paiMesh->mNumVertices, {0, 0, 0} };
	std::vector<int> _Indices; //not sure what this is for yet

	const aiVector3D Origin(0.0f, 0.0f, 0.0f);

	//loop through each vertex in the mesh and extract its data
	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = paiMesh->HasNormals() ? &(paiMesh->mNormals[i]) : &Origin;
		const aiVector3D* pTexture = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Origin;

		std::vector<float> vect{ pPos->x * 1.0f, pPos->y * 1.0f, pPos->z * 1.0f };
		_Verticies[i] = vect;

		//cout << "(" << pPos->x << ", " << pPos->y << ", " << pPos->z << ")\n";
	}

	m_Entries[Index] = _Verticies;
}

bool ObjLoader::InitMaterials(const aiScene* aiScene, const std::string& filename) {
	return false;
}

ObjLoader::MeshEntry::MeshEntry() {

}

ObjLoader::MeshEntry::MeshEntry(std::vector<std::vector<float>>& _Vertices)
{
	ObjLoader::MeshEntry::Vertices = &_Vertices;
}

ObjLoader::MeshEntry::MeshEntry(std::vector<std::vector<float>>& _Vertices,
	std::vector<int>& _Indices)
{
	ObjLoader::MeshEntry::Vertices = &_Vertices;
	ObjLoader::MeshEntry::Indices = &_Indices;
}

ObjLoader::MeshEntry::~MeshEntry()
{
}