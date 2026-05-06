#pragma once
#include "Utils/Utils.h"
//#include "Runtime/Scene/SceneObject.h"
#include "Runtime/Components/Component.h"

namespace pine {

	class Camera : Component{
	public:
		// TODO: fix magic
		explicit Camera(const vec3& pos = vec3(2.0f, 2.0f, -5.0f),
		                const float fov = 70.0f,
		                const float aspect = 1200.0f / 900.0f,
		                const float zNear = 0.1f,
		                const float zFar = 100.0f) :
			forward(vec3(0.0f, 0.0f, 1.0f)),
			up(vec3(0.0f, 1.0f, 0.0f)),
			fov(fov),
			_pos(pos),
			_projection(perspective(radians(fov), aspect, zNear, zFar)),
			_direction(vec3(-0.5f, -0.5f, 1.0f)),
			_zNear(zNear),
			_zFar(zFar){}

		[[nodiscard]] mat4 GetViewProjection() const;
		[[nodiscard]] mat4 GetProjectionMatrix() const;
		[[nodiscard]] mat4 GetViewMatrix() const;
		[[nodiscard]] vec3 GetPos() const;
		[[nodiscard]] vec3 GetDirection() const;

		void SetPos(vec3 pos);
		void SetDirection(const vec3& direction);
		void Rotate(float angle, const vec3& axis);
		void UpdateAspectRatio(float aspectRatio);
		vec3 forward;
		vec3 up;
		float fov;

	private:
		vec3 _pos;
		mat4 _projection;
		vec3 _direction;

		float _zNear;
		float _zFar;
	};

}