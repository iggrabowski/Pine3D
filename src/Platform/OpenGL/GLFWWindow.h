#pragma once

#include "Core/Window.h"
#include "Utils/Utils.h"
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


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

		 // Our ImGUI state
		bool _show_demo_window = false;
		bool _show_another_window = false;
		ImVec4 _clear_color = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

		void HandleEvents();
		void AddGlfwCallbacks();
	};

}
