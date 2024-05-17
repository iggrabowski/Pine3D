#pragma once
#include "Polygon.h"

namespace Pine {

	Polygon::Polygon(std::vector<glm::vec2> points)
	{
		_points = points;
	}

	void Polygon::OnUpdate()
	{
		// TODO: move OpenGL code to OpenGL renderer
		glBegin(GL_TRIANGLE_FAN);

		for each(auto& point in _points) {
			glVertex2f(point.x, point.y);
		}

		glEnd();
	}

}
