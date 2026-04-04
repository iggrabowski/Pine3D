#pragma once
#include "Runtime/Components/Texture.h"

namespace pine {
	class Skybox
	{
	public:
		Skybox();
		~Skybox();
	private:
		Texture* _texture;
	};
}

