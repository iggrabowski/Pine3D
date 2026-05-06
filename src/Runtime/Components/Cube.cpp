#pragma once
#include "Runtime/Components/Cube.h"

namespace pine {

	Cube::Cube()
	{
		m_Positions = std::vector<vec3> {
			vec3(-1, -1, -1),
			vec3(-1, 1, -1),
			vec3(1, 1, -1),
			vec3(1, -1, -1),

			vec3(-1, -1, 1),
			vec3(-1, 1, 1),
			vec3(1, 1, 1),
			vec3(1, -1, 1),

			vec3(-1, -1, -1),
			vec3(-1, -1, 1),
			vec3(1, -1, 1),
			vec3(1, -1, -1),

			vec3(-1, 1, -1),
			vec3(-1, 1, 1),
			vec3(1, 1, 1),
			vec3(1, 1, -1),

			vec3(-1, -1, -1),
			vec3(-1, -1, 1),
			vec3(-1, 1, 1),
			vec3(-1, 1, -1),

			vec3(1, -1, -1),
			vec3(1, -1, 1),
			vec3(1, 1, 1),
			vec3(1, 1, -1)
		};

		m_TexCoords = std::vector<vec2>{
			vec2(1, 0),
			vec2(0, 0),
			vec2(0, 1),
			vec2(1, 1),

			vec2(1, 0),
			vec2(0, 0),
			vec2(0, 1),
			vec2(1, 1),

			vec2(0, 1),
			vec2(1, 1),
			vec2(1, 0),
			vec2(0, 0),

			vec2(0, 1),
			vec2(1, 1),
			vec2(1, 0),
			vec2(0, 0),

			vec2(1, 1),
			vec2(1, 0),
			vec2(0, 0),
			vec2(0, 1),

			vec2(1, 1),
			vec2(1, 0),
			vec2(0, 0),
			vec2(0, 1)
		};

		m_Normals = std::vector<vec3>{
			vec3(0, 0, -1),
			vec3(0, 0, -1),
			vec3(0, 0, -1),
			vec3(0, 0, -1),

			vec3(0, 0, 1),
			vec3(0, 0, 1),
			vec3(0, 0, 1),
			vec3(0, 0, 1),

			vec3(0, -1, 0),
			vec3(0, -1, 0),
			vec3(0, -1, 0),
			vec3(0, -1, 0),

			vec3(0, 1, 0),
			vec3(0, 1, 0),
			vec3(0, 1, 0),
			vec3(0, 1, 0),

			vec3(-1, 0, 0),
			vec3(-1, 0, 0),
			vec3(-1, 0, 0),
			vec3(-1, 0, 0),

			vec3(1, 0, 0),
			vec3(1, 0, 0),
			vec3(1, 0, 0),
			vec3(1, 0, 0)
		};
	

		m_Indices = std::vector<unsigned int> { 
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