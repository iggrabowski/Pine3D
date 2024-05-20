#pragma once
#include "Core/Window.h"
#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Scene/SceneObject.h"
#include "Core/InputHandler.h"
#include "Runtime/Components/MeshRenderer.h"
#include "Utils/Utils.h"
#include "Runtime/Components/Polygon.h"


namespace Pine {

	extern UniquePtr<GLFWWindow> window;
	extern UniquePtr<Renderer> renderer;
	extern UniquePtr<InputHandler> inputHandler;

	extern Vector<SceneObject*> sceneObjects;

	int Run();
	void UpdateFrame();

	void Init(WindowSettings windowSettings = WindowSettings());

}
//
////#include <string>
//
//namespace Pine {
//
//	class Application {
//	public:
//		static Application* GetInstance(const std::string& name = "Pine");
//
//		void Run();
//	private:
//		Application(const std::string& name = "Pine");
//
//		void Init();
//
//		static Application* s_Instance;
//
//		String m_Name;
//
//		UniquePtr<Window> m_Window;
//		UniquePtr<Renderer> m_Renderer;
//		UniquePtr<Controls> m_Controls;
//		//Scene objects
//		Vector<MeshRenderer*> m_SceneObjects;
//				 
//		bool m_Running = true;
//	};
//
//}