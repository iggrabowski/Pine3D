#pragma once
#include "Polygon.h"

namespace Pine {

	Polygon::Polygon(std::vector<Vec2> points)
	{
		m_Points = points;
	}

	void Polygon::OnUpdate()
	{
		// TODO: move OpenGL code to OpenGL renderer
		glBegin(GL_TRIANGLES);

		for each(auto& point in m_Points) {
			glVertex2f(point.x, point.y);
		}

		glEnd();
	}

}
