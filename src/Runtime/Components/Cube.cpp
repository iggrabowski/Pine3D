#pragma once
#include "Runtime/Components/Cube.h"

namespace Pine {

	Cube::Cube()
	{
		Positions = std::vector<Vec3> {
			Vec3(-1, -1, -1),
			Vec3(-1, 1, -1),
			Vec3(1, 1, -1),
			Vec3(1, -1, -1),

			Vec3(-1, -1, 1),
			Vec3(-1, 1, 1),
			Vec3(1, 1, 1),
			Vec3(1, -1, 1),

			Vec3(-1, -1, -1),
			Vec3(-1, -1, 1),
			Vec3(1, -1, 1),
			Vec3(1, -1, -1),

			Vec3(-1, 1, -1),
			Vec3(-1, 1, 1),
			Vec3(1, 1, 1),
			Vec3(1, 1, -1),

			Vec3(-1, -1, -1),
			Vec3(-1, -1, 1),
			Vec3(-1, 1, 1),
			Vec3(-1, 1, -1),

			Vec3(1, -1, -1),
			Vec3(1, -1, 1),
			Vec3(1, 1, 1),
			Vec3(1, 1, -1)
		};

		TexCoords = std::vector<Vec2>{
			Vec2(1, 0),
			Vec2(0, 0),
			Vec2(0, 1),
			Vec2(1, 1),

			Vec2(1, 0),
			Vec2(0, 0),
			Vec2(0, 1),
			Vec2(1, 1),

			Vec2(0, 1),
			Vec2(1, 1),
			Vec2(1, 0),
			Vec2(0, 0),

			Vec2(0, 1),
			Vec2(1, 1),
			Vec2(1, 0),
			Vec2(0, 0),

			Vec2(1, 1),
			Vec2(1, 0),
			Vec2(0, 0),
			Vec2(0, 1),

			Vec2(1, 1),
			Vec2(1, 0),
			Vec2(0, 0),
			Vec2(0, 1)
		};

		Normals = std::vector<Vec3>{
			Vec3(0, 0, -1),
			Vec3(0, 0, -1),
			Vec3(0, 0, -1),
			Vec3(0, 0, -1),

			Vec3(0, 0, 1),
			Vec3(0, 0, 1),
			Vec3(0, 0, 1),
			Vec3(0, 0, 1),

			Vec3(0, -1, 0),
			Vec3(0, -1, 0),
			Vec3(0, -1, 0),
			Vec3(0, -1, 0),

			Vec3(0, 1, 0),
			Vec3(0, 1, 0),
			Vec3(0, 1, 0),
			Vec3(0, 1, 0),

			Vec3(-1, 0, 0),
			Vec3(-1, 0, 0),
			Vec3(-1, 0, 0),
			Vec3(-1, 0, 0),

			Vec3(1, 0, 0),
			Vec3(1, 0, 0),
			Vec3(1, 0, 0),
			Vec3(1, 0, 0)
		};
	

		Indices = std::vector<unsigned int> { 
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

	Cube::Cube(float width, float height, float depth)
	{
		float x = width / 2.0;
		float y = height / 2.0;
		float z = depth / 2.0;
		Positions = std::vector<Vec3>{
			
			Vec3(-x, -y, -z),
			Vec3(-x, y, -z),
			Vec3(x, y, -z),
			Vec3(x, -y, -z),

			Vec3(-x, -y, z),
			Vec3(-x, y, z),
			Vec3(x, y, z),
			Vec3(x, -y, z),

			Vec3(-x, -y, -z),
			Vec3(-x, -y, z),
			Vec3(x, -y, z),
			Vec3(x, -y, -z),

			Vec3(-x, y, -z),
			Vec3(-x, y, z),
			Vec3(x, y, z),
			Vec3(x, y, -z),

			Vec3(-x, -y, -z),
			Vec3(-x, -y, z),
			Vec3(-x, y, z),
			Vec3(-x, y, -z),

			Vec3(x, -y, -z),
			Vec3(x, -y, z),
			Vec3(x, y, z),
			Vec3(x, y, -z)
		};

		TexCoords = std::vector<Vec2>{
			Vec2(1, 0),
			Vec2(0, 0),
			Vec2(0, 1),
			Vec2(1, 1),

			Vec2(1, 0),
			Vec2(0, 0),
			Vec2(0, 1),
			Vec2(1, 1),

			Vec2(0, 1),
			Vec2(1, 1),
			Vec2(1, 0),
			Vec2(0, 0),

			Vec2(0, 1),
			Vec2(1, 1),
			Vec2(1, 0),
			Vec2(0, 0),

			Vec2(1, 1),
			Vec2(1, 0),
			Vec2(0, 0),
			Vec2(0, 1),

			Vec2(1, 1),
			Vec2(1, 0),
			Vec2(0, 0),
			Vec2(0, 1)
		};

		Normals = std::vector<Vec3>{
			Vec3(0, 0, -1),
			Vec3(0, 0, -1),
			Vec3(0, 0, -1),
			Vec3(0, 0, -1),

			Vec3(0, 0, 1),
			Vec3(0, 0, 1),
			Vec3(0, 0, 1),
			Vec3(0, 0, 1),

			Vec3(0, -1, 0),
			Vec3(0, -1, 0),
			Vec3(0, -1, 0),
			Vec3(0, -1, 0),

			Vec3(0, 1, 0),
			Vec3(0, 1, 0),
			Vec3(0, 1, 0),
			Vec3(0, 1, 0),

			Vec3(-1, 0, 0),
			Vec3(-1, 0, 0),
			Vec3(-1, 0, 0),
			Vec3(-1, 0, 0),

			Vec3(1, 0, 0),
			Vec3(1, 0, 0),
			Vec3(1, 0, 0),
			Vec3(1, 0, 0)
		};


		Indices = std::vector<unsigned int>{
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