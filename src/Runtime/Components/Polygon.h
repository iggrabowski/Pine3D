#pragma once
#include "Utils/Utils.h"
#include "Runtime/Scene/SceneObject.h"
#include "Runtime/RenderCore/Shader.h"

#include <vector>


namespace Pine {

	class Polygon : public SceneObject {
	public:
		Polygon(std::vector<Vec2> points);

		void OnUpdate() override;
	private:
		std::vector<Vec2> m_Points;
	};

}