#pragma once
#include "MeshRenderer.h"

#include "Core/Application.h"
#include "Runtime/Components/Cube.h"
#include "Runtime/Renderer/Renderer.h"

namespace pine {

	MeshRenderer::MeshRenderer()
	{
		_transform = new Transform();
		_mesh = new Cube();
		_material = new Material();
	}

	MeshRenderer::~MeshRenderer() {
		delete _material;
		delete _transform;
		delete _mesh;
	}

	void MeshRenderer::OnUpdate()
	{
		_transform->UpdateModel();

		_material->OnUpdate();

		//m_Mesh->Draw();

		_transform->UpdateModel();

		_material->m_Shader->Bind();
		glm::mat4 model = _transform->GetModel();
		_material->m_Shader->SetUniform("Model", model);

		glm::mat4 mvp = Application::renderer->GetRenderCamera().GetViewProjection() * model;
		_material->m_Shader->SetUniform("MVP", mvp);

		glm::vec3 light_dir(0.5, 0.5, 1.0);
		_material->m_Shader->SetUniform("lightDirection", light_dir);

		Application::renderer->Draw(*_mesh, *_material);
	}

}
