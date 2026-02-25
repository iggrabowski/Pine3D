#pragma once

#include "Runtime/Renderer/Renderer.h"

namespace pine {

	class OpenGLRenderer : public Renderer {
	public:
		OpenGLRenderer();

		void Clear() final;
		void Draw(MeshRenderer* mr) final;
		//void Init() override;
		void BufferModelMesh(Model3D* model) final;
	private:
		void DrawIndexed(/*const IndexedModel& model*/);
	};

}