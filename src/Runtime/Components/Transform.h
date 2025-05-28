#pragma once
#include "Runtime/Camera/Camera.h"
#include "Utils/Utils.h"

namespace pine {

	class Transform {
	public:
		Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f), const glm::mat4 model = glm::mat4())
		{
			this->_pos = pos;
			this->_rot = rot;
			this->_scale = scale;
			this->_model = model;
		}

		inline glm::mat4 GetModel() const
		{
			return this->_model;
		}

		inline glm::mat4 GetMVP(const Camera& camera) const
		{
			glm::mat4 VP = camera.GetViewProjection();
			glm::mat4 M = GetModel();

			return VP * M;//camera.GetViewProjection() * GetModel();
		}

		inline void UpdateModel() {

			glm::mat4 posMat = glm::translate(_pos);
			glm::mat4 scaleMat = glm::scale(_scale);
			glm::mat4 rotX = glm::rotate(_rot.x, glm::vec3(1.0, 0.0, 0.0));
			glm::mat4 rotY = glm::rotate(_rot.y, glm::vec3(0.0, 1.0, 0.0));
			glm::mat4 rotZ = glm::rotate(_rot.z, glm::vec3(0.0, 0.0, 1.0));
			glm::mat4 rotMat = rotX * rotY * rotZ;

			_model = posMat * rotMat * scaleMat;
		}

		inline glm::vec3* GetPos() { return &_pos; }
		inline glm::vec3* GetRot() { return &_rot; }
		inline glm::vec3* GetScale() { return &_scale; }

		inline void SetPos(glm::vec3& pos) { this->_pos = pos; UpdateModel(); }
		inline void SetRot(glm::vec3& rot) { this->_rot = rot; UpdateModel();}
		inline void SetScale(glm::vec3& scale) { this->_scale = scale; UpdateModel();}
	protected:
	private:
		glm::mat4 _model;

		glm::vec3 _pos;
		glm::vec3 _rot;
		glm::vec3 _scale;
	};

}