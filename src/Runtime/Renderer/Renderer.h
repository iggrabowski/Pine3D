#pragma once
#include "Runtime/Components/MeshRenderer.h"
#include "Utils/Utils.h"
#include "Runtime/Camera/Camera.h"
#include "Runtime/Components/Skybox.h"

#include <memory>

namespace pine {

	enum class GraphicsApi {
		UNDEFINED_API,
		OPENGL_API
	};

	enum class RenderFlags
	{
		BASE_TEXTURE = 0x1,
		NORMAL_MAPS = 0x2,
		ROUGHNESS_MAPS = 0x4,
		METALNESS_MAPS = 0x8,
		AO_MAPS = 0x10,
		EMISSIVE_MAPS = 0x20
	};

	//main rendering object
	class Renderer {

	public:
		virtual ~Renderer() = default;
		static UniquePtr<Renderer> Init(GraphicsApi API);
			
		virtual void Startup() = 0;
		virtual void OnUpdate() = 0;
		virtual void DrawIndexed(/*const IndexedModel& model*/) = 0;
		virtual void Draw(MeshRenderer* mr) = 0;

		//static Renderer* s_Instance;
		GraphicsApi m_rendererAPI = GraphicsApi::UNDEFINED_API;
		Camera& GetRenderCamera() const;

		// Setter so external code (Editor) can switch which Camera is used for rendering
		void SetRenderCamera(Camera* cam);

		virtual void Clear() = 0;
		virtual void BufferModelMesh(MeshRenderer* mr) = 0;
	protected:
		Camera* _camera;
		std::unique_ptr<Skybox> _skybox;
		void UpdateRenderFlags(MeshRenderer* mr);
		virtual void DrawSkybox() = 0;
	};

}
