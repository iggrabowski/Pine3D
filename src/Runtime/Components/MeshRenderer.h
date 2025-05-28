#pragma once
#include "Runtime/Components/Mesh.h"
#include "Runtime/Components/Material.h"
#include "Runtime/Components/Transform.h"
#include "Runtime/Scene/SceneObject.h"

namespace pine {

	class MeshRenderer : public SceneObject {
	public:
		MeshRenderer();
		~MeshRenderer();

		void OnUpdate() override;
	private:
		Mesh* _mesh;
		Material* _material;
	};

}