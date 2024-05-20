#pragma once
#include "Core/KeyCodes.h"
#include "Platform/OpenGL/GLFWWindow.h"

namespace Pine {

	enum KeyAction {
		KEY_PRESS = GLFW_PRESS,
		KEY_RELEASE = GLFW_RELEASE,
		KEY_REPEAT = GLFW_REPEAT
	};

	enum InputType {
		Mouse,
		Keyboard
	};

	class InputListener {
	public:
		virtual void OnInput(InputType type, KeyCode key, KeyAction action) = 0;

	protected:
		InputListener();
		~InputListener();
	};

}