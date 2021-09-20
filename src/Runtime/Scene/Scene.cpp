#include "Scene.h"
#include "Runtime/Components/MeshRenderer.h"

namespace Pine {

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
		for (auto sceneObject : sceneObjects) {
			delete sceneObject;
		}
	}

	void Scene::OnUpdate()
	{
		// Run update function on every scene object.
		for (auto sceneObject : sceneObjects) {
			sceneObject->OnUpdate();
		}
	}

	UniquePtr<Scene> Scene::Init()
	{
		return MakeUnique<Scene>();
	}

	void Scene::CreateCube()
	{
		MeshRenderer* mr = new MeshRenderer();
		mr->CreateCubeMesh(1.0, 1.0, 1.0);
		sceneObjects.push_back(mr);
	}

	void Scene::CreateCube(float width, float height, float depth)
	{
		MeshRenderer* mr = new MeshRenderer();
		mr->CreateCubeMesh(width, height, depth);
		sceneObjects.push_back(mr);
	}

	void Scene::CreateCube(float width, float height, float depth, const Vec3& location) {
		MeshRenderer* mr = new MeshRenderer();
		mr->CreateCubeMesh(width, height, depth, location);
		sceneObjects.push_back(mr);
	}

	void Scene::CreatePlane() {
		MeshRenderer* mr = new MeshRenderer();
		mr->CreatePlaneMesh(1.0, 1.0);
		sceneObjects.push_back(mr);
	}

	void Scene::CreatePlane(float width, float depth) {
		MeshRenderer* mr = new MeshRenderer();
		mr->CreatePlaneMesh(width, depth);
		sceneObjects.push_back(mr);
	}

	void Scene::CreatePlane(float width, float depth, const Vec3& location) {
		MeshRenderer* mr = new MeshRenderer();
		mr->CreatePlaneMesh(width, depth, location);
		sceneObjects.push_back(mr);
	}

}
