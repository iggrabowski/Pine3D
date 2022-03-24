#pragma once

#include "Core/Window.h"
#include "Utils/Utils.h"

#include <GLFW/glfw3.h>

namespace Pine {
	
	struct GLFWWindowSettings
	{
		/*sf::ContextSettings contextSettings;
		bool VSync;*/
	};

	class GLFWWindow : public Window {
	public:
		GLFWWindow(const WindowSettings& windowSettings);
		~GLFWWindow();

		Vec2i GetMousePosition() override;
		Vec2i GetSize() override;
		void OnUpdate() override;

		//void Init() override;
		//void Sleep(float seconds) override;
		//void Display() override;

		bool IsOpen() override;
	private:
		GLFWwindow* m_Window;
		//sf::RenderWindow* m_Window;
		Vec2 m_LastMousePosition;

		void HandleEvents();
	};

}