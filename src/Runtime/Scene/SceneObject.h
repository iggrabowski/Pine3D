#pragma once
#include "Runtime/Components/Transform.h"

namespace Pine {

	class SceneObject {
	public:
		//SceneObject();

		virtual void OnUpdate() = 0;
	protected:
		Transform* m_Transform;
		//MeshRenderer m_MeshRenderer;
	};

}