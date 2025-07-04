#pragma once
#include "Runtime/Camera/Camera.h"
#include "Runtime/Components/InputListener.h"
#include "EditorGUI.h"

class Application;

namespace pine {
	class Editor {
		friend Application;
	public:
		virtual ~Editor() = default;
		Editor();
		void OnUpdate();
		static std::unique_ptr<Editor> Init();
		void Startup();

		[[nodiscard]] Camera* GetCamera() const { return _mainCamera; };
	private:
		void MoveCameraX(float scale) const;
		void MoveCameraY(float scale) const;
		EditorGUI _editorGUI;
		float _moveSpeed = 0.05f;
		Camera* _mainCamera;
		// Input handling methods (prob deprecated)
		void HandleEventlessInput() const;
		void MoveInDirection(glm::vec3 direction) const;
	};
}