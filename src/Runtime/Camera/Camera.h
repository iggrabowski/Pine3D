#pragma once
#include "Utils/Utils.h"
//#include "Runtime/Scene/SceneObject.h"
#include "Runtime/Components/Component.h"

namespace pine {

	class Camera : Component{
	public:
		explicit Camera(const glm::vec3& pos = glm::vec3(2.0f, 2.0f, -5.0f),
		                const float fov = 70.0f,
		                const float aspect = 1200.0f / 900.0f,
		                const float zNear = 0.1f,
		                const float zFar = 100.0f) :
			forward(glm::vec3(0.0f, 0.0f, 1.0f)),
			up(glm::vec3(0.0f, 1.0f, 0.0f)),
			fov(fov),
			_pos(pos),
			_projection(Perspective(fov, aspect, zNear, zFar)), _direction(glm::vec3(-0.5f, -0.5f, 1.0f)) {}

		[[nodiscard]] glm::mat4 GetViewProjection() const;
		[[nodiscard]] glm::mat4 GetProjectionMatrix() const;
		[[nodiscard]] glm::mat4 GetViewMatrix() const;
		[[nodiscard]] glm::vec3 GetPos() const;
		[[nodiscard]] glm::vec3 GetDirection() const;

		void SetPos(glm::vec3 pos);
		void SetDirection(const glm::vec3& direction);

		glm::vec3 forward;
		glm::vec3 up;
		float fov;

	private:
		glm::vec3 _pos;
		glm::mat4 _projection;
		glm::vec3 _direction;
	};

}