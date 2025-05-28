#pragma once
#include "Runtime/Components/Cube.h"

namespace pine {

	Cube::Cube()
	{
		m_positions = std::vector<glm::vec3> {
			glm::vec3(-1, -1, -1),
			glm::vec3(-1, 1, -1),
			glm::vec3(1, 1, -1),
			glm::vec3(1, -1, -1),

			glm::vec3(-1, -1, 1),
			glm::vec3(-1, 1, 1),
			glm::vec3(1, 1, 1),
			glm::vec3(1, -1, 1),

			glm::vec3(-1, -1, -1),
			glm::vec3(-1, -1, 1),
			glm::vec3(1, -1, 1),
			glm::vec3(1, -1, -1),

			glm::vec3(-1, 1, -1),
			glm::vec3(-1, 1, 1),
			glm::vec3(1, 1, 1),
			glm::vec3(1, 1, -1),

			glm::vec3(-1, -1, -1),
			glm::vec3(-1, -1, 1),
			glm::vec3(-1, 1, 1),
			glm::vec3(-1, 1, -1),

			glm::vec3(1, -1, -1),
			glm::vec3(1, -1, 1),
			glm::vec3(1, 1, 1),
			glm::vec3(1, 1, -1)
		};

		m_texCoords = std::vector<glm::vec2>{
			glm::vec2(1, 0),
			glm::vec2(0, 0),
			glm::vec2(0, 1),
			glm::vec2(1, 1),

			glm::vec2(1, 0),
			glm::vec2(0, 0),
			glm::vec2(0, 1),
			glm::vec2(1, 1),

			glm::vec2(0, 1),
			glm::vec2(1, 1),
			glm::vec2(1, 0),
			glm::vec2(0, 0),

			glm::vec2(0, 1),
			glm::vec2(1, 1),
			glm::vec2(1, 0),
			glm::vec2(0, 0),

			glm::vec2(1, 1),
			glm::vec2(1, 0),
			glm::vec2(0, 0),
			glm::vec2(0, 1),

			glm::vec2(1, 1),
			glm::vec2(1, 0),
			glm::vec2(0, 0),
			glm::vec2(0, 1)
		};

		m_normals = std::vector<glm::vec3>{
			glm::vec3(0, 0, -1),
			glm::vec3(0, 0, -1),
			glm::vec3(0, 0, -1),
			glm::vec3(0, 0, -1),

			glm::vec3(0, 0, 1),
			glm::vec3(0, 0, 1),
			glm::vec3(0, 0, 1),
			glm::vec3(0, 0, 1),

			glm::vec3(0, -1, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, -1, 0),

			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),

			glm::vec3(-1, 0, 0),
			glm::vec3(-1, 0, 0),
			glm::vec3(-1, 0, 0),
			glm::vec3(-1, 0, 0),

			glm::vec3(1, 0, 0),
			glm::vec3(1, 0, 0),
			glm::vec3(1, 0, 0),
			glm::vec3(1, 0, 0)
		};
	

		m_indices = std::vector<unsigned int> { 
			0, 1, 2,
			0, 2, 3,

			6, 5, 4,
			7, 6, 4,

			10, 9, 8,
			11, 10, 8,

			12, 13, 14,
			12, 14, 15,

			16, 17, 18,
			16, 18, 19,

			22, 21, 20,
			23, 22, 20
		};
	}

}