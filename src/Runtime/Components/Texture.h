#pragma once
#include <Runtime/Components/Image.h>
#include <string>

// Has to be sufficient for now
#include <Utils/Utils.h>

namespace pine {
	enum TextureType {
		TEX_TYPE_BASE = 0,
		TEX_TYPE_NORMAL,
		TEX_TYPE_METALLIC,
		TEX_TYPE_ROUGHNESS,
		TEX_TYPE_AO,
		TEX_TYPE_EMISSIVE,
	};

	class Texture
	{
	public:
		Texture();
		Texture(GLenum textureTarget);
		Texture(GLenum textureTarget, std::string filePath);
		//Texture(const std::string& fileName);

		void LoadFromImage(Image& image);

		void Bind();

		// TODO: fix for GLFW
		//void Update(int offsetX, int offsetY, sf::Image img_data);

		virtual ~Texture();
		//sf::Image tex;
		TextureType m_TextureType = TEX_TYPE_BASE;
		GLenum p_textureTarget = 0; // TODO: use
	private:
		void operator=(const Texture& texture) {}
		std::string _filePath;

		//TODO: make the texture more abstract, this relies on openGL standard
		unsigned int _texture;
	};
}