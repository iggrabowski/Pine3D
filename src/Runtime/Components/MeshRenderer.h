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

	struct Model {
		MeshData					mesh;
		std::vector<BasicMesh>		b_meshes;
		std::vector<Material*>		materials;
	};

	class MeshRenderer : public SceneObject {
	public:
		MeshRenderer();
		~MeshRenderer();
		Model* GetModel() const { return _model; }
		Transform GetTransform() const { return *_transform; }

		void OnUpdate() override;
	private:
		Model*		_model; //TODO: confusion with model matrix
		//Material*	_material;
	};

}