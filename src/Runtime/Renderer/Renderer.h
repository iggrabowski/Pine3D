#pragma once
#include "Runtime/Components/MeshRenderer.h"
#include "Utils/Utils.h"
#include "Runtime/Camera/Camera.h"

#include <memory>

namespace pine {

	enum class GRAPHICS_API {
		UNDEFINED_API,
		OPENGL_API
	};

	enum class RENDER_FLAGS
	{
		BASE_TEXTURE = 0x1,
		NORMAL_MAPS = 0x2,
		ROUGHNESS_MAPS = 0x4
	};

	//main rendering object
	class Renderer {

	public:
		static UniquePtr<Renderer> Init(GRAPHICS_API API);
			
		virtual void DrawIndexed(/*const IndexedModel& model*/) = 0;
		virtual void Draw(MeshRenderer* mr) = 0;

		//static Renderer* s_Instance;
		GRAPHICS_API m_rendererAPI = GRAPHICS_API::UNDEFINED_API;
		Camera& GetRenderCamera() const;

		// Setter so external code (Editor) can switch which Camera is used for rendering
		void SetRenderCamera(Camera* cam);

		virtual void Clear() = 0;
	protected:
		Camera* _camera;
		void UpdateRenderFlags(MeshRenderer* mr);
	};

}