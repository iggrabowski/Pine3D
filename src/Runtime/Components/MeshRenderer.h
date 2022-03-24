#pragma once
#include "Runtime/Components/Mesh.h"
#include "Runtime/Components/Material.h"
#include "Runtime/Components/Transform.h"
#include "Runtime/Scene/SceneObject.h"

namespace Pine {

	class MeshRenderer : public SceneObject {
	public:
		MeshRenderer();
		~MeshRenderer();

		void OnUpdate() override;
	private:
		Mesh* m_Mesh;
		Material* m_Material;
	};

}