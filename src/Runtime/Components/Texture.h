#pragma once

#include <string>

// Has to be sufficient for now
#include <Utils/Utils.h>

namespace Pine {

	class Texture
	{
	public:
		Texture(const std::string& fileName);
		void Bind();

		// TODO: fix for GLFW
		//void Update(int offsetX, int offsetY, sf::Image img_data);

		virtual ~Texture();
		//sf::Image tex;
	protected:
	private:
		void operator=(const Texture& texture) {}

		GLuint m_texture;
	};
}