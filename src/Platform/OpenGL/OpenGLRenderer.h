#pragma once

#include "Runtime/Renderer/Renderer.h"

namespace pine {

	class OpenGLRenderer final : public Renderer {
	public:
		OpenGLRenderer();

		void OnUpdate() override;
		void Clear() override;
		void DrawSkybox() override;
		void Startup() override;
		void Draw(MeshRenderer* mr) override;
		void PrefilterEnvironmentMap();
		//void Init() override;
		void BufferModelMesh(MeshRenderer* mr) override;
		void DrawBRDFLUT();
		void RenderQuad();

	private:
		void DrawIndexed(/*const IndexedModel& model*/) override;
		void InitSkybox();
		void GenerateIrradianceMap();
		unsigned int _prefilteredMapMaxMipLevels;
		GLuint _skyboxTextureObj;
		GLuint _skyboxCubeVAO;
		GLuint _irradianceMapTextureObj;
		GLuint _prefilteredMapObj;
		GLuint _brdfLUTTextureObj;
		GLuint _hdrTexture;
	};

}