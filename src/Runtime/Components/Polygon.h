#pragma once
#include "Utils/Utils.h"
#include "Runtime/Scene/SceneObject.h"
#include "Runtime/RenderCore/Shader.h"

#include <vector>


namespace pine {

	class Polygon : public SceneObject {
	public:
		Polygon(std::vector<glm::vec2> points);

		void OnUpdate() override;
	private:
		std::vector<glm::vec2> _points;
	};

}