#pragma once
#include "Runtime/Components/Texture.h"
#include <GLFW/glfw3.h>

#include <iostream>

namespace pine {

	Texture::Texture() {

	}

	Texture::Texture(GLenum textureTarget) {
		p_textureTarget = textureTarget;
	}

	Texture::Texture(GLenum textureTarget, std::string filePath) {
		p_textureTarget = textureTarget;
		_filePath = filePath;
	}
  //  Texture::Texture(const std::string& fileName)
  //  {
  //      //int width, height, numComponents;
  //      //unsigned char* data = stbi_load((fileName).c    _str(), &width, &height, &numComponents, 4);

  //      // load texture
  //      //sf::Image img_data;
  //      //tex.loadFromImage(img_data);    

  //      /*glGenTextures(1, &m_texture);
  //      glActiveTexture(GL_TEXTURE0);
  //      glBindTexture(GL_TEXTURE_2D, m_texture);

  //      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//if (!glfwLoadTexture2D(fileName))
		//{
		//	std::cout << "ERROR: Texture failed to load!" << std::endl;
		//}

  //      sf::Vector2u texSize = tex.getSize();
  //      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texSize.x, texSize.y,
  //          0, GL_RGBA, GL_UNSIGNED_BYTE, tex.getPixelsPtr());*/
  //  }

	void Texture::LoadFromImage(Image & image) // TODO: why is this not abstract
	{
		glGenTextures(1, &_texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture);
			
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		GLsizei texWidth = image.GetWidth();
		GLsizei texHeight = image.GetHeight();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight,
			0, GL_RGB, GL_UNSIGNED_BYTE, image.GetPixelsPtr());
	}

    Texture::~Texture()
    {
        glDeleteTextures(1, &_texture);
    }

	void Texture::Bind(unsigned int unit) const
	{
		// Guard: clamp unit to reasonable range if desired
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, _texture);
	}    //void Texture::Update(int offsetX, int offsetY, sf::Image img_data)
    //{
    //    tex = img_data;
    //    sf::Vector2u texSize = img_data.getSize();
    //    Bind();
    //    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texSize.x, texSize.y, GL_RGBA, GL_UNSIGNED_BYTE, img_data.getPixelsPtr());
    //    //glBindTexture(GL_TEXTURE_2D, 0);
    //}

}
