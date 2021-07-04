#pragma once
#include "Runtime/Components/Material.h"

namespace Pine {

	Material::Material()
	{
		m_Texture = new Texture("res/epic5.jpg");
		m_Shader = Shader::LoadShader("res/basicShader");
	}

	Material::Material(Shader* shader)
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