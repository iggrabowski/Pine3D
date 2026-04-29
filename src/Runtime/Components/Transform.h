#pragma once
#include "Runtime/Camera/Camera.h"
#include "Utils/Utils.h"

namespace pine {

	class Transform {
	public:
		Transform(const vec3& pos = vec3(), const vec3& rot = vec3(), const vec3& scale = vec3(1.0f, 1.0f, 1.0f), const mat4 model = mat4())
		{
			this->_pos = pos;
			this->_rot = rot;
			this->_scale = scale;
			this->_model = model;
		}

		inline mat4 GetModel() const
		{
			return this->_model;
		}

		inline mat4 GetMVP(const Camera& camera) const
		{
			mat4 VP = camera.GetViewProjection();
			mat4 M = GetModel();

			return VP * M;//camera.GetViewProjection() * GetModel();
		}

		inline void UpdateModel() {

			// TODO: only update when something changes
			mat4 posMat = translate(_pos);
			mat4 scaleMat = scale(_scale);
			mat4 rotX = rotate(_rot.x, vec3(1.0, 0.0, 0.0));
			mat4 rotY = rotate(_rot.y, vec3(0.0, 1.0, 0.0));
			mat4 rotZ = rotate(_rot.z, vec3(0.0, 0.0, 1.0));
			mat4 rotMat = rotX * rotY * rotZ;

			_model = posMat * rotMat * scaleMat;
		}

		inline vec3* GetPos() { return &_pos; }
		inline vec3* GetRot() { return &_rot; }
		inline vec3* GetScale() { return &_scale; }

		inline void SetPos(vec3& pos) { this->_pos = pos; UpdateModel(); }
		inline void SetRot(vec3& rot) { this->_rot = rot; UpdateModel();}
		inline void SetScale(vec3& scale) { this->_scale = scale; UpdateModel();}
	protected:
	private:
		mat4 _model;

		vec3 _pos;
		vec3 _rot;
		vec3 _scale;
	};

}