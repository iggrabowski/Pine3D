#pragma once

#include "Runtime/Renderer/Renderer.h"

namespace pine {

	class OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer();

		void Clear() override;
		void Draw(MeshData& mesh, Material& mat) override final;
		//void Init() override;
	private:
		void DrawIndexed(/*const IndexedModel& model*/);
		void BufferMesh(MeshData& mesh, Shader& shader);
	};

}