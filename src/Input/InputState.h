#pragma once
#include <unordered_map>
#include <unordered_set>
#include "Input/MouseButtons.h"
//#include "Input/InputHandler.h"
#include "Input/InputDevices.h"
#include "Input/KeyCodes.h"

namespace pine
{

	class InputState
	{
	public:
		InputState();
		~InputState();
	private:
		std::unordered_map<KeyCode, InputDeviceState> GetKeyboardState(int index) { return _keyboardState; }
		std::unordered_map<MouseButtons, InputDeviceState> GetMouseState(int index) { return _mouseState; }
		std::unordered_map<int, std::unordered_map<KeyCode, InputDeviceState>>  GetGamepadState(int index) { return _inputGamepadStates; }

		void UpdateKeyboardState(int index, KeyCode key, InputDeviceState state) {
			_keyboardState[key] = state;
		}
		void UpdateMouseState(MouseButtons button, InputDeviceState state) {
			_mouseState[button] = state;
		}
		void UpdateGamepadState(int index, KeyCode key, InputDeviceState state) {
			_inputGamepadStates[index][key] = state;
		}
		
		std::unordered_map<KeyCode, InputDeviceState> _keyboardState{};
		std::unordered_map<MouseButtons, InputDeviceState> _mouseState{};
		std::unordered_map<int, std::unordered_map<KeyCode, InputDeviceState>> _inputGamepadStates{};
	};
}
