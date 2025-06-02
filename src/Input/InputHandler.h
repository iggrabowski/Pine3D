// Input mapping implementation based on work by Ozzadar Dev on YouTube
// https://www.youtube.com/watch?v=Ms9metbS2lU

#pragma once
#include "Utils/Utils.h"
#include "Runtime/Components/InputListener.h"
#include "Input/InputStates.h"
//#include "Input/InputDevices.h"
#include <unordered_map>
#include <unordered_set>
#include <functional>

namespace pine {
	//extern class Application;

	struct InputAction
	{
		std::string name;
		KeyActionType type;
		float scale = 1.0f;
	};
	
	class InputHandler {
		//friend class Application;
	public:
		using ActionCallbackFunc = std::function<bool(int, float)>;
		struct ActionCallback {
			std::string ref;
			ActionCallbackFunc func;
		};
		static UniquePtr<InputHandler> Init();
		InputHandler();
		~InputHandler();
		void OnUpdate();
		void Zoom(int delta) const;
		void ChangeDirection(int xPosition, int yPosition);
		void AddListener(InputListener* listener);
		void RemoveListener(const InputListener* listener);
		void AddActionCallback(const std::string& actionName, const ActionCallback& callback);
		void RemoveActionCallback(const std::string& actionName, const std::string& callbackRef);
		void MapInputToAction(KeyCode key, const InputAction& inputAction);
		void UnmapInputFromAction(KeyCode key, const std::string& action);
		void ProcessInput();
		void RegisterDevice(const std::shared_ptr<InputDevice>& device);
		bool IsMouseButtonPressed(MouseButtons mouseCode);
		std::vector<InputListener*>& GetListeners()
		{
			return _listeners;
		}
		void UpdateKeyboardState(int index, KeyCode key, InputDeviceState state) {
			_inputState.UpdateKeyboardState(index, key, state);
		}
		void UpdateMouseState(int index, KeyCode button, InputDeviceState state) {
			_inputState.UpdateMouseState(index, button, state);
		}
		void UpdateGamepadState(int index, KeyCode key, InputDeviceState state) {
			_inputState.UpdateGamepadState(index, key, state);
		}
		std::unordered_map<KeyCode, InputDeviceState> GetMouseState()
		{
			return _inputState.GetMouseState();
		}
		std::unordered_map<KeyCode, InputDeviceState> GetKeyboardState()
		{
			return _inputState.GetKeyboardState();
		}
		std::unordered_map<int, std::unordered_map<KeyCode, InputDeviceState>> GetGamepadState(int index)
		{
			return _inputState.GetGamepadState();
		}

	private:
		struct ActionEvent
		{
			int device_index;
			float new_value;
			std::string action_name;
		};
		bool IsKeyPressed(KeyCode keyCode);
		std::vector<ActionEvent> GenerateActionEvent(int deviceIndex, KeyCode keyCode, float oldVal, float newVal);
		void PropagateActionEvent(const ActionEvent& actionEvent);
		void UnregisterDevice(int deviceIndex, InputDeviceType type);
		//int _keyStates[99] = {};
		//int _keyStatesPrev[99] = {};
		std::unordered_map<KeyCode, std::vector<InputAction>> _inputActionMapping;
		std::unordered_map<std::string, std::vector<ActionCallback>> _actionCallbacks;
		std::vector<InputListener*> _listeners;
		std::vector<std::shared_ptr<InputDevice>> _inputDevices;
		//bool _initialized = false;
		float _moveSpeed;
		float _zoomPerScroll;
		float _directionSpeedX;
		float _directionSpeedY;

		InputStates _inputState;
	};
	
}
