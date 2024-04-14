#pragma once
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Pine {

	//Renderer* Renderer::s_Instance = nullptr;
	
	Camera& Renderer::GetRenderCamera() const
	{
		return *m_Camera;
	}

	UniquePtr<Renderer> Renderer::Init(GRAPHICS_API API)
	{
		if (API == GRAPHICS_API::OPENGL_API) {
			return MakeUnique<OpenGLRenderer>();
		}
	}

}
