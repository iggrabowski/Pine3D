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
		std::unordered_map<KeyCode, InputDeviceState> GetKeyboardState() { return _keyboardState; }
		std::unordered_map<KeyCode, InputDeviceState> GetMouseState() { return _mouseState; }
		std::unordered_map<int, std::unordered_map<KeyCode, InputDeviceState>>  GetGamepadState() { return _inputGamepadStates; }
		
		void UpdateKeyboardState(int index, KeyCode key, InputDeviceState state) {
			_keyboardState[key] = state;
		}
		void UpdateMouseState(int index, KeyCode button, InputDeviceState state) {
			_mouseState[button] = state;
		}
		void UpdateGamepadState(int index, KeyCode key, InputDeviceState state) {
			_inputGamepadStates[index][key] = state;
		}
	private:	
		std::unordered_map<KeyCode, InputDeviceState> _keyboardState{};
		std::unordered_map<KeyCode, InputDeviceState> _mouseState{};
		std::unordered_map<int, std::unordered_map<KeyCode, InputDeviceState>> _inputGamepadStates{};
	};
}
