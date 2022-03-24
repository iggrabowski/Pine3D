#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/ext.hpp>

#include <memory>
#include <vector>
#include <string>
#include <iostream>

namespace Pine {

//#ifdef GRAPHICS_API_OPENGL
	typedef glm::vec2 Vec2;
	typedef glm::vec3 Vec3;
	typedef glm::vec4 Vec4;

	typedef glm::ivec2 Vec2i;
	typedef glm::ivec3 Vec3i;
	typedef glm::ivec4 Vec4i;

	typedef glm::mat3 Mat3;
	typedef glm::mat4 Mat4;

//#define LookAt glm::lookAt
	template<typename ... Args>
	static constexpr Mat4 LookAt(Args&& ... args)
	{
		return glm::lookAt(std::forward<Args>(args)...);
	}

//#define Perspective glm::perspective
	template<typename ... Args>
	static constexpr Mat4 Perspective(Args&& ... args)
	{
		return glm::perspective(std::forward<Args>(args)...);
	}

//#define Rotate glm::rotate
	template<typename T, typename ... Args>
	static constexpr T Rotate(Args&& ... args)
	{
		return glm::rotate(std::forward<Args>(args)...);
	}

//#define Cross glm::cross
	template<typename ... Args>
	static constexpr Vec3 Cross(Args&& ... args)
	{
		return glm::cross(std::forward<Args>(args)...);
	}

//#define Normalize glm::normalize
	template<typename ... Args>
	static constexpr Vec3 Normalize(Args&& ... args)
	{
		return glm::normalize(std::forward<Args>(args)...);
	}
//#endif // GRAPHICS_API_OPENGL

	template<class T>
	using UniquePtr = std::unique_ptr<T>;

	template<class T>
	using Vector = std::vector<T>;

	using String = std::string;

	template<typename T, typename ... Args>
	static constexpr UniquePtr<T> MakeUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

}