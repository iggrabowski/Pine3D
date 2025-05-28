#pragma once
#include "Core/Window.h"
#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Scene/SceneObject.h"
#include "Input/InputHandler.h"
#include "Runtime/Components/MeshRenderer.h"
#include "Utils/Utils.h"
#include "Runtime/Components/Polygon.h"
#include "Editor/Editor.h"

namespace pine {

	 class Application {

	 public:
		static int Run();
		static void Update_Frame();
		static void Init();

		static inline UniquePtr<Editor> editor = nullptr;
		static inline UniquePtr<GlfwWindow> window = nullptr; //for now only GLFW window implementation
		static inline UniquePtr<Renderer> renderer = nullptr;
		static inline UniquePtr<InputHandler> input_handler = nullptr;
		static inline Vector<SceneObject*> scene_objects;
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