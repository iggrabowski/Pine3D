#include "Editor/Editor.h"
#include "Core/Application.h"

namespace pine {
	Editor::Editor()
	{
		_camera = std::make_unique<Camera>(glm::vec3(2.0f, 2.0f, -5.0f));
		_activeCameraIndex = 0;
	}

	std::unique_ptr<Editor> Editor::Init()
	{
		return std::make_unique<Editor>();
	}

	void Editor::Startup()
	{
		SetKeyBinds();
		//_editorGui->Startup();
	}

	void Editor::SetKeyBinds()
	{
		//Application::input_handler->MapInputToAction(KeyCode::A, {
		//	.name = "editor_camera_strafe_x",
		//	.type = pine::KEY_ON_HOLD,
		//	.scale = -1.0f });
		//Application::input_handler->MapInputToAction(KeyCode::D, {
		//	.name = "editor_camera_strafe_x",
		//	.type = pine::KEY_ON_HOLD,
		//	.scale = 1.0f });
		//Application::input_handler->AddActionCallback("editor_camera_strafe_x",
		//	pine::InputHandler::ActionCallback {
		//		.ref = "editor_camera_strafe_x",
		//		.func = [this](int sourceIndex, float value)
		//		{
		//			MoveCameraX(value);
		//			return true;
		//		}
		//	});

		//Application::input_handler->MapInputToAction(KeyCode::Q, {
		//	.name = "editor_camera_strafe_y",
		//	.type = pine::KEY_ON_HOLD,
		//	.scale = -1.0f });
		//Application::input_handler->MapInputToAction(KeyCode::E, {
		//	.name = "editor_camera_strafe_y",
		//	.type = pine::KEY_ON_HOLD,
		//	.scale = 1.0f });
		//Application::input_handler->AddActionCallback("editor_camera_strafe_y",
		//	pine::InputHandler::ActionCallback {
		//		.ref = "editor_camera_strafe_y",
		//		.func = [this](int sourceIndex, float value)
		//		{
		//			MoveCameraY(value);
		//			return true;
		//		}
		//	});

		Application::input_handler->MapInputToAction(KeyCode::S, {
			.name = "editor_camera_strafe_z",
			.type = pine::KEY_ON_HOLD,
			.scale = -1.0f });
		Application::input_handler->MapInputToAction(KeyCode::W, {
			.name = "editor_camera_strafe_z",
			.type = pine::KEY_ON_HOLD,
			.scale = 1.0f });
		Application::input_handler->AddActionCallback("editor_camera_strafe_z",
			pine::InputHandler::ActionCallback {
				.ref = "editor_camera_strafe_z",
				.func = [this](int sourceIndex, float value)
				{
					MoveCameraZ(value);
					return true;
				}
			});

		Application::input_handler->MapInputToAction(KeyCode::MB_BUTTON_RIGHT, {
			.name = "editor_camera_rotate",
			.type = pine::KEY_ON_RELEASE,
			.scale = -1.0f });
		Application::input_handler->MapInputToAction(KeyCode::MB_BUTTON_RIGHT, {
			.name = "editor_camera_rotate",
			.type = pine::KEY_ON_HOLD,
			.scale = 1.0f });
		Application::input_handler->AddActionCallback("editor_camera_rotate",
			pine::InputHandler::ActionCallback {
				.ref = "editor_camera_rotate",
				.func = [this](int sourceIndex, float value)
				{
					// get raw mouse motion
					std::pair<float, float> mousePos = Application::input_handler->GetCurrentMousePosition();
					std::pair<float, float> lastMousePos = Application::input_handler->GetLastMousePosition();

					float rotX = mousePos.first - lastMousePos.first;
					float rotY = mousePos.second - lastMousePos.second;
					GetCamera()->Rotate(EDITOR_CAMERA_MOVE_SPEED * -rotX, glm::vec3(0.0f, 1.0f,0.0f));
					GetCamera()->Rotate(EDITOR_CAMERA_MOVE_SPEED * -rotY, glm::cross(GetCamera()->GetDirection(), GetCamera()->up));
					Application::window->SetCursorDisabled(value);
					Application::input_handler->UpdateMousePosition(0, mousePos.first, mousePos.second);
					return true;
				}
			});

		// --- Light preset switching controls ---
		// Cycle light presets with 'C'
		Application::input_handler->MapInputToAction(KeyCode::C, {
			.name = "editor_light_cycle",
			.type = pine::KEY_ON_PRESS,
			.scale = 1.0f });
		Application::input_handler->AddActionCallback("editor_light_cycle",
			pine::InputHandler::ActionCallback {
				.ref = "editor_light_cycle",
				.func = [this](int sourceIndex, float value)
				{
					CycleLightPreset();
					return true;
				}
			});

		// Direct select light presets with F1/F2/F3
		Application::input_handler->MapInputToAction(KeyCode::F1, {
			.name = "editor_light_select_0",
			.type = pine::KEY_ON_PRESS,
			.scale = 1.0f });
		Application::input_handler->AddActionCallback("editor_light_select_0",
			pine::InputHandler::ActionCallback {
				.ref = "editor_light_select_0",
				.func = [this](int sourceIndex, float value)
				{
					SetActiveLightPreset(0);
					return true;
				}
			});

		Application::input_handler->MapInputToAction(KeyCode::F2, {
			.name = "editor_light_select_1",
			.type = pine::KEY_ON_PRESS,
			.scale = 1.0f });
		Application::input_handler->AddActionCallback("editor_light_select_1",
			pine::InputHandler::ActionCallback {
				.ref = "editor_light_select_1",
				.func = [this](int sourceIndex, float value)
				{
					SetActiveLightPreset(1);
					return true;
				}
			});

		Application::input_handler->MapInputToAction(KeyCode::F3, {
			.name = "editor_light_select_2",
			.type = pine::KEY_ON_PRESS,
			.scale = 1.0f });
		Application::input_handler->AddActionCallback("editor_light_select_2",
			pine::InputHandler::ActionCallback {
				.ref = "editor_light_select_2",
				.func = [this](int sourceIndex, float value)
				{
					SetActiveLightPreset(2);
					return true;
				}
			});
	}

	void Editor::SetAspectRatio(float aspectRatio) const
	{
		// update every camera's projection
			if (_camera) _camera->UpdateAspectRatio(aspectRatio);
	}

	void Editor::HandleEventlessInput() const
	{
		/*if (Application::input_handler->IsKeyPressed(KeyCode::A))
			MoveLeft();
		if (Application::input_handler->IsKeyPressed(KeyCode::D))
			MoveRight();
		if (Application::input_handler->IsKeyPressed(KeyCode::W))
			MoveUp();
		if (Application::input_handler->IsKeyPressed(KeyCode::S))
			MoveDown();*/
	}

	void Editor::OnUpdate()
	{
		HandleEventlessInput();
	}

	void Editor::MoveCameraX(const float scale) const
	{
		glm::vec3 moveDir = scale * glm::normalize(
			glm::cross(Application::renderer->GetRenderCamera().GetDirection(), Application::renderer->GetRenderCamera().up)
		);
		MoveInDirection(moveDir);
	}

	void Editor::MoveCameraY(const float scale) const
	{
		MoveInDirection(scale * Application::renderer->GetRenderCamera().up);
	}

	void Editor::MoveCameraZ(const float scale) const
	{
		MoveInDirection(scale * Application::renderer->GetRenderCamera().GetDirection());
	}

	void Editor::MoveInDirection(glm::vec3 direction) const
	{
		Camera& camera = Application::renderer->GetRenderCamera();
		glm::vec3 pos = camera.GetPos();

		camera.SetPos(pos + direction * _moveSpeed);
	}

	// Cycle to next light preset (wraps). Editor keeps the logic, active index is stored in Application.
	void Editor::CycleLightPreset()
	{
		if (Application::light_presets.empty())
			return;

		Application::activeLightPresetIndex = (Application::activeLightPresetIndex + 1) % static_cast<int>(Application::light_presets.size());

		// apply the chosen preset to the active lights list
		Application::lights = Application::light_presets[Application::activeLightPresetIndex];
	}

	// Select a specific light preset index
	void Editor::SetActiveLightPreset(int index)
	{
		if (index < 0 || index >= static_cast<int>(Application::light_presets.size()))
			return;

		Application::activeLightPresetIndex = index;
		Application::lights = Application::light_presets[Application::activeLightPresetIndex];
	}
}