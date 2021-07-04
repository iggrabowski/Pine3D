#pragma once
#include "Core/Window.h"
#include "Platform/SFML/SFMLWindow.h"


namespace Pine {

	//Window* Window::s_Instance = nullptr;

	UniquePtr<Window> Window::Init(const WindowSettings& windowSettings)
	{
		//#ifdef WINDOW_SFML
		return MakeUnique<SFMLWindow>(windowSettings);
		//#endif
	}

	bool Window::GetIsActive() {
		return m_IsActive;
	}

}
