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

	//main rendering object
	class Renderer {

	public:
		static UniquePtr<Renderer> Init(GRAPHICS_API API);
			
		virtual void DrawIndexed(/*const IndexedModel& model*/) = 0;
		virtual void Draw(Model& model) = 0;

		//static Renderer* s_Instance;
		GRAPHICS_API m_rendererAPI = GRAPHICS_API::UNDEFINED_API;
		Camera& GetRenderCamera() const;

		// Setter so external code (Editor) can switch which Camera is used for rendering
		void SetRenderCamera(Camera* cam);

		virtual void Clear() = 0;
	protected:
		Camera* _camera;
	};

}