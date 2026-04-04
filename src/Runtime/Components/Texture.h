#pragma once
#include <Runtime/Components/Image.h>
#include <string>
//#include <GL/glew.h> // for GLuint

// Has to be sufficient for now
#include <Utils/Utils.h>

// TODO: make the texture more abstract
namespace pine {
	enum TextureType {
		TEX_TYPE_BASE = 0,
		TEX_TYPE_NORMAL,
		TEX_TYPE_METALLIC,
		TEX_TYPE_ROUGHNESS,
		TEX_TYPE_AO,
		TEX_TYPE_HEIGHT,
		TEX_TYPE_EMISSIVE,
	};

	// Textures are loaded into GPU memory by default.
	// TODO: if the app expands, dont load every texture into GPU.
	class Texture
	{
	public:
		Texture();
		Texture(GLenum textureTarget);
		Texture(GLenum textureTarget, std::string filePath);
		//Texture(const std::string& fileName);

		void LoadFromImage(Image& image);

		// Bind to texture unit 0 by default
		void Bind() const { Bind(0); }
		// Bind to specific texture unit (0..GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS-1)
		void Bind(unsigned int unit) const;

		 // Return underlying GL texture handle
		unsigned int GetGLHandle() const { return _texture; }

		virtual ~Texture();
		TextureType m_TextureType = TEX_TYPE_BASE;
		GLenum m_textureTarget = 0; // TODO: use
	private:
		void operator=(const Texture& texture) const {}
		std::string _filePath;

		//TODO: make the texture more abstract, this relies on openGL standard
		unsigned int _texture = 0;
	};
}