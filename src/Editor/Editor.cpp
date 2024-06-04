#pragma once
#include "Editor/Editor.h"
#include "Core/Application.h"

namespace Pine {
	Editor::Editor()
	{
		_mainCamera = new Camera();
	}
	void Editor::OnInputAction(InputType type, int key, KeyAction action)
	{
		
	}

	std::unique_ptr<Editor> Editor::Init()
	{
		return std::unique_ptr<Editor>(new Editor());
	}
	void Editor::HandleEventlessInput()
	{
		if (inputHandler->IsKeyPressed(KeyCode::A))
			MoveLeft();
		if (inputHandler->IsKeyPressed(KeyCode::D))
			MoveRight();
		if (inputHandler->IsKeyPressed(KeyCode::W))
			MoveUp();
		if (inputHandler->IsKeyPressed(KeyCode::S))
			MoveDown();
	}

	void Editor::OnUpdate()
	{
		HandleEventlessInput();
	}

	void Editor::MoveLeft()
	{
		glm::vec3 moveDir = -glm::normalize(
			Cross(renderer->GetRenderCamera().GetDirection(), renderer->GetRenderCamera().up)
		);
		MoveInDirection(moveDir);
	}

	void Editor::MoveRight()
	{
		glm::vec3 moveDir = glm::normalize(
			Cross(renderer->GetRenderCamera().GetDirection(), renderer->GetRenderCamera().up)
		);
		MoveInDirection(moveDir);
	}

	void Editor::MoveUp()
	{
		MoveInDirection(renderer->GetRenderCamera().up);
	}

	void Editor::MoveDown()
	{
		MoveInDirection(-renderer->GetRenderCamera().up);
	}


	void Editor::MoveInDirection(glm::vec3 direction)
	{
		Camera& camera = renderer->GetRenderCamera();
		glm::vec3 pos = camera.GetPos();

		camera.SetPos(pos + direction * _moveSpeed);
	}


}