#pragma once
#include "Runtime/Components/MeshRenderer.h"
#include "Utils/Utils.h"
#include "Runtime/Camera/Camera.h"

#include <memory>

namespace Pine {

	//main rendering object
	class Renderer {
		friend class Application;
	public:
		static UniquePtr<Renderer> Init();

		virtual void DrawIndexed(/*const IndexedModel& model*/) = 0;
		virtual void Draw(Mesh& mesh, Material& mat) = 0;

		//static Renderer* s_Instance;

		Camera& GetRenderCamera();

		virtual void Clear() = 0;
	protected:
		Camera* m_Camera;
	};

}