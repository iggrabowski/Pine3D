#pragma once
#include "Input/KeyCodes.h"
#include "Platform/OpenGL/GLFWWindow.h"

namespace pine {

enum MousButtonAction : int {
  MOUSE_PRESS = GLFW_PRESS,
  MOUSE_RELEASE = GLFW_RELEASE,
};

enum KeyAction : int {
  KEY_PRESS = GLFW_PRESS,
  KEY_RELEASE = GLFW_RELEASE,
  KEY_REPEAT = GLFW_REPEAT
};

enum InputType : int { MOUSE_INPUT, KEYBOARD_INPUT };

enum MouseButtons : int {
  LEFT_BUTTON = GLFW_MOUSE_BUTTON_LEFT,
  RIGHT_BUTTON = GLFW_MOUSE_BUTTON_RIGHT,
  MIDDLE_BUTTON = GLFW_MOUSE_BUTTON_MIDDLE
};

class InputListener {
public:
  virtual void OnInputAction(InputType type, int key, KeyAction action) = 0;

  bool operator==(const InputListener &other) const { return this == &other; }

protected:
  InputListener();
  ~InputListener();
};

} // namespace pine
