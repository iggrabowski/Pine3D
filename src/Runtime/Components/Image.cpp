#include "Image.h"

// Inlude stb image library
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

Pine::Image::Image()
{

}

Pine::Image::Image(const char * path)
{
	this->Create(path);
}

const void * Pine::Image::getPixelsPtr()
{
	return m_bytes;
}

bool Pine::Image::Create(const char * path)
{
	// TODO: figure out how to return false if file not loaded
	m_bytes = stbi_load(path, &_width, &_height, &_numColorCh, 0);
	return true;
}
