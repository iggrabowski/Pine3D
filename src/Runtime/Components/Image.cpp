#include "Image.h"
#include <filesystem>
#include "utils/Logger.h"

// Include stb image library
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

pine::Image::Image()
= default;

pine::Image::~Image()
{
	if (_bytes) {
		stbi_image_free(_bytes);
		_bytes = nullptr;
	}
	if (m_modifiedBytes) {
		delete[] m_modifiedBytes;
		m_modifiedBytes = nullptr;
	}
}

pine::Image::Image(const char * path)
{
	this->Load(path);
}

const void* pine::Image::GetPixelsPtr() const
{
	return _bytes;
}

const void* pine::Image::GetModifiedPtr() const
{
	return m_modifiedBytes;
}

bool pine::Image::Load(const char * path)
{
	m_path = path;
	// TODO: figure out how to return false if file not loaded
	if (!std::filesystem::exists(m_path)) {
		Logger::Instance().Error("Image file does not exist at path: " + m_path);
		return false;
	}
	_bytes = stbi_load(path, &_width, &_height, &_numColorCh, 0);
	return true;
}
