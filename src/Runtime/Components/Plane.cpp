#pragma once
#include "Runtime/Components/Plane.h"

namespace Pine {

	Plane::Plane()
	{
		Positions = std::vector<Vec3>{
			Vec3(-1.0, 0.0, -1.0),
			Vec3(-1.0, 0.0, 1.0),
			Vec3(1.0, 0.0, -1.0),
			Vec3(1.0, 0.0, 1.0),
		};
	}

	Plane::Plane(float width, float depth)
	{
		Positions = std::vector<Vec3>{
			Vec3(-width / 2.0, 0.0, -depth / 2.0),
			Vec3(-width / 2.0, 0.0, depth / 2.0),
			Vec3(width / 2.0, 0.0, -depth / 2.0),
			Vec3(width / 2.0, 0.0, depth / 2.0),
		};

		Normals = std::vector<Vec3>{
			Vec3(0, 1, 0),
			Vec3(0, 1, 0),
			Vec3(0, 1, 0),
			Vec3(0, 1, 0),
		};

		Indices = std::vector<unsigned int>{
			0, 1, 2,
			1, 3, 2,
		};
	}

}