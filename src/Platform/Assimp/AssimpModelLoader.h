#pragma once
#include "Runtime/Components/MeshData.h"
#include <string>
#include <vector>
#include <Core/Application.h>

namespace pine {
    //struct Vertex
    //{
    //    float position[3];
    //    float normal[3];
    //    float uv[2];
    //};

    //struct Mesh
    //{
    //    std::vector<Vertex> vertices;
    //    std::vector<unsigned int> indices;
    //    std::string diffuseTexturePath; // empty if none
    //};
	void LoadModel(const std::string& filePath);
    bool LoadModelWithAssimp(const std::string& filePath, Model3D& outModel);
}//namespace pine