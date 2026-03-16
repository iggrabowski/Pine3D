#pragma once

#include "Runtime/Renderer/Renderer.h"

namespace pine {

	class OpenGLRenderer final : public Renderer {
	public:
		OpenGLRenderer();

		void Clear() override;
		void Draw(MeshRenderer* mr) override;
		//void Init() override;
		void BufferModelMesh(MeshRenderer* mr) override;
	private:
		void DrawIndexed(/*const IndexedModel& model*/) override;
	};

}