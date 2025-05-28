#pragma once
#include "Editor/Editor.h"
#include "Core/Application.h"

namespace pine {
	Editor::Editor()
	{
		_mainCamera = new Camera();
	}
	void Editor::OnInputAction(InputType type, const int key, KeyAction action)
	{
		switch (key)
		{
		case KeyCode::A:
			MoveLeft();
			break;
		case KeyCode::D:
			MoveRight();
			break;
		case KeyCode::W:
			MoveUp();
			break;
		case KeyCode::S:
			MoveDown();
			break;
		default:
			break;
		}
	}

	std::unique_ptr<Editor> Editor::Init()
	{
		return std::make_unique<Editor>();
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

	void Editor::MoveLeft() const
	{
		glm::vec3 moveDir = -glm::normalize(
			glm::cross(Application::renderer->GetRenderCamera().GetDirection(), Application::renderer->GetRenderCamera().up)
		);
		MoveInDirection(moveDir);
	}

	void Editor::MoveRight() const
	{
		glm::vec3 moveDir = glm::normalize(
			glm::cross(Application::renderer->GetRenderCamera().GetDirection(), Application::renderer->GetRenderCamera().up)
		);
		MoveInDirection(moveDir);
	}

	void Editor::MoveUp() const
	{
		MoveInDirection(Application::renderer->GetRenderCamera().up);
	}

	void Editor::MoveDown() const
	{
		MoveInDirection(-Application::renderer->GetRenderCamera().up);
	}

	void Editor::MoveInDirection(glm::vec3 direction) const
	{
		Camera& camera = Application::renderer->GetRenderCamera();
		glm::vec3 pos = camera.GetPos();

		camera.SetPos(pos + direction * _moveSpeed);
	}

}