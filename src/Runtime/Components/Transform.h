#pragma once
#include "Runtime/Camera/Camera.h"
#include "Utils/Utils.h"

namespace Pine {

	class Transform {
	public:
		Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
		{
			this->pos = pos;
			this->rot = rot;
			this->scale = scale;
		}

		inline Mat4 GetModel() const
		{
			return this->model;
		}

		inline glm::mat4 GetMVP(const Camera& camera) const
		{
			glm::mat4 VP = camera.GetViewProjection();
			glm::mat4 M = GetModel();

			return VP * M;//camera.GetViewProjection() * GetModel();
		}

		inline void UpdateModel() {

			glm::mat4 posMat = glm::translate(pos);
			glm::mat4 scaleMat = glm::scale(scale);
			glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
			glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
			glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
			glm::mat4 rotMat = rotX * rotY * rotZ;

			model = posMat * rotMat * scaleMat;
		}

		inline glm::vec3* GetPos() { return &pos; }
		inline glm::vec3* GetRot() { return &rot; }
		inline glm::vec3* GetScale() { return &scale; }

		inline void SetPos(glm::vec3& pos) { this->pos = pos; UpdateModel(); }
		inline void SetRot(glm::vec3& rot) { this->rot = rot; UpdateModel();}
		inline void SetScale(glm::vec3& scale) { this->scale = scale; UpdateModel();}
	protected:
	private:
		glm::mat4 model;

		glm::vec3 pos;
		glm::vec3 rot;
		glm::vec3 scale;
	};

}