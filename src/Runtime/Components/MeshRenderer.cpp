#pragma once
#include "MeshRenderer.h"

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
		if (!_dataIsBuffered)
		{
			InitModel();
			_dataIsBuffered = true;
		}
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
		//GetModel()->mesh.InitMesh();
		if (!_shadersValidated)
			if (!ValidateShaderAttributes()) return false;

		Application::renderer->BufferModelMesh(GetModel());
		m_render_flags.reserve(_model3D->num_materials);

		// init render flags based on available textures in materials
		for (unsigned int i = 0; i < _model3D->num_materials; i++) {
			m_render_flags.push_back(0);
			if (_model3D->materials[i]->m_textures[TEX_TYPE_BASE] != nullptr)
				m_render_flags[i] |= static_cast<uint32_t>(RENDER_FLAGS::BASE_TEXTURE);
			if (_model3D->materials[i]->m_textures[TEX_TYPE_NORMAL] != nullptr) {
				m_render_flags[i] |= static_cast<uint32_t>(RENDER_FLAGS::NORMAL_MAPS);
				_model3D->materials[i]->m_enableNormalMap = true;
			}
			if (_model3D->materials[i]->m_textures[TEX_TYPE_ROUGHNESS] != nullptr) {
				m_render_flags[i] |= static_cast<uint32_t>(RENDER_FLAGS::ROUGHNESS_MAPS);
				_model3D->materials[i]->m_enableRoughnessMap = true;
			}
			if (_model3D->materials[i]->m_textures[TEX_TYPE_METALLIC] != nullptr) {
				m_render_flags[i] |= static_cast<uint32_t>(RENDER_FLAGS::METALNESS_MAPS);
				_model3D->materials[i]->m_enableMetallicMap = true;
			}
		}
		return true;
	}

	bool MeshRenderer::ValidateShaderAttributes()
	{
		// Map attribute location -> ShaderVariable*

		for (unsigned int i = 0; i < _model3D->num_materials; i++) {
			const Material* mat = _model3D->materials[i];
			if (!mat) {
				Logger::Instance().Error("MeshRenderer: Material " + std::to_string(i) + " - missing material.");
				return false;
			}
			const Shader* shader = mat->m_shader;
			if (shader == nullptr) {
				Logger::Instance().Error("MeshRenderer: Material " + std::to_string(i) + " - missing shader.");
				return false;
			}

			const auto& attrs = shader->GetAttributes();
			for (const auto& attr : attrs) {
				// Check by location: if another attribute already uses this location it must match name+type
				auto it_loc = loc_map.find(attr.loc);
				if (it_loc != loc_map.end()) {
					const ShaderVariable* existing = it_loc->second;
					if (existing->name != attr.name || existing->type != attr.type) {
						Logger::Instance().Error("MeshRenderer: Attribute conflict"
							   " at location " + std::to_string(attr.loc) +
							". Existing: '" + existing->name + "' (type " + std::to_string(existing->type) +
							"), Found: '" + attr.name + "' (type " + std::to_string(attr.type) + ").");
						return false;
					}
				} else {
					loc_map[attr.loc] = &attr;
				}

				auto it_name = name_map.find(attr.name);
				if (it_name != name_map.end()) {
					const ShaderVariable* existing = it_name->second;
					if (existing->loc != attr.loc || existing->type != attr.type) {
						Logger::Instance().Error("MeshRenderer: Attribute conflict for name '" + attr.name +
							"'. Existing: location " + std::to_string(existing->loc) + " (type " + std::to_string(existing->type) +
							"), Found: location " + std::to_string(attr.loc) + " (type " + std::to_string(attr.type) + ").");
						return false;
					}
				} else {
					name_map[attr.name] = &attr;
				}
			}
		}
		_shadersValidated = true;
		return true;
	}
}