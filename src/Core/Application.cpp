#pragma once
#include "Core/Application.h"

#include <memory>

namespace Pine {

	UniquePtr<Window> window;
	UniquePtr<Renderer> renderer;
	UniquePtr<Controls> controls;

	Vector<SceneObject*> sceneObjects;

	/*Application* Application::s_Instance = nullptr;

	Application* Application::GetInstance(const std::string& name)
	{
		if (!s_Instance) {
			s_Instance = new Application(name);
		}
		return s_Instance;
	}*/

	void UpdateFrame()
	{
		//Add some objects to SceneObjects vector
		//---------------------------------------
		//meshRenderer.

		//MeshRenderer* mr = new MeshRenderer();

		//add default Mesh renderer to the scene
		//sceneObjects.push_back(mr);

		//---------------------------------------

		renderer->Clear();

		//controls.Update(transform, event);

		// Run update function on every scene object.
		for (unsigned int i = 0; i < sceneObjects.size(); i++) {
			sceneObjects[i]->OnUpdate();
		}

		window->OnUpdate();

		//window->Display();
		//window->Sleep(0.02f);
	}

	// Old constructor.
	/*Application::Application(const std::string& name)
	{
		m_Name = name;
		m_Window = Window::Init(m_Name);
		m_Renderer = Renderer::Create();
		m_Controls = Controls::Create(*m_Window, m_Renderer->GetRenderCamera());
	}*/

	void Init(WindowSettings windowSettings)
	{
		window = Window::Init(windowSettings);

		// Default API is OpenGL due to the lack of other implementations obviously lol
		renderer = Renderer::Init(GRAPHICS_API::OPENGL_API);
		controls = Controls::Init();
	}

}