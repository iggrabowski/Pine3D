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

		GLint internal_format;
		GLenum format;
		if (image.GetNumColorCh() == 1) {
			internal_format = GL_RGB8;
			format = GL_RGB;
			image._modifiedBytes = static_cast<unsigned char*>(malloc(texWidth * texHeight * 3 * sizeof(unsigned char)));
			for (int i = 0; i < texWidth * texHeight; i++) {
				const unsigned char v = image.GetBytes()[i];
				image._modifiedBytes[i*3+0] = v;
				image._modifiedBytes[i*3+1] = v;
				image._modifiedBytes[i*3+2] = v;
			}
			glTexImage2D(GL_TEXTURE_2D, 0, internal_format, texWidth, texHeight,
				0, format, GL_UNSIGNED_BYTE, image.GetModifiedPtr());
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (image.GetNumColorCh() == 3) {
			internal_format = GL_RGB8;
			format = GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, internal_format, texWidth, texHeight,
			0, format, GL_UNSIGNED_BYTE, image.GetPixelsPtr());
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (image.GetNumColorCh() == 4)
		{
			 internal_format = GL_RGBA8;
			 format = GL_RGBA;
			glTexImage2D(GL_TEXTURE_2D, 0, internal_format, texWidth, texHeight,
			0, format, GL_UNSIGNED_BYTE, image.GetPixelsPtr());
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "ERROR: Unsupported number of color channels in texture image: " << image.GetNumColorCh() << "\n";
			return;
		}
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
