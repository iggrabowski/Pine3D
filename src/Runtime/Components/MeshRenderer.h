#pragma once
#include "Runtime/Components/MeshData.h"
#include "Runtime/Components/Material.h"
#include "Runtime/Components/Transform.h"
#include "Runtime/Scene/SceneObject.h"

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
		std::vector<unsigned int> m_render_flags;
	private:
		Model3D*		_model3D = nullptr;
		//Material*	_material;
	};

}