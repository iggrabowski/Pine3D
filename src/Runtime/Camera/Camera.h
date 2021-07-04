#pragma once
#include "Utils/Utils.h"

namespace Pine {

	class Camera/* : public SceneObject*/ {
	public:
		Camera(const Vec3& pos = Vec3(0.0f, 0.0f, -2.0f),
			float fov = 70.0f,
			float aspect = 1200.0f / 900.0f,
			float zNear = 0.1f,
			float zFar = 100.0f) :
			m_Pos(pos),
			forward(Vec3(0.0f, 0.0f, 1.0f)),
			up(Vec3(0.0f, 1.0f, 0.0f)),
			m_Direction(Vec3(0.0f, 0.0f, 1.0f)),
			m_Projection(Perspective(fov, aspect, zNear, zFar)) {}

		Mat4 GetViewProjection() const;
		Mat4 GetProjectionMatrix() const;
		Mat4 GetViewMatrix() const;
		Vec3 GetPos() const;
		Vec3 GetDirection() const;

		void SetPos(Vec3 pos);
		void SetDirection(Vec3 direction);

		const Vec3 forward;
		const Vec3 up;
	private:
		Vec3 m_Pos;
		Mat4 m_Projection;
		Vec3 m_Direction;
	};

}