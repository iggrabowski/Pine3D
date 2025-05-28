#pragma once
#include <functional>

#include "Input/KeyCodes.h"

enum class InputDeviceType : uint8_t
{
	// Input device types
	KEYBOARD,
	MOUSE,
	GAMEPAD,
	TOUCH_SCREEN,
	NONE
};

struct InputDeviceState { //TODO maybe delete
	float value;
};

using InputDeviceCallbackFunc = std::function<std::unordered_map<pine::KeyCode, InputDeviceState>(int8_t)>;
struct InputDevice
{
	int8_t index;
	InputDeviceType type = InputDeviceType::NONE;
	std::unordered_map<pine::KeyCode, InputDeviceState> states;
	InputDeviceCallbackFunc callback_func;
};

inline const char* to_string(const InputDeviceType e)
{
	switch (e)
	{
	case InputDeviceType::KEYBOARD: return "keyboard";
	case InputDeviceType::MOUSE: return "mouse";
	case InputDeviceType::GAMEPAD: return "gamepad";
	case InputDeviceType::TOUCH_SCREEN: return "touch_screen";
	case InputDeviceType::NONE: return "none";
	default: return "unknown";
	}
}
