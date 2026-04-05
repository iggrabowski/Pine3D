#pragma once
#include "Runtime/Components/Texture.h"

namespace pine {
	class Skybox
	{
	public:
		Skybox();
		~Skybox();
	private:
		void ConvertEquirectangularToCubemap();

		Texture* _texture;
		Image _cubemapTextures[6];
	};
}

