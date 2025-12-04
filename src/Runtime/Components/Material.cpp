#pragma once
#include "Runtime/Components/Material.h"

namespace pine {

	Material::Material()
	{
		// Load default texture files from file
		Image img("../res/textures/default.jpg");
		// Load default shaders
		m_Shader = Shader::LoadShaders("../res/shaders/PBR");

		m_Texture = new Texture();
		m_Texture->LoadFromImage(img);
	}

	Material::Material(Shader* shader): m_Texture(nullptr)
	{
		m_Shader = shader;
	}

	Material::Material(Shader* shader, Texture* texture)
	{
		m_Shader = shader;
		m_Texture = texture;
	}

	void Material::OnUpdate()
	{
		//m_Shader->Bind();

		//m_Shader->Update(*m_Transform);
	}

}