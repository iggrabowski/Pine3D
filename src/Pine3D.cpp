#include "Core/Application.h"

int main(void)
{
	/* INITIATE THE APPLICATION */
	pine::Application::Init();
	pine::Application::Startup();

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

	// test input mapping
	// test key mapping
	//pine::Application::input_handler->MapInputToAction(pine::KeyCode::A, { "test", pine::KEY_ON_PRESS + pine::KEY_ON_RELEASE, -1.0f });
	//pine::Application::input_handler->AddActionCallback("test", 
	//	pine::InputHandler::ActionCallback {
	//		.ref = "test_callback",
	//		.func = [](int sourceIndex, float value)
	//		{
	//			pine::Logger::Instance().Info("test A");

	//			return true;
	//		} 
	//	});

	//// test mouse mapping
	//pine::Application::input_handler->MapInputToAction(pine::KeyCode::MB_BUTTON_LEFT, { "test_mouse", pine::KEY_ON_PRESS + pine::KEY_ON_RELEASE, 1.0f });
	//pine::Application::input_handler->AddActionCallback("test_mouse", 
	//	pine::InputHandler::ActionCallback {
	//		.ref = "test_mouse_callback",
	//		.func = [](int sourceIndex, float value)
	//		{
	//			pine::Logger::Instance().Info("test LEFT MOUSE");

	//			return true;
	//		} 
	//	});

	pine::Application::Run();

    return 0;
}