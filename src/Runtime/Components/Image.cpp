#include "Image.h"

// Include stb image library
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

pine::Image::Image()
= default;

pine::Image::Image(const char * path)
{
	this->Create(path);
}

const void * pine::Image::GetPixelsPtr() const
{
	return _bytes;
}

bool pine::Image::Create(const char * path)
{
	// TODO: figure out how to return false if file not loaded
	_bytes = stbi_load(path, &_width, &_height, &_numColorCh, 0);
	return true;
}
