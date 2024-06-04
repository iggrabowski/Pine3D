#pragma once
#include "Runtime/Components/Transform.h"
#include "Runtime/Camera/Camera.h"
#include "Utils/Utils.h"
#include "Core/Window.h"
#include "Core/KeyCodes.h"
#include "Runtime/Components/InputListener.h"
#include <map>

namespace Pine {
	//extern class Application;
	
	class InputHandler {
		//friend class Application;
	public:
		static UniquePtr<InputHandler> Init();

		InputHandler();
		void OnUpdate();

		void Zoom(int delta);
		void ChangeDirection(int x, int y);

		void AddListener(InputListener* listener);
		void RemoveListener(InputListener* listener);

		bool IsKeyPressed(KeyCode keyCode);
		bool IsMouseButtonPressed(MouseButtons mouseCode);

		std::vector<InputListener*>& GetListeners() { return _listeners; };
	private:
		//int _keyStates[99] = {};
		//int _keyStatesPrev[99] = {};
		std::map<KeyCode, bool> _keyStates;
		std::vector<InputListener*> _listeners;
		bool _initialized = false;
		float _zoomPerScroll;
		float _moveSpeed;
		float _directionSpeedX;
		float _directionSpeedY;
	};

}