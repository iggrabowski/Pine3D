#pragma once
#include "Runtime/Components/Texture.h"
//#include <GLFW/glfw3.h>

#include <iostream>
//#include <algorithm>
//#include <cctype>

namespace pine {

	Texture::Texture() {

	}

	Texture::Texture(GLenum textureTarget) {
		m_textureTarget = textureTarget;
	}

	Texture::Texture(GLenum textureTarget, std::string filePath) {
		m_textureTarget = textureTarget;
		_filePath = filePath;
	}

	void Texture::LoadFromImage(Image& image) // TODO: why is this not abstract
	{
		_image = &image;
		// TODO: generate gl texture somewhere else.
		
		glGenTextures(1, &_texture);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture);
			

		_texWidth = image.GetWidth();
		_texHeight = image.GetHeight();

		GLint internal_format;
		GLenum format;

		if (image.GetPixelFormat() == PIXEL_FORMAT_R16F) {
			// HDR image
			internal_format = GL_RGB16F;
			format = GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, internal_format, _texWidth, _texHeight,
				0, format, GL_FLOAT, image.GetPixels());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			if (image.GetPixelFormat() == PIXEL_FORMAT_R8G8B8) {
				internal_format = GL_RGB8;
				format = GL_RGB;
				glTexImage2D(GL_TEXTURE_2D, 0, internal_format, _texWidth, _texHeight,
					0, format, GL_UNSIGNED_BYTE, image.GetPixels());
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else if (image.GetPixelFormat() == PIXEL_FORMAT_R8G8B8A8)
			{
				internal_format = GL_RGBA8;
				format = GL_RGBA;
				glTexImage2D(GL_TEXTURE_2D, 0, internal_format, _texWidth, _texHeight,
					0, format, GL_UNSIGNED_BYTE, image.GetPixels());
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else {
				std::cout << "ERROR: Unsupported pixel format. No columns: " << image.GetNumColorCh() <<
					" | Format: " << enum_to_string(image.GetPixelFormat()) <<"\n";
			}
		}
	}

    Texture::~Texture()
    {
        glDeleteTextures(1, &_texture);
    }

	void Texture::Bind(unsigned int unit) const
	{
		// TODO: move to Api 
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
