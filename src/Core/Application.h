#pragma once
//#include "Core/Window.h"
#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Scene/SceneObject.h"
#include "Input/InputHandler.h"
//#include "Runtime/Components/MeshRenderer.h"
//#include "Utils/Utils.h"
#include "Runtime/Components/Polygon.h"
#include "Editor/Editor.h"
#include "Utils/Logger.h"

namespace pine {

	 class Application {

	 public:
		static int Run();
		static void Update_Frame();
		static void Init();
		static void Startup();

		static inline std::unique_ptr<Editor> editor = nullptr;
		static inline std::unique_ptr<GlfwWindow> window = nullptr; //for now only GLFW window implementation
		static inline std::unique_ptr<Renderer> renderer = nullptr;
		static inline std::unique_ptr<InputHandler> input_handler = nullptr;
		static inline std::vector<SceneObject*> scene_objects;
		//static inline std::unique_ptr<Logger> logger = nullptr;
	};

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
//		UniquePtr<Renderer> m_Rendereiir;
//		UniquePtr<Controls> m_Controls;
//		//Scene objects
//		Vector<MeshRenderer*> m_SceneObjects;
//				 
//		bool m_Running = true;
//	};
//
//}