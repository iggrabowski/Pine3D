#pragma once
#include "Core/Window.h"
#include "Platform/OpenGL/GLFWWindow.h"


namespace Pine {

	//Window* Window::s_Instance = nullptr;

	UniquePtr<Window> Window::Init(const WindowSettings& windowSettings)
	{
		//#ifdef WINDOW_GLFW
		return MakeUnique<GLFWWindow>(windowSettings);
		//#endif
	}

}
