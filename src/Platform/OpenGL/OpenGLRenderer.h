#pragma once

#include "Runtime/Renderer/Renderer.h"

namespace pine {

	class OpenGLRenderer final : public Renderer {
	public:
		OpenGLRenderer();

		void OnUpdate() override;
		void Clear() override;
		void DrawSkybox() override;
		void Draw(MeshRenderer* mr) override;
		//void Init() override;
		void BufferModelMesh(MeshRenderer* mr) override;
	private:
		void DrawIndexed(/*const IndexedModel& model*/) override;
		void InitSkybox();
		GLuint _skyboxTextureObj;
		GLuint _skyboxCubeVAO;
	};

}