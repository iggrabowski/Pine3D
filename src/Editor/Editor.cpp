#pragma once
#include "Editor/Editor.h"
#include "Core/Application.h"

namespace pine {
	Editor::Editor()
	{
		_mainCamera = new Camera();
	}

	std::unique_ptr<Editor> Editor::Init()
	{
		return std::make_unique<Editor>();
	}

	void Editor::Startup()
	{
		SetKeyBinds();
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

}