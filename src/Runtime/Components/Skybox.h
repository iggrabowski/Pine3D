#pragma once
#include "Runtime/Components/Texture.h"
#include "Runtime/RenderCore/Shader.h"

namespace pine {
	class Skybox
	{
	public:
		Skybox();
		~Skybox();
		Image* GetCubemapTextures() { return _cubemapTextures; }
		Shader* GetShader() const { return _shader; }
		Texture* GetTexture() const { return _texture; }
		unsigned int GetResolution() const { return _resolution; }
	private:
		void ConvertEquirectangularToCubemap();

		unsigned int _resolution;
		Texture* _texture;
		Shader* _shader;
		Image _cubemapTextures[6];
	};
}

