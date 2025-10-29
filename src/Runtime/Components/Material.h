#pragma once
#include "Runtime/RenderCore/Shader.h"
#include "Runtime/Components/Texture.h"

namespace pine {

	class Material {
	public:
		Material();
		explicit Material(Shader* shader);
		Material(Shader* shader, Texture* texture);

		void OnUpdate();

		Shader* m_Shader = nullptr;
		Texture* m_Texture = nullptr;
		// See texture types in Texture.h
		Texture* m_Textures[6] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	};

}