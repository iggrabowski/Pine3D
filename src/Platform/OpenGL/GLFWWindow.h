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

		glm::ivec2 GetMousePosition() override;
		glm::ivec2 GetSize() override;
		void OnUpdate() override;
		GLFWwindow* GetWindow() {
			return _window;
		};

		//void Init() override;
		//void Sleep(float seconds) override;
		//void Display() override;

		bool IsOpen() override;
	private:
		GLFWwindow* _window;

		//sf::RenderWindow* m_Window;
		glm::vec2 _LastMousePosition;

		void HandleEvents();
	};

}