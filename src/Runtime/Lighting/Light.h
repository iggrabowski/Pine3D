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
        Light(LightType type, glm::vec3 dir_pos, glm::vec3 color);
        ~Light();

		glm::vec3 GetColor() const { return m_Color; }
		glm::vec3 GetDirection() const { return m_Direction; }
    private:
		glm::vec3 m_Color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 m_Direction = glm::vec3(0.0f, -1.0f, 0.0f);
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
    };
}
