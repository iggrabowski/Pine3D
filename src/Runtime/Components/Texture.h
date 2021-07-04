#pragma once

#include <string>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

namespace Pine {

	class Texture
	{
	public:
		Texture(const std::string& fileName);
		void Bind();
		void Update(int offsetX, int offsetY, sf::Image img_data);

		virtual ~Texture();
		sf::Image tex;
	protected:
	private:
		void operator=(const Texture& texture) {}

		GLuint m_texture;
	};

}