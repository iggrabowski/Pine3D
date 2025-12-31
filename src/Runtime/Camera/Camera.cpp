#pragma once
#include "Camera.h"

#include "Utils/Logger.h"

namespace pine {

	glm::mat4 Camera::GetViewProjection() const
	{
		return _projection * glm::lookAt(_pos, _pos + _direction, up);
	}

	glm::mat4 Camera::GetProjectionMatrix() const
	{
		return _projection;
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(_pos, _pos + _direction, up);
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

	void Camera::Rotate(float angle, const glm::vec3& axis)
	{
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);

        glm::vec4 newPos4 = rotation * glm::vec4(_pos, 1.0f);
        _pos = glm::vec3(newPos4);

        up = glm::normalize(glm::vec3(rotation * glm::vec4(up, 0.0f)));

        _direction = glm::normalize(glm::vec3(0.0f) - _pos);
	}

	void Camera::UpdateAspectRatio(float aspectRatio)
	{
		_projection = glm::perspective(glm::radians(fov), aspectRatio, _zNear, _zFar);
	}
}
