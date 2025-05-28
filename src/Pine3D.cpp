#include "Core/Application.h"

int main(void)
{
	/* INITIATE THE APPLICATION */
	pine::Application::Init();

	// TODO: fix loading textures after migrating from GLFW
	// until then, no mesh rendering

	/* ADD DEFAULT MESH RENDERER TO THE SCENE */
	pine::MeshRenderer mr;
	// Add default Mesh renderer to the scene
	pine::Application::scene_objects.push_back(&mr);

	///* ADD POLYGON TO THE SCENE */
	//std::vector<Pine::glm::vec2> vs;
	//vs.push_back(Pine::glm::vec2( 0.5f, -0.5f));
	//vs.push_back(Pine::glm::vec2( 0.5f,  0.5f));
	//vs.push_back(Pine::glm::vec2(-0.5f,  0.5f));
	//vs.push_back(Pine::glm::vec2(-0.5f, -0.5f));

	//Pine::Polygon pl(vs);
	//Pine::sceneObjects.push_back(&pl);

	pine::Application::Run();

    return 0;
}