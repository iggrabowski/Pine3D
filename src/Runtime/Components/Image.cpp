#include "Image.h"

// Inlude stb image library
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

Pine::Image::Image()
{

}

const void * Pine::Image::getPixelsPtr()
{
	return m_bytes;
}

bool Pine::Image::Create(const char * path)
{
	// TODO: figure out how to return false if file not loaded
	m_bytes = stbi_load(path, &m_width, &m_height, &m_numColorCh, 0);
	return true;
}
