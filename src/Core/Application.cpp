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