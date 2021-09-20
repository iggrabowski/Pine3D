#pragma once
#include "Runtime/Components/Mesh.h"
#include "Runtime/Components/Material.h"
#include "Runtime/Components/Transform.h"
#include "Runtime/Scene/SceneObject.h"

namespace Pine {

	enum class MeshType {
		MESH_TYPE_CUBE,
		MESH_TYPE_SPHERE,
		MESH_TYPE_PLANE
	};

	class MeshRenderer : public SceneObject {
	public:
		MeshRenderer();
		//MeshRenderer(MeshType meshType, float width, float height, float depth);
		//MeshRenderer(MeshType meshType, float width, float depth);
		//MeshRenderer(MeshType meshType);
		~MeshRenderer();

		void CreateCubeMesh(float width, float height, float depth);
		void CreateCubeMesh(float width, float height, float depth, const Vec3& location);
		void CreatePlaneMesh(float width, float depth);
		void CreatePlaneMesh(float width, float depth, const Vec3& location);
		void OnUpdate() override;
	private:
		Mesh* m_Mesh;
		Material* m_Material;
	};

}