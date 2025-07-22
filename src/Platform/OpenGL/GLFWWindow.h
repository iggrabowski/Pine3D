#pragma once

#include "Core/Window.h"
#include "Utils/Utils.h"
#include <GLFW/glfw3.h>

#include "Input/InputDevices.h"

namespace pine {
	enum class KeyCode;

	struct GlfwWindowSettings
	{
		/*sf::ContextSettings contextSettings;
		bool VSync;*/
	};

	class GlfwWindow final : public Window {
	public:
		GlfwWindow();
		~GlfwWindow() override;
		explicit GlfwWindow(const WindowSettings& windowSettings);
		void Startup() override;
		void SetCursorDisabled(bool hidden) override;
	
		glm::ivec2 GetMousePosition() override;
		glm::ivec2 GetSize() override;
		void OnUpdate() override;

		[[nodiscard]] GLFWwindow* GetWindow() const;

		//void Init() override;
		//void Sleep(float seconds) override;
		//void Display() override;

		bool IsOpen() override;
	private:
		GLFWwindow* _window;
		static KeyCode GlfwToKeyCode(int glfwCode, InputDeviceType deviceType);
		static int KeyCodeToGlfw(KeyCode code);

		//sf::RenderWindow* m_Window;
		glm::vec2 _lastMousePosition;

		void HandleEvents();
	};

}
