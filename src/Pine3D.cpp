#include "Core/Application.h"

int main(void)
{
	/* INITIATE THE APPLICATION */
	Pine::Init();

	// TODO: fix loading textures after migrating from GLFW
	// until then, no mesh rendering

	/* ADD DEFAULT MESH RENDERER TO THE SCENE */
	Pine::MeshRenderer mr;
	// Add default Mesh renderer to the scene
	Pine::sceneObjects.push_back(&mr);


	///* ADD POLYGON TO THE SCENE */
	//std::vector<Pine::Vec2> vs;
	//vs.push_back(Pine::Vec2( 0.5f, -0.5f));
	//vs.push_back(Pine::Vec2( 0.5f,  0.5f));
	//vs.push_back(Pine::Vec2(-0.5f,  0.5f));
	//vs.push_back(Pine::Vec2(-0.5f, -0.5f));

	//Pine::Polygon pl(vs);
	//Pine::sceneObjects.push_back(&pl);

	//MAIN LOOP
	while (Pine::window->IsOpen()) {
		Pine::UpdateFrame();
	}

    return 0;
}