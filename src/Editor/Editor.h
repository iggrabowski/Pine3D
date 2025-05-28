#pragma once
#include "Runtime/Camera/Camera.h"
#include "Runtime/Components/InputListener.h"

namespace pine {
	class Editor final : InputListener {
	public:
		virtual ~Editor() = default;
		Editor();
		void OnInputAction(InputType type, int key, KeyAction action) override;
		void OnUpdate();
		static std::unique_ptr<Editor> Init();

		[[nodiscard]] Camera* GetCamera() const { return _mainCamera; };
	private:
		float _moveSpeed = 0.05f;
		Camera* _mainCamera;
		void HandleEventlessInput() const;
		void MoveLeft() const;
		void MoveRight() const;
		void MoveUp() const;
		void MoveDown() const;
		void MoveInDirection(glm::vec3 direction) const;
	};
}