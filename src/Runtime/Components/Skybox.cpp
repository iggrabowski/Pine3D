#include "Skybox.h"
#include "utils/Logger.h"
#include "Core/Application.h"

#include <algorithm>
#include <numbers>

namespace pine {
	Skybox::Skybox()
	{
		// default path to skybox texture
		Image& image = Application::images.emplace_back();
		_shader = Shader::LoadShaders("../res/shaders/skybox");
		if (!image.Load("../res/textures/skybox.hdr"))
		{
			Logger::Instance().Warning("Couldn't create a skybox using default texture path (missing texture).");
			return;
		}

		_texture = &Application::textures.emplace_back();
		_texture->LoadFromImage(image);

		ConvertEquirectangularToCubemap();	// translate Equirectangular to skybox format
											// shoutout OGLDEV
	}

	Skybox::~Skybox()
	{
		delete _shader;
	}

	void Skybox::ConvertEquirectangularToCubemap()
	{
		int face_size = _texture->GetWidth() / 4;
		if (face_size <= 0) {
			Logger::Instance().Error("ConvertEquirectangularToCubemap: invalid skybox size.");
			return;
		}

		Image& src_image = *_texture->_image;
		const PixelFormat srcFmt = src_image.GetPixelFormat();
		if (!(_texture->_image->GetPixelFormat() == PIXEL_FORMAT_R32F))
		{
			Logger::Instance().Error("ConvertEquirectangularToCubemap: Unsupported skybox texture format, only HDR types supported.");
			}

		const float* src = static_cast<const float*>(src_image.GetPixels());
		if (!src) {
			Logger::Instance().Error("ConvertEquirectangularToCubemap: source has no pixel data.");
			return;
		}

		const int srcW = src_image.GetWidth();
		const int srcH = src_image.GetHeight();
		const int srcCh = std::max(1, src_image.GetNumColorCh());

		const float PI = std::numbers::pi_v<float>;
		const float TWO_PI = 2.0f * PI;

		for (int face = 0; face < 6; ++face)
		{
			const int numPixels = face_size * face_size;
			// allocate RGB float buffer (3 floats per texel)
			float* dst = static_cast<float*>(malloc(sizeof(float) * numPixels * 3));
			if (!dst) {
				Logger::Instance().Error("ConvertEquirectangularToCubemap: allocation failed.");
				return;
			}

			int idx = 0;
			for (int y = 0; y < face_size; ++y)
			{
				for (int x = 0; x < face_size; ++x)
				{
					const float a = 2.0f * ((x + 0.5f) / face_size) - 1.0f;
					const float b = 2.0f * ((y + 0.5f) / face_size) - 1.0f;

					glm::vec3 dir;
					switch (face)
					{
					case 0: dir = glm::vec3(1.0f, -b, -a); break; // +X
					case 1: dir = glm::vec3(-1.0f, -b, a); break; // -X
					case 2: dir = glm::vec3(a, 1.0f, b); break; // +Y
					case 3: dir = glm::vec3(a, -1.0f, -b); break; // -Y
					case 4: dir = glm::vec3(a, -b, 1.0f); break; // +Z
					case 5: dir = glm::vec3(-a, -b, -1.0f); break; // -Z
					}
					dir = glm::normalize(dir);

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
			_cubemapTextures[face].SoftCopyFrom(*this->_texture->_image);
			_cubemapTextures[face].SetPixels(dst, face_size, face_size);
		}

		Logger::Instance().Info("Skybox: translated equirectangular -> cubemap (HDR).");
	}
}