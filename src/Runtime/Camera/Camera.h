#pragma once
#include "Utils/Utils.h"
//#include "Runtime/Scene/SceneObject.h"
#include "Runtime/Components/Component.h"

namespace Pine {

	class Camera : Component{
	public:
		Camera(const glm::vec3& pos = glm::vec3(2.0f, 2.0f, -5.0f),
			float fov = 70.0f,
			float aspect = 1200.0f / 900.0f,
			float zNear = 0.1f,
			float zFar = 100.0f) :
			m_Pos(pos),
			forward(glm::vec3(0.0f, 0.0f, 1.0f)),
			up(glm::vec3(0.0f, 1.0f, 0.0f)),
			m_Direction(glm::vec3(-0.5f, -0.5f, 1.0f)),
			m_Projection(Perspective(fov, aspect, zNear, zFar)) {}

		glm::mat4 GetViewProjection() const;
		glm::mat4 GetProjectionMatrix() const;
		glm::mat4 GetViewMatrix() const;
		glm::vec3 GetPos() const;
		glm::vec3 GetDirection() const;

		void SetPos(glm::vec3 pos);
		void SetDirection(glm::vec3 direction);

		const glm::vec3 forward;
		const glm::vec3 up;
	private:
		glm::vec3 m_Pos;
		glm::mat4 m_Projection;
		glm::vec3 m_Direction;
	};

}