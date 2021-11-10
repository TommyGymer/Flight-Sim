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

private:
	bool InitFromScene(const aiScene* pScene, const std::string& filename);
	void InitMesh(unsigned int index, const aiMesh* paiMesh);
	bool InitMaterials(const aiScene* pScene, const std::string& filename);

#define TEXTURE_NF 0xFFFFFFFF

	struct MeshEntry {
		/*bool Init(const std::vector<std::vector<int>>& Vertices,
			const std::vector<int>& Indices);
		*/
		const std::vector<std::vector<int>>& Vertices;
		const std::vector<int>& Indices;
		GLuint VB;
		GLuint IB;
		unsigned int NumIndices;
		unsigned int MaterialIndex;
	};

	std::vector<MeshEntry> m_Entries;
	std::vector<int> m_Textures;
};