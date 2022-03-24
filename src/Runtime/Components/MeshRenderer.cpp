#pragma once
#include "MeshRenderer.h"
#include "Runtime/Components/Cube.h"
#include "Runtime/Renderer/Renderer.h"

namespace Pine {
	extern UniquePtr<Renderer> renderer;

	MeshRenderer::MeshRenderer()
	{
		m_Transform = new Transform();
		m_Mesh = new Cube();
		m_Material = new Material();
	}

	MeshRenderer::~MeshRenderer() {
		delete m_Material;
		delete m_Transform;
		delete m_Mesh;
	}

	void MeshRenderer::OnUpdate()
	{
		/*m_Transform->UpdateModel();

		m_Material->OnUpdate();

		m_Mesh->Draw();*/

		m_Transform->UpdateModel();

		//m_Material->m_Shader->Bind();
		Mat4 model = m_Transform->GetModel();
		m_Material->m_Shader->SetUniform("Model", model);

		Mat4 MVP = renderer->GetRenderCamera().GetViewProjection() * model;
		m_Material->m_Shader->SetUniform("MVP", MVP);

		Vec3 lightDir(0.5, 0.5, 1.0);
		m_Material->m_Shader->SetUniform("lightDirection", lightDir);

		renderer->Draw(*m_Mesh, *m_Material);
	}

}
