#pragma once
#include "MeshRenderer.h"

#include "Core/Application.h"
#include "Runtime/Components/Cube.h"
//#include "Runtime/Renderer/Renderer.h"

namespace pine {

	MeshRenderer::MeshRenderer()
	{
		_transform = std::make_unique<Transform>();
		_model3D = new Model3D();
		//_mesh = new Cube();
		//_material = new Material();
	}

	MeshRenderer::~MeshRenderer() {
	}

	void MeshRenderer::ResetModel3D()
	{
		delete _model3D;
		_model3D = new Model3D();
	}

	void MeshRenderer::OnUpdate()
	{
		_transform->UpdateModel();

		// PBR shader uniforms
	//	for (auto& basic_mesh : _model3D->b_meshes) {
			//Material* material = _model3D->materials[basic_mesh.materialIndex];
			//_model->materials[basic_mesh.MaterialIndex]->OnUpdate();

			// shader binding
			//glm::vec3 light_dir(0.5, 0.5, 1.0);
			//material->m_Shader->SetUniform("lightDirection", light_dir);

			// draw call
			Application::renderer->Draw(this);
	//	}
	}

	bool MeshRenderer::InitModel()
	{
		GetModel()->mesh.InitMesh();
		m_render_flags.reserve(_model3D->num_materials);
		for (unsigned int i = 0; i < _model3D->num_materials; i++) {
			m_render_flags.push_back(0);
			if (_model3D->materials[i]->m_textures[TEX_TYPE_BASE] != nullptr)
				m_render_flags[i] |= static_cast<uint32_t>(RENDER_FLAGS::BASE_TEXTURE);
			if (_model3D->materials[i]->m_textures[TEX_TYPE_NORMAL] != nullptr) 
				m_render_flags[i] |= static_cast<uint32_t>(RENDER_FLAGS::NORMAL_MAPS);
			if (_model3D->materials[i]->m_textures[TEX_TYPE_ROUGHNESS] != nullptr)
				m_render_flags[i] |= static_cast<uint32_t>(RENDER_FLAGS::ROUGHNESS_MAPS);
		}
		return true;
	}
}
