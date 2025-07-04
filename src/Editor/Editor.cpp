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
		Application::input_handler->MapInputToAction(A, {
			.name = "editor_camera_strafe_x",
			.type = pine::KEY_ON_HOLD,
			.scale = -1.0f });
		Application::input_handler->MapInputToAction(D, {
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

		Application::input_handler->MapInputToAction(S, {
			.name = "editor_camera_strafe_y",
			.type = pine::KEY_ON_HOLD,
			.scale = -1.0f });
		Application::input_handler->MapInputToAction(W, {
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

	void Editor::MoveInDirection(glm::vec3 direction) const
	{
		Camera& camera = Application::renderer->GetRenderCamera();
		glm::vec3 pos = camera.GetPos();

		camera.SetPos(pos + direction * _moveSpeed);
	}

}