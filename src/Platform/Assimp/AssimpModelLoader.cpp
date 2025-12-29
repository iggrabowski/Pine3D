#include "AssimpModelLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <algorithm>

#include "assimp/pbrmaterial.h"


namespace pine {

	// TODO: change printf to logger
    std::string GetDirectory(const std::string& path)
    {
        size_t pos = path.find_last_of("/\\");
        if (pos == std::string::npos) return "";
        return path.substr(0, pos + 1);
    }

    void LoadTextureFromFile(const std::string& Dir, const aiString& Path, TextureType texType, int MaterialIndex, Material* targetMaterial, Model3D& outModel)
    {
        std::string p(Path.data);

        if (p.substr(0, 2) == ".\\")
            p = p.substr(2, p.size() - 2);

        std::string fullPath = Dir + "/" + p;
        targetMaterial->m_textures[texType] = new Texture(GL_TEXTURE_2D, fullPath.c_str());
        Image image;

        if (!image.Create(fullPath.c_str())) {
            printf("Error loading texture '%s'\n", fullPath.c_str());
        }
        else {
            targetMaterial->m_textures[texType]->LoadFromImage(image);
            outModel.materials[MaterialIndex] = targetMaterial;
            printf("Loaded texture '%s' (type %d) at index %d\n", fullPath.c_str(), texType, MaterialIndex);
        }
    }

    void LoadAllMaterialTextures(const aiScene* scene, const std::string& Dir, const aiMaterial* pMaterial, int MaterialIndex, Material* targetMaterial, Model3D& outModel)
    {
        struct TexTypeInfo {
            aiTextureType assimpType;
            TextureType pineType;
        };

        // List of texture types to load
        const TexTypeInfo texTypes[] = {
            { aiTextureType_DIFFUSE,            TEX_TYPE_BASE },
            { aiTextureType_NORMALS,            TEX_TYPE_NORMAL },
            { aiTextureType_METALNESS,          TEX_TYPE_METALLIC },
            { aiTextureType_DIFFUSE_ROUGHNESS,  TEX_TYPE_ROUGHNESS },
            { aiTextureType_AMBIENT_OCCLUSION,  TEX_TYPE_AO },
            { aiTextureType_HEIGHT,             TEX_TYPE_NORMAL }, // for now height will be normal
            { aiTextureType_EMISSIVE,           TEX_TYPE_EMISSIVE }
        };

        for (const auto& texInfo : texTypes) {
            if (pMaterial->GetTextureCount(texInfo.assimpType) > 0) {
                aiString Path;
                if (pMaterial->GetTexture(texInfo.assimpType, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                    const aiTexture* paiTexture = scene->GetEmbeddedTexture(Path.C_Str());
                    if (paiTexture) {
                        // TODO: handle embedded textures if needed
                    }
                    else {
                        LoadTextureFromFile(Dir, Path, texInfo.pineType, MaterialIndex, targetMaterial, outModel);
                    }
                }
            }
        }
    }

    // Flatten all meshes into a single Mesh
    bool LoadModelWithAssimp(const std::string& filePath, Model3D& outModel)
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

		outModel.num_meshes = scene->mNumMeshes;
		outModel.num_materials = scene->mNumMaterials;
        outModel.b_meshes.reserve(outModel.num_meshes );
		outModel.materials.reserve(outModel.num_materials);

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
        outModel.mesh.m_Tangents.reserve(vertexOffset);
		outModel.mesh.m_Bitangents.reserve(vertexOffset);
        outModel.mesh.m_Indices.reserve(indexOffset);

        for (unsigned int i = 0; i < scene->mNumMeshes; i++) {

			aiMesh* mesh = scene->mMeshes[i];
            const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
            // Populate the vertex attribute vectors
            for (unsigned int j = 0; j < mesh->mNumVertices; j++) {

                const aiVector3D& p_pos = mesh->mVertices[j];
                const aiVector3D& p_normal = mesh->mNormals[j];
                const aiVector3D& p_tex_coord = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][j] : Zero3D;
				const aiVector3D& p_tangent = mesh->HasTangentsAndBitangents() ? mesh->mTangents[j] : Zero3D;
				const aiVector3D& p_bitangent = mesh->HasTangentsAndBitangents() ? mesh->mBitangents[j] : Zero3D;
                outModel.mesh.m_Positions.emplace_back(p_pos.x, p_pos.y, p_pos.z);
                outModel.mesh.m_Normals.emplace_back(p_normal.x, p_normal.y, p_normal.z);
                outModel.mesh.m_TexCoords.emplace_back(p_tex_coord.x, p_tex_coord.y);
				outModel.mesh.m_Tangents.emplace_back(p_tangent.x, p_tangent.y, p_tangent.z);
				outModel.mesh.m_Bitangents.emplace_back(p_bitangent.x, p_bitangent.y, p_bitangent.z);
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
        for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
            const aiMaterial* pMaterial = scene->mMaterials[i];
            Material* currentMat = &Application::materials.emplace_back();
			pMaterial->Get(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_ROUGHNESS_FACTOR, currentMat->m_roughness);

			outModel.materials.emplace_back(currentMat);
            LoadAllMaterialTextures(scene, Dir, pMaterial, i, currentMat, outModel);

            example::color_editor.AddMaterialNodes(currentMat, ImVec2(1,1));
        }

        return Ret;
    }

    void LoadModel(const std::string& filePath)
    {
#ifdef SINGLE_MESH_MODE
			Application::mr.ResetModel3D();
            LoadModelWithAssimp(filePath, *Application::mr.GetModel());

		// TODO: probably do that somewhere else
			Application::mr.InitModel();
#else 
		// initiate a new MeshRenderer and add to scene
        // multiple meshes version 
            Application::scene_objects.emplace_back(new MeshRenderer);
            MeshRenderer* meshRenderer = static_cast<MeshRenderer*>(Application::scene_objects.back().get());
            // create mesh if load true
            LoadModelWithAssimp(filePath, *meshRenderer->GetModel());
			meshRenderer->InitModel();
#endif
    }

} // namespace pine