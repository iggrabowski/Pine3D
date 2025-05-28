#pragma once
#include "Polygon.h"

#include <utility>

namespace pine {

	Polygon::Polygon(std::vector<glm::vec2> points)
	{
		_points = std::move(points);
	}

	void Polygon::OnUpdate()
	{
		// TODO: move OpenGL code to OpenGL renderer
		glBegin(GL_TRIANGLE_FAN);

		for (const auto& point : _points) {
			glVertex2f(point.x, point.y);
		}

		glEnd();
	}

}
