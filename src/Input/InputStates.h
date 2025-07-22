#pragma once
#include <unordered_map>
#include <unordered_set>
#include "Input/MouseButtons.h"
//#include "Input/InputHandler.h"
#include "Input/InputDevices.h"
#include "Input/KeyCodes.h"

namespace pine
{

	class InputStates
	{
	public:
		InputStates();
		~InputStates();
	private:
	public:
		[[nodiscard]] std::unordered_map<KeyCode, InputDeviceState> GetKeyboardState() { return _keyboardState; }
		[[nodiscard]] std::unordered_map<KeyCode, InputDeviceState> GetMouseState() { return _mouseState; }
		[[nodiscard]] std::pair<float, float> GetCurrentMousePosition() const { return _currentMousePosition; }
		[[nodiscard]] std::pair<float, float> GetLastMousePosition() const { return _lastMousePosition; }
		[[nodiscard]] std::unordered_map<int, std::unordered_map<KeyCode, InputDeviceState>>  GetGamepadState() { return _inputGamepadStates; }
		
		void UpdateKeyboardState(int index, KeyCode key, InputDeviceState state) {
			_keyboardState[key] = state;
		}
		void UpdateMouseState(int index, KeyCode button, InputDeviceState state) {
			_mouseState[button] = state;
		}
		void UpdateMousePosition(int index, float x, float y) {
			_lastMousePosition = _currentMousePosition;
			_currentMousePosition = { x, y };
		}
		void UpdateGamepadState(int index, KeyCode key, InputDeviceState state) {
			_inputGamepadStates[index][key] = state;
		}
	private:	
		std::pair<float, float> _currentMousePosition{ 0.0f, 0.0f };
		std::pair<float, float> _lastMousePosition{ 0.0f, 0.0f };
		std::unordered_map<KeyCode, InputDeviceState> _keyboardState{};
		std::unordered_map<KeyCode, InputDeviceState> _mouseState{};
		std::unordered_map<int, std::unordered_map<KeyCode, InputDeviceState>> _inputGamepadStates{};
	};
}
