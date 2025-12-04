#pragma once
#include "MeshRenderer.h"

#include "Core/Application.h"
#include "Runtime/Components/Cube.h"
#include "Runtime/Renderer/Renderer.h"

namespace pine {

	MeshRenderer::MeshRenderer()
	{
		_transform = std::make_unique<Transform>();
		_model = new Model();
		//_mesh = new Cube();
		//_material = new Material();
	}

	MeshRenderer::~MeshRenderer() {
	}

	void MeshRenderer::OnUpdate()
	{
		_transform->UpdateModel();

		// PBR shader uniforms
		for (auto& basic_mesh : _model->b_meshes) {
			Material* material = _model->materials[basic_mesh.materialIndex];
			//_model->materials[basic_mesh.MaterialIndex]->OnUpdate();

			// shader binding
			//glm::vec3 light_dir(0.5, 0.5, 1.0);
			//material->m_Shader->SetUniform("lightDirection", light_dir);

			// draw call
			Application::renderer->Draw(this);
		}
	}

}
