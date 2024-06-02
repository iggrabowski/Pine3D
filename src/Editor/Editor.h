#pragma once
#include "Runtime/Camera/Camera.h"
#include "Runtime/Components/InputListener.h"

namespace Pine {
	class Editor : InputListener {
	public: 
		Editor();
		void OnInputAction(InputType type, KeyCode key, KeyAction action) override;
		void OnUpdate();
		static std::unique_ptr<Editor> Init();

		Camera* GetCamera() { return _mainCamera; };
	private:
		float _moveSpeed = 0.05f;
		Camera* _mainCamera;
		void HandleEventlessInput();

		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();

		void MoveInDirection(glm::vec3 direction);
	};
}