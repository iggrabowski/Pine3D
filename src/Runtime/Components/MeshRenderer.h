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
			NumIndices = 0;
			BaseVertex = 0;
			BaseIndex = 0;
			MaterialIndex = INVALID_MATERIAL;
		}
		unsigned int NumIndices;
		unsigned int BaseVertex;
		unsigned int BaseIndex;
		unsigned int MaterialIndex;
	};

	struct Model {
		MeshData							mesh;
		std::vector<BasicMesh>	b_meshes;
		std::vector<Material*>		materials;
	};

	class MeshRenderer : public SceneObject {
	public:
		MeshRenderer();
		~MeshRenderer();

		void OnUpdate() override;
	private:
		Model*		_model;
		//Material*	_material;
	};

}