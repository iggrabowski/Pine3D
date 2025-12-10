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
