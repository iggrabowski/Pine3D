#pragma once
#include "Runtime/Components/Transform.h"
#include "Runtime/Camera/Camera.h"
#include "Utils/Utils.h"
#include "Core/Window.h"

#include <Windows.h>
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
		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();
	private:
		unsigned char _keyStates[256] = {};
		unsigned char _prevKeyStates[256] = {};

		//std::map<unsigned char, void*()> keyMappings;

		float _zoomPerScroll;
		float _moveSpeed;
		float _directionSpeedX;
		float _directionSpeedY;
		
		void MoveInDirection(glm::vec3 direction);
	};

}