#pragma once
#include "MeshRenderer.h"

#include "Core/Application.h"
#include "Runtime/Components/Cube.h"
#include "Runtime/Renderer/Renderer.h"

namespace pine {

	MeshRenderer::MeshRenderer()
	{
		_transform = std::make_unique<Transform>();
		//_mesh = new Cube();
		//_material = new Material();
	}

	MeshRenderer::~MeshRenderer() {
	}

	void MeshRenderer::OnUpdate()
	{
		_transform->UpdateModel();

		for (auto& material : _model->materials) {
			material->OnUpdate();

			// shader binding

			material->m_Shader->Bind();
			glm::mat4 model = _transform->GetModel();
			material->m_Shader->SetUniform("Model", model);

			glm::mat4 mvp = Application::renderer->GetRenderCamera().GetViewProjection() * model;
			material->m_Shader->SetUniform("MVP", mvp);

			glm::vec3 light_dir(0.5, 0.5, 1.0);
			material->m_Shader->SetUniform("lightDirection", light_dir);

			// draw call
			Application::renderer->Draw(*_mesh, *material);
		}
	}

}
