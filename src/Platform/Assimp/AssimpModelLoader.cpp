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

    void LoadDiffuseTextureFromFile(const std::string& Dir, const aiString& Path, int MaterialIndex, Material* targetMaterial, Model& outModel)
    {
        std::string p(Path.data);

        if(p.substr(0,2) == ".\\")
			p = p.substr(2, p.size() - 2);

		std::string fullPath = Dir + "/" + p;
        targetMaterial->m_Textures[TEX_TYPE_BASE] = new Texture(GL_TEXTURE_2D, fullPath.c_str());
        Image* image = new Image();

        if (!image->Create(fullPath.c_str())) {
            printf("Error loading diffuse texture '%s'\n", fullPath.c_str());
        }
        else {

            targetMaterial->m_Textures[TEX_TYPE_BASE]->LoadFromImage(*image);
            outModel.materials[MaterialIndex] = targetMaterial;
            printf("Loaded diffuse texture '%s' at index %d\n", fullPath.c_str(), MaterialIndex);
        }
    }

    void LoadDiffuseTexture(const aiScene* scene, const std::string& Dir, const aiMaterial* pMaterial, int MaterialIndex, Material* targetMaterial, Model& outModel)
    {
        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                const aiTexture* paiTexture = scene->GetEmbeddedTexture(Path.C_Str());

                if (paiTexture) {
                    //LoadDiffuseTextureEmbedded(paiTexture, MaterialIndex, outMesh);
                }
                else {
                    LoadDiffuseTextureFromFile(Dir, Path, MaterialIndex, targetMaterial, outModel);
                }
            }
        }
    }

    // Flatten all meshes into a single Mesh
    bool LoadModelWithAssimp(const std::string& filePath, Model& outModel)
    {
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

        outModel.b_meshes.reserve(scene->mNumMeshes);
		outModel.materials.reserve(scene->mNumMaterials);

        unsigned int vertexOffset = 0;
        unsigned int indexOffset = 0;
        for (unsigned int meshIdx = 0; meshIdx < scene->mNumMeshes; ++meshIdx)
        {
            aiMesh* mesh = scene->mMeshes[meshIdx];
            outModel.b_meshes.emplace_back();
            outModel.b_meshes[meshIdx].numIndices = mesh->mNumFaces * 3;
            outModel.b_meshes[meshIdx].baseVertex = vertexOffset;
            outModel.b_meshes[meshIdx].baseIndex = indexOffset;
            outModel.b_meshes[meshIdx].materialIndex = mesh->mMaterialIndex;


            vertexOffset += mesh->mNumVertices;
            indexOffset += outModel.b_meshes[meshIdx].numIndices;
        }

        outModel.mesh.m_Positions.reserve(vertexOffset);
        outModel.mesh.m_Normals.reserve(vertexOffset);
		outModel.mesh.m_TexCoords.reserve(vertexOffset);
        outModel.mesh.m_Indices.reserve(indexOffset);

        for (unsigned int i = 0; i < scene->mNumMeshes; i++) {

			aiMesh* mesh = scene->mMeshes[i];
            const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
            // Populate the vertex attribute vectors
            for (unsigned int j = 0; j < mesh->mNumVertices; j++) {

                const aiVector3D& p_pos = mesh->mVertices[j];
                const aiVector3D& p_normal = mesh->mNormals[j];
                const aiVector3D& p_tex_coord = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][j] : Zero3D;
                outModel.mesh.m_Positions.emplace_back(p_pos.x, p_pos.y, p_pos.z);
                outModel.mesh.m_Normals.emplace_back(p_normal.x, p_normal.y, p_normal.z);
                outModel.mesh.m_TexCoords.emplace_back(p_tex_coord.x, p_tex_coord.y);
            }
            // Populate the index buffer
            for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
                const aiFace& Face = mesh->mFaces[j]; assert(Face.mNumIndices == 3);
                outModel.mesh.m_Indices.push_back(Face.mIndices[0]);
                outModel.mesh.m_Indices.push_back(Face.mIndices[1]);
                outModel.mesh.m_Indices.push_back(Face.mIndices[2]);
            }
            Logger::Instance().Info(
                "Loaded mesh " + std::to_string(i) + ", " + 
                std::to_string(mesh->mNumVertices) + " :  vertices, " + 
                std::to_string(mesh->mNumFaces) + "  faces"
            );
        }

		// Extract the directory part from the file path
        std::string Dir = GetDirectory(filePath);

        bool Ret = true;

        printf("Num materials: %d\n", scene->mNumMaterials);

        // Initialize the materials
        // TODO: more texture types
        for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
            const aiMaterial* pMaterial = scene->mMaterials[i];
            Material* currentMat = &Application::materials.emplace_back();

			outModel.materials.emplace_back(nullptr);
            LoadDiffuseTexture(scene, Dir, pMaterial, i, currentMat, outModel);
        }

        return Ret;
    }

    void LoadModel(const std::string& filePath)
    {
		// initiate a new MeshRenderer and add to scene
        Application::scene_objects.emplace_back(new MeshRenderer);
		MeshRenderer* meshRenderer = static_cast<MeshRenderer*>(Application::scene_objects.back().get());
        // create mesh if load true
		LoadModelWithAssimp(filePath, *meshRenderer->GetModel());

		//TODO: probably do that somewhere else
		meshRenderer->GetModel()->mesh.InitMesh();
    }

} // namespace pine