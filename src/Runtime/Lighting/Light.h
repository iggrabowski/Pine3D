#pragma once
#include "Runtime/Scene/SceneObject.h"

namespace pine
{
    enum LightType
    {
		LIGHT_TYPE_DIRECTIONAL, // has direction, no position
        LIGHT_TYPE_POINT, // has position, no direction
	};

    class Light
    {
    public:
        Light();
        Light(LightType type, vec3 dir_pos, vec3 color);
        ~Light();

		vec3 GetColor() const { return m_Color; }
		vec3 GetDirection() const { return m_Direction; }
    private:
		vec3 m_Color = vec3(1.0f, 1.0f, 1.0f);
		vec3 m_Direction = vec3(0.0f, -1.0f, 0.0f);
		vec3 m_Position = vec3(0.0f, 0.0f, 0.0f);
    };
}
