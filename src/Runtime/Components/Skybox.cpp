#include "Skybox.h"
#include "utils/Logger.h"
#include "Core/Application.h"

#include <cmath>
#include <algorithm>
#include <glm/glm.hpp>

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
		_texture->LoadFromImage(image);

		ConvertEquirectangularToCubemap();	// translate Equirectangular to skybox format
											// shoutout OGLDEV
	}

	void Skybox::ConvertEquirectangularToCubemap()
	{
		int face_size = _texture->GetWidth() / 4;
		if (face_size <= 0) {
			Logger::Instance().Error("ConvertEquirectangularToCubemap: skybox size.");
			return;
		}

		if (!(_texture->_image->GetPixelFormat() == PIXEL_FORMAT_R16F))
		{
			Logger::Instance().Error("ConvertEquirectangularToCubemap: Unsupported skybox texture format, only HDR types supported.");
			return;
		}

		// Assume the HDR/equirectangular source image is the last loaded image
		Image& src_image = *_texture->_image;
		const float* srcBytes = static_cast<const float*>(src_image.GetPixels());
		if (!srcBytes) {
			Logger::Instance().Error("ConvertEquirectangularToCubemap: source image has no pixel data.");
			return;
		}

		const int srcW = src_image.GetWidth();
		const int srcH = src_image.GetHeight();
		const int srcCh = std::max(1, src_image.GetNumColorCh()); // guard

		const float PI = 3.14159265358979323846f;

		// For each cube face, allocate an 8-bit RGB buffer in m_modifiedBytes (used elsewhere in the codebase)
		for (int face = 0; face < 6; ++face)
		{
			_cubemapTextures[face].SoftCopyFrom(src_image); // copy metadata
			const int numPixels = face_size * face_size;
			void* n = _cubemapTextures[face].GetPixels();
			n = malloc(sizeof(float) * numPixels * 4);
			float* dst = static_cast<float*>(n);

			int dstIdx = 0;
			for (int y = 0; y < face_size; ++y)
			{
				for (int x = 0; x < face_size; ++x)
				{
					// NDC coords in [-1,1]
					const float a = 2.0f * ((x + 0.5f) / face_size) - 1.0f;
					const float b = 2.0f * ((y + 0.5f) / face_size) - 1.0f;

					glm::vec3 dir;
					// Mapping based on common OpenGL cube face orientation (LearnOpenGL style)
					switch (face)
					{
					default:
					case 0: dir = glm::vec3(1.0f, -b, -a); break; // +X
					case 1: dir = glm::vec3(-1.0f, -b, a); break; // -X
					case 2: dir = glm::vec3(a, 1.0f, b); break; // +Y
					case 3: dir = glm::vec3(a, -1.0f, -b); break; // -Y
					case 4: dir = glm::vec3(a, -b, 1.0f); break; // +Z
					case 5: dir = glm::vec3(-a, -b, -1.0f); break; // -Z
					}

					dir = glm::normalize(dir);

					// Convert direction to equirectangular (u,v)
					const float theta = std::atan2(dir.z, dir.x);        // range (-PI, PI]
					const float phi = std::asin(std::clamp(dir.y, -1.0f, 1.0f)); // range [-PI/2, PI/2]

					float u = 0.5f + (theta / (PI * 2.0f));     // [0,1]
					float v = 0.5f - (phi / PI);           // [0,1] (flip to match image coord system)

					// Wrap and clamp
					u = u - std::floor(u); // ensure in [0,1)
					v = std::clamp(v, 0.0f, 1.0f);

					// Nearest-neighbor sample from source
					const int srcX = std::min(static_cast<int>(u * srcW), srcW - 1);
					const int srcY = std::min(static_cast<int>(v * srcH), srcH - 1);
					const int srcIndex = (srcY * srcW + srcX) * srcCh;

					// Copy at least RGB channels (if source has 1 channel replicate to RGB)
					unsigned char r = srcBytes[srcIndex + 0];
					unsigned char g = (srcCh >= 2) ? srcBytes[srcIndex + 1] : r;
					unsigned char bcol = (srcCh >= 3) ? srcBytes[srcIndex + 2] : r;

					dst[dstIdx++] = r;
					dst[dstIdx++] = g;
					dst[dstIdx++] = bcol;
				}
			}
		}

		Logger::Instance().Info("Skybox created.");
	}
}