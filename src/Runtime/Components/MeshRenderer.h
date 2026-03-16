#pragma once
#include "Runtime/Components/MeshData.h"
#include "Runtime/Components/Material.h"
#include "Runtime/Components/Transform.h"
#include "Runtime/Scene/SceneObject.h"
#include "Core/Application.h"
#include <unordered_map>

namespace pine {

	struct BasicMesh
	{
		BasicMesh()
		{
			numIndices = 0;
			baseVertex = 0;
			baseIndex = 0;
			materialIndex = INVALID_MATERIAL;
		}
		unsigned int numIndices;
		unsigned int baseVertex;
		unsigned int baseIndex;
		unsigned int materialIndex;
	};

	struct Model3D {
		MeshData							mesh;
		std::vector<BasicMesh>	b_meshes;
		std::vector<Material*>		materials;
		unsigned int						num_meshes = 0;
		unsigned int						num_materials = 0;
	};

	class MeshRenderer : public SceneObject {
	public:
		MeshRenderer();
		~MeshRenderer();
		Model3D* GetModel() const { return _model3D; }
		Transform GetTransform() const { return *_transform; }

		void ResetModel3D();
		void OnUpdate() override;
		bool InitModel();
		[[nodiscard]] bool IsShadersValid() const { return _shadersValidated; }
		int GetAttributeLocation(const std::string& attName);
		std::vector<unsigned int> m_render_flags; // per 3D model materials
	private:
		Model3D*		_model3D = nullptr;
		bool _dataIsBuffered = false;
		bool _shadersValidated = false;
		bool ValidateShaderAttributes();
		// maps with all shader attributes by name and location
		std::unordered_map<unsigned int, const ShaderVariable*> loc_map;
		std::unordered_map<std::string, const ShaderVariable*> name_map;

		//Material*	_material;
	};

}