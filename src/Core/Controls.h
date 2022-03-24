#pragma once
#include "Runtime/Components/Transform.h"
#include "Runtime/Camera/Camera.h"
#include "Utils/Utils.h"
#include "Core/Window.h"

namespace Pine {

	//extern class Application;

	class Controls {
		//friend class Application;
	public:
		static UniquePtr<Controls> Init();

		Controls();
		void OnUpdate();

		void Zoom(int delta);
		void ChangeDirection(int x, int y);
		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();
	private:
		float m_ZoomPerScroll;
		float m_MoveSpeed;
		float m_directionSpeedX;
		float m_directionSpeedY;
		
		void MoveInDirection(Vec3 direction);
	};

}