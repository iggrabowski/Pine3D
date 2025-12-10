#pragma once
#include "Runtime/Components/Material.h"

namespace pine {

	Material::Material()
	{
		// Load default texture files from file
		Image img("../res/textures/default.jpg");
		// Load default shaders
		m_shader = Shader::LoadShaders("../res/shaders/PBR");

		m_texture = new Texture();
		m_texture->LoadFromImage(img);
	}

	Material::Material(Shader* shader): m_texture(nullptr)
	{
		m_shader = shader;
	}

	Material::Material(Shader* shader, Texture* texture)
	{
		m_shader = shader;
		m_texture = texture;
	}

	void Material::OnUpdate()
	{
		//m_Shader->Bind();

		//m_Shader->Update(*m_Transform);
	}

}