#pragma once
#include "Runtime/Components/Material.h"

namespace Pine {

	Material::Material()
	{
		m_Texture = nullptr;
		m_Shader = Shader::LoadShader("res/shaders/default");
	}

	Material::Material(Shader* shader)
	{
		m_Texture = nullptr;
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