#pragma once
#include "Camera.h"

namespace pine {

	glm::mat4 Camera::GetViewProjection() const
	{
		return _projection * LookAt(_pos, _pos + _direction, up);
	}

	glm::mat4 Camera::GetProjectionMatrix() const
	{
		return _projection;
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		return LookAt(_pos, _pos + _direction, up);
	}

	glm::vec3 Camera::GetPos() const
	{
		return _pos;
	}

	glm::vec3 Camera::GetDirection() const
	{
		return _direction;
	}

	void Camera::SetPos(const glm::vec3 pos)
	{
		_pos = pos;
	}

	void Camera::SetDirection(const glm::vec3& direction)
	{
		_direction = direction;
	}

}
