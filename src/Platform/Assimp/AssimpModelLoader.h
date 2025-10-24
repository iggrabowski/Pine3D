#pragma once

#include <string>
#include <vector>

struct Vertex
{
    float position[3];
    float normal[3];
    float uv[2];
};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::string diffuseTexturePath; // empty if none
};

struct Model
{
    std::vector<Mesh> meshes;
};

bool LoadModelWithAssimp(const std::string& filePath, Model& outModel);