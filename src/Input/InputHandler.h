// Input mapping implementation based on work by Ozzadar Dev on YouTube
// https://www.youtube.com/watch?v=Ms9metbS2lU

#pragma once
#include "Utils/Utils.h"
#include "Runtime/Components/InputListener.h"
#include "Input/InputState.h"
//#include "Input/InputDevices.h"
#include <unordered_map>
#include <unordered_set>
#include <functional>

namespace pine {
	//extern class Application;
	
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
		void MapInputToAction(KeyCode key, const std::string& action);
		void UnmapInputFromAction(KeyCode key, const std::string& action);
		void ProcessInput();
		bool IsMouseButtonPressed(MouseButtons mouseCode);
		std::vector<InputListener*>& GetListeners()
		{
			return _listeners;
		}

	private:
		struct ActionEvent
		{
			int device_index;
			float new_value;
			std::string action_name;
		};
		bool IsKeyPressed(KeyCode keyCode);
		std::vector<ActionEvent> GenerateActionEvent(int deviceIndex, KeyCode keyCode, float newVal);
		void PropagateActionEvent(const ActionEvent& actionEvent);
		void RegisterDevice(InputDevice device);
		void UnregisterDevice(int deviceIndex, InputDeviceType type);
		//int _keyStates[99] = {};
		//int _keyStatesPrev[99] = {};
		std::unordered_map<KeyCode, std::unordered_set<std::string>> _inputActionMapping;
		std::unordered_map<std::string, std::vector<ActionCallback>> _actionCallbacks;
		std::vector<InputListener*> _listeners;
		std::vector<InputDevice> _inputDevices;
		//bool _initialized = false;
		float _moveSpeed;
		float _zoomPerScroll;
		float _directionSpeedX;
		float _directionSpeedY;

		InputState _inputState;
	};
	
}
