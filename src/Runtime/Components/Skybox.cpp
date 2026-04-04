#include "Skybox.h"
#include "utils/Logger.h"
#include "Core/Application.h"

namespace pine {
	Skybox::Skybox()
	{
		// default path to skybox texture
		Image& image = Application::images.emplace_back();
		if (!image.Load("res/textures/skybox.hdr"))
		{
			Logger::Instance().Warning("Couldn't create a skybox using default texture path (missing texture).");
			return;
		}
		Application::images.push_back(image);

		_texture = &Application::textures.emplace_back();
	}
}
