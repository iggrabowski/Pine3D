#pragma once
#include "Runtime/Camera/Camera.h"
#include "Runtime/Components/InputListener.h"

#define EDITOR_CAMERA_MOVE_SPEED 0.45f

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
		void SetKeyBinds();
		void SetAspectRatio(float aspectRatio) const;

		[[nodiscard]] Camera* GetCamera() const { return _camera.get(); }

		// Camera switching (kept for camera selection) -- replaced by light-preset cycling API
		void CycleLightPreset();
		void SetActiveLightPreset(int index);

	private:
		void MoveCameraX(float scale) const;
		void MoveCameraY(float scale) const;
		void MoveCameraZ(float scale) const;
		float _moveSpeed = 0.05f;

		// three editor cameras; the active one is returned by GetCamera()
		std::unique_ptr<Camera> _camera;
		// local index used only for GetCamera() indexing; camera active index remains local to the editor cameras
		int _activeCameraIndex = 0;

		// Input handling methods (prob deprecated)
		void HandleEventlessInput() const;
		void MoveInDirection(glm::vec3 direction) const;
	};
}