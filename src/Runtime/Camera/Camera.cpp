#pragma once
#include "Camera.h"

namespace Pine {

	glm::mat4 Camera::GetViewProjection() const
	{
		return m_Projection * LookAt(m_Pos, m_Pos + m_Direction, up);
	}

	glm::mat4 Camera::GetProjectionMatrix() const
	{
		return m_Projection;
	}

	glm::mat4 Camera::GetViewMatrix() const
	{
		return LookAt(m_Pos, m_Pos + m_Direction, up);
	}

	glm::vec3 Camera::GetPos() const
	{
		return m_Pos;
	}

	glm::vec3 Camera::GetDirection() const
	{
		return m_Direction;
	}

	void Camera::SetPos(glm::vec3 pos)
	{
		m_Pos = pos;
	}

	void Camera::SetDirection(glm::vec3 direction)
	{
		m_Direction = direction;
	}

}
