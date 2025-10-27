#include "AssimpModelLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <algorithm>

namespace pine {

    std::string GetDirectory(const std::string& path)
    {
        size_t pos = path.find_last_of("/\\");
        if (pos == std::string::npos) return "";
        return path.substr(0, pos + 1);
    }

    // Flatten all meshes into a single Mesh
    bool LoadModelWithAssimp(const std::string& filePath, Mesh& outMesh)
    {
        outMesh.m_Positions.clear();
		outMesh.m_TexCoords.clear();
		outMesh.m_Normals.clear();
		outMesh.m_Indices.clear();
		outMesh.m_Meshes.clear();
		outMesh.m_Materials.clear();

        Assimp::Importer importer;
        const unsigned int flags = aiProcess_Triangulate
            | aiProcess_GenSmoothNormals
            | aiProcess_CalcTangentSpace
            | aiProcess_JoinIdenticalVertices
            | aiProcess_FlipUVs;

        const aiScene* scene = importer.ReadFile(filePath, flags);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            return false;

        std::string modelDir = GetDirectory(filePath);

        outMesh.m_Meshes.reserve(scene->mNumMeshes);
		outMesh.m_Materials.reserve(scene->mNumMaterials);

        unsigned int vertexOffset = 0;
        unsigned int indexOffset = 0;
        for (unsigned int meshIdx = 0; meshIdx < scene->mNumMeshes; ++meshIdx)
        {
            aiMesh* mesh = scene->mMeshes[meshIdx];
            outMesh.m_Meshes.emplace_back();
            outMesh.m_Meshes[meshIdx].NumIndices = mesh->mNumFaces * 3;
            outMesh.m_Meshes[meshIdx].BaseVertex = vertexOffset;
            outMesh.m_Meshes[meshIdx].BaseIndex = indexOffset;
            outMesh.m_Meshes[meshIdx].MaterialIndex = mesh->mMaterialIndex;


            vertexOffset += mesh->mNumVertices;
            indexOffset += outMesh.m_Meshes[meshIdx].NumIndices;
        }

        outMesh.m_Positions.reserve(vertexOffset);
        outMesh.m_Normals.reserve(vertexOffset);
		outMesh.m_TexCoords.reserve(vertexOffset);
        outMesh.m_Indices.reserve(indexOffset);
        // (Optional) You can also collect material/texture info here if needed

        for (unsigned int i = 0; i < scene->mNumMeshes; i++) {

			aiMesh* mesh = scene->mMeshes[i];
            const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
            // Populate the vertex attribute vectors
            for (unsigned int i = 0; i < mesh->mNumVertices; i++) {

                const aiVector3D& p_pos = mesh->mVertices[i];
                const aiVector3D& p_normal = mesh->mNormals[i];
                const aiVector3D& p_tex_coord = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : Zero3D;
                outMesh.m_Positions.emplace_back(p_pos.x, p_pos.y, p_pos.z);
                outMesh.m_Normals.emplace_back(p_normal.x, p_normal.y, p_normal.z);
                outMesh.m_TexCoords.emplace_back(p_tex_coord.x, p_tex_coord.y);
            }
            // Populate the index buffer
            for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
                const aiFace& Face = mesh->mFaces[i]; assert(Face.mNumIndices == 3);
                outMesh.m_Indices.push_back(Face.mIndices[0]);
                outMesh.m_Indices.push_back(Face.mIndices[1]);
                outMesh.m_Indices.push_back(Face.mIndices[2]);
            }
        }

        return true;
    }
} // namespace pine