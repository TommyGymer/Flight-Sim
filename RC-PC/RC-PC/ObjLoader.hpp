#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <stdlib.h>
#include <string.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>
#include <gl/glew.h>

class ObjLoader
{
public:
	ObjLoader();

	~ObjLoader();

	bool LoadMesh(const std::string& Filename);

	bool DebugMaterial();

private:
	bool InitFromScene(const aiScene* pScene, const std::string& filename);
	void InitMesh(unsigned int index, const aiMesh* paiMesh);
	bool InitMaterials(const aiScene* pScene, const std::string& filename);

#define TEXTURE_NF 0xFFFFFFFF

	struct MeshEntry {
		MeshEntry();

		MeshEntry(std::vector<std::vector<float>>& _Vertices);

		MeshEntry(std::vector<std::vector<float>>& _Vertices,
			std::vector<int>& _Indices);

		~MeshEntry();

		std::vector<std::vector<float>>* Vertices;
		std::vector<int>* Indices;

		GLuint VB;
		GLuint IB;
		unsigned int NumIndices;
		unsigned int MaterialIndex;
	};

	std::vector<MeshEntry> m_Entries;
	std::vector<int> m_Textures;
};