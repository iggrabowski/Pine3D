#pragma once
#include <Utils/Utils.h>

namespace Pine {

	class Image {
	public:
		Image();
		Image(const char* path);
		const void* getPixelsPtr();
		inline int getWidth() const { return _width; };
		inline int getHeight() const { return _height; };

		bool Create(const char* path);
	private:
		int _width;
		int _height;
		int _numColorCh;

		unsigned char* m_bytes;
	};

}