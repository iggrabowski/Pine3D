#pragma once
#include "Runtime/RenderCore/Shader.h"
#include "Runtime/Components/Texture.h"

namespace pine {

	class Material {
	public:
		Material();
		~Material() { delete m_Shader;  };
		explicit Material(Shader* shader);
		Material(Shader* shader, Texture* texture);

		void OnUpdate();

		Shader* m_Shader = nullptr;
		Texture* m_Texture = nullptr;
		// See texture types in Texture.h

		// TODO: use sharepointer?? the textures should be kept in main app and be reusable
		Texture* m_Textures[7] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

		float m_roughness = 0.2f;
	};

}