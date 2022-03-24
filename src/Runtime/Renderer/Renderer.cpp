#pragma once
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Pine {

	//Renderer* Renderer::s_Instance = nullptr;
	
	Camera& Renderer::GetRenderCamera()
	{
		return *m_Camera;
	}

	UniquePtr<Renderer> Renderer::Init()
	{
		return MakeUnique<OpenGLRenderer>();
	}

}