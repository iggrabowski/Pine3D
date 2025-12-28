#include "Light.h"

pine::Light::Light()
{
}

pine::Light::Light(LightType type, glm::vec3 dir_pos, glm::vec3 color)
{
	if (type == LIGHT_TYPE_DIRECTIONAL)
	{
		m_Direction = dir_pos;
	}
	else if (type == LIGHT_TYPE_POINT)
	{
		m_Position = dir_pos;
	}
	m_Color = color;
}

pine::Light::~Light()
{
}
