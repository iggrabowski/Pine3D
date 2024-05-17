#pragma once
#include <Runtime/Components/Image.h>
#include <string>

// Has to be sufficient for now
#include <Utils/Utils.h>

namespace Pine {

	class Texture
	{
	public:
		Texture();
		//Texture(const std::string& fileName);

		void LoadFromImage(Image& image);

		void Bind();

		// TODO: fix for GLFW
		//void Update(int offsetX, int offsetY, sf::Image img_data);

		virtual ~Texture();
		//sf::Image tex;
	protected:
	private:
		void operator=(const Texture& texture) {}

		//TODO: make the texture more abstract, this relies on openGL standard
		unsigned int _texture;
	};
}