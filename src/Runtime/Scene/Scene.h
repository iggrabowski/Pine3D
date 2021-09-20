#pragma once
#include "Utils/Utils.h"
#include "Runtime/Scene/SceneObject.h"

namespace Pine {

	class Scene {
	public:
		Scene();
		~Scene();

		void OnUpdate();
		static UniquePtr<Scene> Init();
		void CreateCube();
		void CreateCube(float width, float height, float depth);
		void CreateCube(float width, float height, float depth, const Vec3& location);
		void CreatePlane();
		void CreatePlane(float width, float depth);
		void CreatePlane(float width, float depth, const Vec3& location);

		Vector<SceneObject*> sceneObjects;
	};

}