#pragma once
#include "Runtime/Components/Mesh.h"
#include <string>
#include <vector>

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

    struct Model
    {
        std::vector<Mesh> meshes;
    };

    bool LoadModelWithAssimp(const std::string& filePath, Model& outModel);
}//namespace pine