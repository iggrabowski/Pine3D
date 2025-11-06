#include "Editor/Editor.h"
#include "Core/Application.h"

namespace pine {
	Editor::Editor()
	{
		// create three editor cameras with slightly different start positions
		_cameras.emplace_back(std::make_unique<Camera>(glm::vec3(2.0f, 2.0f, -5.0f)));
		_cameras.emplace_back(std::make_unique<Camera>(glm::vec3(0.0f, 2.5f, -6.0f)));
		_cameras.emplace_back(std::make_unique<Camera>(glm::vec3(0.0f, 5.0f, -10.0f)));
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
		Application::input_handler->MapInputToAction(KeyCode::A, {
			.name = "editor_camera_strafe_x",
			.type = pine::KEY_ON_HOLD,
			.scale = -1.0f });
		Application::input_handler->MapInputToAction(KeyCode::D, {
			.name = "editor_camera_strafe_x",
			.type = pine::KEY_ON_HOLD,
			.scale = 1.0f });
		Application::input_handler->AddActionCallback("editor_camera_strafe_x",
			pine::InputHandler::ActionCallback {
				.ref = "editor_camera_strafe_x",
				.func = [this](int sourceIndex, float value)
				{
					MoveCameraX(value);
					return true;
				}
			});

		Application::input_handler->MapInputToAction(KeyCode::Q, {
			.name = "editor_camera_strafe_y",
			.type = pine::KEY_ON_HOLD,
			.scale = -1.0f });
		Application::input_handler->MapInputToAction(KeyCode::E, {
			.name = "editor_camera_strafe_y",
			.type = pine::KEY_ON_HOLD,
			.scale = 1.0f });
		Application::input_handler->AddActionCallback("editor_camera_strafe_y",
			pine::InputHandler::ActionCallback {
				.ref = "editor_camera_strafe_y",
				.func = [this](int sourceIndex, float value)
				{
					MoveCameraY(value);
					return true;
				}
			});

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

		// --- Camera switching controls ---
		// Cycle cameras with 'C'
		Application::input_handler->MapInputToAction(KeyCode::C, {
			.name = "editor_camera_cycle",
			.type = pine::KEY_ON_PRESS,
			.scale = 1.0f });
		Application::input_handler->AddActionCallback("editor_camera_cycle",
			pine::InputHandler::ActionCallback {
				.ref = "editor_camera_cycle",
				.func = [this](int sourceIndex, float value)
				{
					CycleCamera();
					return true;
				}
			});

		// Direct select F1/F2/F3
		Application::input_handler->MapInputToAction(KeyCode::F1, {
			.name = "editor_camera_select_0",
			.type = pine::KEY_ON_PRESS,
			.scale = 1.0f });
		Application::input_handler->AddActionCallback("editor_camera_select_0",
			pine::InputHandler::ActionCallback {
				.ref = "editor_camera_select_0",
				.func = [this](int sourceIndex, float value)
				{
					SetActiveCamera(0);
					return true;
				}
			});

		Application::input_handler->MapInputToAction(KeyCode::F2, {
			.name = "editor_camera_select_1",
			.type = pine::KEY_ON_PRESS,
			.scale = 1.0f });
		Application::input_handler->AddActionCallback("editor_camera_select_1",
			pine::InputHandler::ActionCallback {
				.ref = "editor_camera_select_1",
				.func = [this](int sourceIndex, float value)
				{
					SetActiveCamera(1);
					return true;
				}
			});

		Application::input_handler->MapInputToAction(KeyCode::F3, {
			.name = "editor_camera_select_2",
			.type = pine::KEY_ON_PRESS,
			.scale = 1.0f });
		Application::input_handler->AddActionCallback("editor_camera_select_2",
			pine::InputHandler::ActionCallback {
				.ref = "editor_camera_select_2",
				.func = [this](int sourceIndex, float value)
				{
					SetActiveCamera(2);
					return true;
				}
			});
	}

	void Editor::SetAspectRatio(float aspectRatio) const
	{
		// update every camera's projection
		for (const auto& cam : _cameras)
		{
			if (cam) cam->UpdateAspectRatio(aspectRatio);
		}
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

	// Cycle to next camera (wraps)
	void Editor::CycleCamera()
	{
		_activeCameraIndex = (_activeCameraIndex + 1) % static_cast<int>(_cameras.size());
		// inform renderer about the new active camera
		if (Application::renderer) Application::renderer->SetRenderCamera(GetCamera());
	}

	// Select a specific camera index [0..2]
	void Editor::SetActiveCamera(int index)
	{
		if (index < 0 || index >= static_cast<int>(_cameras.size())) return;
		_activeCameraIndex = index;
		if (Application::renderer) Application::renderer->SetRenderCamera(GetCamera());
	}

}