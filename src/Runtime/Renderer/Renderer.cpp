#pragma once
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace pine {

	//Renderer* Renderer::s_Instance = nullptr;
	
	Camera& Renderer::GetRenderCamera() const
	{
		return *_camera;
	}

	void Renderer::UpdateRenderFlags(MeshRenderer* mr)
	{
		// update render flags based on available textures in materials
		for (unsigned int i = 0; i < mr->GetModel()->num_materials; i++) {
			mr->m_render_flags[i] = 0;
			unsigned int* flags = &mr->m_render_flags[i];
			auto mat = mr->GetModel()->materials[i];

			if (mat->m_textures[TEX_TYPE_BASE] != nullptr)
				*flags |= static_cast<uint32_t>(RENDER_FLAGS::BASE_TEXTURE);
			if (mat->m_textures[TEX_TYPE_NORMAL] != nullptr) {
				if (mat->m_enableNormalMap)
					*flags |= static_cast<uint32_t>(RENDER_FLAGS::NORMAL_MAPS);
				else
					*flags -= *flags & static_cast<uint32_t>(RENDER_FLAGS::NORMAL_MAPS);
			}
			if (mat->m_textures[TEX_TYPE_ROUGHNESS] != nullptr) {
				if (mat->m_enableRoughnessMap)
					*flags |= static_cast<uint32_t>(RENDER_FLAGS::ROUGHNESS_MAPS );
				else
					*flags -= *flags & static_cast<uint32_t>(RENDER_FLAGS::ROUGHNESS_MAPS);
			}
			if (mat->m_textures[TEX_TYPE_METALLIC] != nullptr && mat->m_enableMetallicMap) {
				if (mat->m_enableMetallicMap)
					*flags |= static_cast<uint32_t>(RENDER_FLAGS::METALNESS_MAPS);
				else
					*flags -= *flags & static_cast<uint32_t>(RENDER_FLAGS::METALNESS_MAPS);
			}
		}
	}

	void Renderer::SetRenderCamera(Camera* cam)
	{
		_camera = cam;
	}

	UniquePtr<Renderer> Renderer::Init(GRAPHICS_API API)
	{
		if (API == GRAPHICS_API::OPENGL_API) {
			return MakeUnique<OpenGLRenderer>();
		}
	}

}
