#pragma once
#include "Camera.h"

#include "Utils/Logger.h"

namespace pine {

	mat4 Camera::GetViewProjection() const
	{
		return _projection * lookAt(_pos, _pos + _direction, up);
	}

	mat4 Camera::GetProjectionMatrix() const
	{
		return _projection;
	}

	mat4 Camera::GetViewMatrix() const
	{
		return lookAt(_pos, _pos + _direction, up);
	}

	vec3 Camera::GetPos() const
	{
		return _pos;
	}

	vec3 Camera::GetDirection() const
	{
		return _direction;
	}

	void Camera::SetPos(const vec3 pos)
	{
		_pos = pos;
	}

	void Camera::SetDirection(const vec3& direction)
	{
		_direction = direction;
	}

	void Camera::Rotate(float angle, const vec3& axis)
	{
        mat4 rotation = rotate(mat4(1.0f), radians(angle), axis);

        vec4 newPos4 = rotation * vec4(_pos, 1.0f);
        _pos = vec3(newPos4);

        up = normalize(vec3(rotation * vec4(up, 0.0f)));

        _direction = normalize(vec3(0.0f) - _pos);
	}

	void Camera::UpdateAspectRatio(float aspectRatio)
	{
		_projection = perspective(radians(fov), aspectRatio, _zNear, _zFar);
	}
}
