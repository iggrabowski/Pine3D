#pragma once
#include "Core/Application.h"
#include <memory>

namespace pine {

	//If in Editor
	/*Application* Application::s_Instance = nullptr;

	Application* Application::GetInstance(const std::string& name)
	{
		if (!s_Instance) {
			s_Instance = new Application(name);
		}
		return s_Instance;
	}*/

	//int run()
	//{
	//	//MAIN LOOP
	//	while (window->IsOpen()) {
	//		update_frame();
	//	}
	//	return 0;
	//}
	int Application::Run()
	{
		light_presets.resize(3); // three light presets
		// light preset 1

		light_presets[0].emplace_back(
			LIGHT_TYPE_DIRECTIONAL,
			glm::vec3(2.0f, 1.0f, 1.0f),
			glm::vec3(0.0f, 0.9f, 0.0f) // green light
		);

		light_presets[0].emplace_back(
			LIGHT_TYPE_DIRECTIONAL,
			glm::vec3(-2.0f, 1.0f, -2.0f),
			glm::vec3(0.95f, 0.1f, 0.1f) // red light
		);

		light_presets[0].emplace_back(
			LIGHT_TYPE_DIRECTIONAL,
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.12f, 0.1f, 0.917f) // blue light
		);

		// light preset 2  //blue
		light_presets[1].emplace_back(
			LIGHT_TYPE_DIRECTIONAL,
			glm::vec3(2.0f, 1.0f, 1.0f),
			glm::vec3(0.34f, 0.74f, 0.998f)
		);

		light_presets[1].emplace_back(
			LIGHT_TYPE_DIRECTIONAL,
			glm::vec3(-2.0f, 1.0f, -2.0f),
			glm::vec3(0.339f, 0.898f, 0.979f	)
		);

		light_presets[1].emplace_back(
			LIGHT_TYPE_DIRECTIONAL,
			glm::vec3(0.0f, -1.0f, 0.0f),  // white light
			glm::vec3(0.339f, 0.398f,0.998f)
		);

		// light preset 3

		//light_presets[2].emplace_back(
		//	LIGHT_TYPE_DIRECTIONAL,
		//	glm::vec3(2.0f, 1.0f, 1.0f),
		//	glm::vec3(0.52f, 0.8f, 0.917f) // blue sky light
		//);

		light_presets[2].emplace_back(
			LIGHT_TYPE_DIRECTIONAL,
			glm::vec3(-2.0f, 1.0f, -2.0f),
			glm::vec3(1.0f) // white light
		);

		//light_presets[2].emplace_back(
		//	LIGHT_TYPE_DIRECTIONAL,
		//	glm::vec3(0.0f, -1.0f, 0.0f),
		//	glm::vec3(0.95f, 0.4f, 0.2f) // orange light
		//);

		//MAIN LOOP
		while (window->IsOpen()) {
			Update_Frame();
		}
		return 0;
	}

	void Application::Update_Frame()
	{
		//Add some objects to SceneObjects vector
		//---------------------------------------
		//meshRenderer.
		//MeshRenderer* mr = new MeshRenderer();
		//add default Mesh renderer to the scene
		//sceneObjects.push_back(mr);
		//---------------------------------------

		input_handler->OnUpdate();
		renderer->Clear();
		input_handler->OnUpdate();
		editor->OnUpdate();

		// Run update function on every scene object.
		for (const auto& sceneObject : scene_objects)
		{
			sceneObject->OnUpdate();
		}

		mr.OnUpdate();
		window->OnUpdate();
		//window->Display();
		//window->Sleep(0.02f);
	}

	void Application::Init()
	{
		// TODO: chekc if some init methods can be moved to Startup
		Logger::Instance().Info("Pine3D: begin initiating objects...");
		window = std::make_unique<GlfwWindow>();
		input_handler = InputHandler::Init();
		//If in editor
		editor = Editor::Init();
		// Default API is OpenGL due to the lack of other implementations obviously lol
		renderer = Renderer::Init(GRAPHICS_API::OPENGL_API);
		Logger::Instance().Success("Pine3D: ...initiating objects complete.");
	}

	void Application::Startup()
	{
		Logger::Instance().Info("Pine3D: starting...");
		// Startup the window and other components
		window->Startup();
		editor->Startup();
		Logger::Instance().Success("Pine3D: ...startup complete.");
	}

	//TODO shutdown impl	
}