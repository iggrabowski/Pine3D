#include "Image.h"
#include <algorithm>
#include <filesystem>
#include "utils/Logger.h"

// Include stb image library
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

const char* pine::enum_to_string(PixelFormat e)
{
	switch (e)
	{
		case PIXEL_FORMAT_UNKNOWN: return "PIXEL_FORMAT_UNKNOWN";
		case PIXEL_FORMAT_R8G8B8A8: return "PIXEL_FORMAT_R8G8B8A8";
		case PIXEL_FORMAT_R8G8B8: return "PIXEL_FORMAT_R8G8B8";
		case PIXEL_FORMAT_R8: return "PIXEL_FORMAT_R8";
		case PIXEL_FORMAT_R16F: return "PIXEL_FORMAT_R16F";
		case PIXEL_FORMAT_R32F: return "PIXEL_FORMAT_R32F";
	}
	return nullptr;
}

pine::Image::Image()
= default;

pine::Image::~Image()
{
	if (_pixels) {
		stbi_image_free(_pixels);
		_pixels = nullptr;
	}
}

pine::Image::Image(const char * path)
{
	this->Load(path);
}

bool pine::Image::Load(const char * path)
{
	m_path = path;

	// TODO: figure out how to return false if file not loaded
	if (!std::filesystem::exists(m_path)) {
		Logger::Instance().Error("Image file does not exist at path: " + m_path);
		return false;
	}
	// NOTE: maybe use seperate class for loading 
	{
		if (stbi_is_hdr(path)) {
			_pixelFormat = PIXEL_FORMAT_R16F;
			_pixels = stbi_loadf(path, &_width, &_height, &_numColorCh, 0);
		}
		else 
			_pixels = stbi_load(path, &_width, &_height, &_numColorCh, 0);
	}
	ProcessBytes();
	return true;
}

std::string pine::Image::ReadImageExtension(const char* path)
{
	std::filesystem::path p(path);
	std::string file_extension = p.extension().string(); // may include leading '.'
	if (!file_extension.empty() && file_extension[0] == '.') 
		file_extension.erase(0, 1);
	std::ranges::transform(
		file_extension,
file_extension.begin(),
		[](unsigned char c)
		{
			return static_cast<char>(std::tolower(c));
		});
	return file_extension;
}

void pine::Image::ProcessBytes()
{
	// transform monohrome to rgb
	if (_pixelFormat != PIXEL_FORMAT_R32F && _pixelFormat != PIXEL_FORMAT_R16F)
	{
		if (GetNumColorCh() == 1) {
			void* modified_bytes = malloc(_height * _width * 3 * sizeof(unsigned char));
			unsigned char* modified_bytes_char = static_cast<unsigned char*>(modified_bytes);
			for (int i = 0; i < _width * _height; i++) {
				const unsigned char* v = static_cast<unsigned char*>(GetPixels());
				modified_bytes_char[i * 3 + 0] = v[i];
				modified_bytes_char[i * 3 + 1] = v[i];
				modified_bytes_char[i * 3 + 2] = v[i];
			}
			stbi_image_free(_pixels);
			_pixels = modified_bytes;
			_pixelFormat = PIXEL_FORMAT_R8G8B8;
		}
		else if (GetNumColorCh() == 3) {
			_pixelFormat = PIXEL_FORMAT_R8G8B8;
		}
		else if (GetNumColorCh() == 4)
		{
			_pixelFormat = PIXEL_FORMAT_R8G8B8A8;
		}
		else {
			std::cout << "ERROR: Unsupported number of color channels in texture image: " << GetNumColorCh() << "\n";
		}
	}
}

void pine::Image::SoftCopyFrom(const Image& other)
{
	// copy metadata first
	_numColorCh = other._numColorCh;
	_pixelFormat = other._pixelFormat;
}

void pine::Image::SetPixels(void* pixels, unsigned int width, unsigned int height)
{
    if (_pixels) {
        stbi_image_free(_pixels);
        _pixels = nullptr;
    }
    _pixels = pixels;
    _width = static_cast<int>(width);
    _height = static_cast<int>(height);
}
