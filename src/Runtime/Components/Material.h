#pragma once
#include "Runtime/RenderCore/Shader.h"
#include "Runtime/Components/Texture.h"

namespace Pine {

	class Material {
	public:
		Material();
		Material(Shader* shader);
		Material(Shader* shader, Texture* texture);

		void OnUpdate();

		Shader* m_Shader;
		Texture* m_Texture;
	};

}