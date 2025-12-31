#pragma once
#include "Runtime/RenderCore/Shader.h"
#include "Runtime/Components/Texture.h"

namespace pine {

	class Material {
	public:
		Material();
		~Material(); // TODO: shaders memory leak
		explicit Material(Shader* shader);
		Material(Shader* shader, Texture* texture);

		void OnUpdate();

		Shader* m_shader = nullptr;
		Texture* m_texture = nullptr;
		// See texture types in Texture.h

		// TODO: use sharepointer?? the textures should be kept in main app and be reusable
		Texture* m_textures[7] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

		float m_roughness = 0.2f;
		float m_metallic = 0.5f;
		bool m_enableNormalMap = false;
		bool m_enableRoughnessMap = false;
		bool m_enableMetallicMap = false;
	};

}