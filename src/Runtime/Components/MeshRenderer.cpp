#pragma once
#include "MeshRenderer.h"
#include "Runtime/Components/Cube.h"
#include "Runtime/Renderer/Renderer.h"

namespace Pine {
	extern UniquePtr<Renderer> renderer;

	MeshRenderer::MeshRenderer()
	{
		m_Transform = new Transform();
		_mesh = new Cube();
		_material = new Material();
	}

	MeshRenderer::~MeshRenderer() {
		delete _material;
		delete m_Transform;
		delete _mesh;
	}

	void MeshRenderer::OnUpdate()
	{
		m_Transform->UpdateModel();

		_material->OnUpdate();

		//m_Mesh->Draw();

		m_Transform->UpdateModel();

		_material->m_Shader->Bind();
		glm::mat4 model = m_Transform->GetModel();
		_material->m_Shader->SetUniform("Model", model);

		glm::mat4 MVP = renderer->GetRenderCamera().GetViewProjection() * model;
		_material->m_Shader->SetUniform("MVP", MVP);

		glm::vec3 lightDir(0.5, 0.5, 1.0);
		_material->m_Shader->SetUniform("lightDirection", lightDir);

		renderer->Draw(*_mesh, *_material);
	}

}
