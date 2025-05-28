#pragma once

#include "Core/Window.h"
#include "Utils/Utils.h"

#include <GLFW/glfw3.h>

namespace pine {
	
	struct GlfwWindowSettings
	{
		/*sf::ContextSettings contextSettings;
		bool VSync;*/
	};

	class GlfwWindow final : public Window {
	public:
		GlfwWindow();
		explicit GlfwWindow(const WindowSettings& windowSettings);
		~GlfwWindow();

		glm::ivec2 GetMousePosition() override;
		glm::ivec2 GetSize() override;
		void OnUpdate() override;
		GLFWwindow* GetWindow() const
		{
			return _window;
		};

		//void Init() override;
		//void Sleep(float seconds) override;
		//void Display() override;

		bool IsOpen() override;
	private:
		GLFWwindow* _window;

		//sf::RenderWindow* m_Window;
		glm::vec2 _lastMousePosition;

		void HandleEvents();
	};

}