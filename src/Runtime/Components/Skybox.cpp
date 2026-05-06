#include "Skybox.h"
#include "utils/Logger.h"
#include "Core/Application.h"

#include <algorithm>
#include <numbers>

namespace pine {
	Skybox::Skybox()
	{
		// load shaders + texture (interface?)
		// evaluate
		// convert to cubemap (its equirectangular) or not (shader maybe)
		// clear ram from stbi data
		// keep in gl objects
		Image image;
		_shader = Shader::LoadShaders("../res/shaders/skybox");
		if (!image.Load("../res/textures/skybox.hdr"))
		{
			Logger::Instance().Warning("Couldn't create a skybox using default texture path (missing texture).");
			return;
		}

		ConvertEquirectangularToCubemap(image);	// translate Equirectangular to skybox format
													// shoutout OGLDEV
	}

	Skybox::~Skybox()
	{
		delete _shader;
	}

	void Skybox::ConvertEquirectangularToCubemap(Image& image)
	{
		_resolution = image.GetWidth() / 4;
		if (_resolution <= 0) {
			Logger::Instance().Error("ConvertEquirectangularToCubemap: invalid skybox size.");
			return;
		}

		if (!(image.GetPixelFormat() == PIXEL_FORMAT_R16F))
		{
			Logger::Instance().Error("ConvertEquirectangularToCubemap: Unsupported skybox texture format, only HDR types supported.");
			}

		const float* src = static_cast<const float*>(image.GetPixels());
		if (!src) {
			Logger::Instance().Error("ConvertEquirectangularToCubemap: source has no pixel data.");
			return;
		}

		const int srcW = image.GetWidth();
		const int srcH = image.GetHeight();
		const int srcCh = std::max(1, image.GetNumColorCh());

		const float PI = std::numbers::pi_v<float>;
		const float TWO_PI = 2.0f * PI;

		for (int face = 0; face < 6; ++face)
		{
			const unsigned int numPixels = _resolution * _resolution;
			// allocate RGB float buffer (3 floats per texel)
			float* dst = static_cast<float*>(malloc(sizeof(float) * numPixels * 3));
			if (!dst) {
				Logger::Instance().Error("ConvertEquirectangularToCubemap: allocation failed.");
				return;
			}

			int idx = 0;
			for (int y = 0; y < _resolution; ++y)
			{
				for (int x = 0; x < _resolution; ++x)
				{
					const float a = 2.0f * ((x + 0.5f) / _resolution) - 1.0f;
					const float b = 2.0f * ((y + 0.5f) / _resolution) - 1.0f;
					vec3 dir;
					switch (face)
					{
					case 0: dir = vec3(1.0f, -b, -a); break; // +X
					case 1: dir = vec3(-1.0f, -b, a); break; // -X
					case 2: dir = vec3(a, 1.0f, b); break; // +Y
					case 3: dir = vec3(a, -1.0f, -b); break; // -Y
					case 4: dir = vec3(a, -b, 1.0f); break; // +Z
					case 5: dir = vec3(-a, -b, -1.0f); break; // -Z
					}
					dir = normalize(dir);

					const float theta = std::atan2(dir.z, dir.x);
					const float phi = std::asin(std::clamp(dir.y, -1.0f, 1.0f));
					float u = 0.5f + (theta / TWO_PI);
					float v = 0.5f - (phi / PI);

					u = u - std::floor(u);
					v = std::clamp(v, 0.0f, 1.0f);

					const int srcX = std::min(static_cast<int>(u * srcW), srcW - 1);
					const int srcY = std::min(static_cast<int>(v * srcH), srcH - 1);
					const int srcIndex = (srcY * srcW + srcX) * srcCh;

					// read floats (linear HDR)
					float rf = src[srcIndex + 0];
					float gf = (srcCh >= 2) ? src[srcIndex + 1] : rf;
					float bf = (srcCh >= 3) ? src[srcIndex + 2] : rf;

					dst[idx++] = rf;
					dst[idx++] = gf;
					dst[idx++] = bf;
				}
			}

			// transfer ownership into the Image (SetPixels will free previous buffer)
			_cubemapTextures[face].SoftCopyFrom(image);
			_cubemapTextures[face].SetPixels(dst, _resolution, _resolution);
		}

		Logger::Instance().Info("Skybox: translated equirectangular -> cubemap (HDR).");
	}
}