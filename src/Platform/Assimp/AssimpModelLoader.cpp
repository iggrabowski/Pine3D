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

    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& modelDir)
    {
        Mesh out;
        out.vertices.reserve(mesh->mNumVertices);
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
        {
            Vertex v{};
            if (mesh->mVertices)
            {
                v.position[0] = mesh->mVertices[i].x;
                v.position[1] = mesh->mVertices[i].y;
                v.position[2] = mesh->mVertices[i].z;
            }
            if (mesh->mNormals)
            {
                v.normal[0] = mesh->mNormals[i].x;
                v.normal[1] = mesh->mNormals[i].y;
                v.normal[2] = mesh->mNormals[i].z;
            }
            else
            {
                v.normal[0] = v.normal[1] = v.normal[2] = 0.0f;
            }

            if (mesh->mTextureCoords[0]) // Assimp supports up to 8 UV channels; we take the first
            {
                v.uv[0] = mesh->mTextureCoords[0][i].x;
                v.uv[1] = mesh->mTextureCoords[0][i].y;
            }
            else
            {
                v.uv[0] = v.uv[1] = 0.0f;
            }

            out.vertices.push_back(v);
        }
        Mesh* meshPtr = new Mesh(mesh->mVertices, mesh->mTextureCoords, mesh->mNormals);

        // indices
        for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
        {
            const aiFace& face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; ++j)
                out.indices.push_back(face.mIndices[j]);
        }

        // material / diffuse texture (first)
        if (mesh->mMaterialIndex >= 0 && scene->mMaterials)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            aiString texPath;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == AI_SUCCESS)
            {
                std::string texStr = texPath.C_Str();
                // If relative path, prepend modelDir
                if (!texStr.empty() && (texStr[0] != '/' && texStr.find(":\\") == std::string::npos))
                    out.diffuseTexturePath = modelDir + texStr;
                else
                    out.diffuseTexturePath = texStr;
            }
        }

        return out;
    }

    void ProcessNode(aiNode* node, const aiScene* scene, const std::string& modelDir, Model& outModel)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; ++i)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            outModel.meshes.push_back(ProcessMesh(mesh, scene, modelDir));
        }

        for (unsigned int i = 0; i < node->mNumChildren; ++i)
            ProcessNode(node->mChildren[i], scene, modelDir, outModel);
    }


    bool LoadModelWithAssimp(const std::string& filePath, Model& outModel)
    {
        outModel.meshes.clear();

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
        ProcessNode(scene->mRootNode, scene, modelDir, outModel);
        return true;
}
} // namespace