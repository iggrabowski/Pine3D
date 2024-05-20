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
		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();

		std::vector<InputListener*> m_Listeners;
		void AddListener(InputListener* listener);
		void RemoveListener(InputListener* listener);
	private:
		//int _keyStates[99] = {};
		//int _keyStatesPrev[99] = {};
		//std::map<unsigned char, void*()> keyMappings;
		bool _initialized = false;
		float _zoomPerScroll;
		float _moveSpeed;
		float _directionSpeedX;
		float _directionSpeedY;
		
		void MoveInDirection(glm::vec3 direction);
	};

}