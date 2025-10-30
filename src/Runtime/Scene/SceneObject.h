#pragma once
#include "Runtime/Components/Transform.h"

namespace pine {

	class SceneObject {
	public:
		virtual ~SceneObject() = default;
		//SceneObject();

		virtual void OnUpdate() = 0;
	protected:
		std::unique_ptr<Transform> _transform = nullptr;
		//MeshRenderer m_MeshRenderer;
	};

}