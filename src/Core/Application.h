#pragma once
#include "Core/Window.h"
#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Scene/SceneObject.h"
#include "Core/Controls.h"
#include "Runtime/Components/MeshRenderer.h"
#include "Utils/Utils.h"
#include "Runtime/Components/Polygon.h"


namespace Pine {

	extern UniquePtr<Window> window;
	extern UniquePtr<Renderer> renderer;
	extern UniquePtr<Controls> controls;

	extern Vector<SceneObject*> sceneObjects;

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