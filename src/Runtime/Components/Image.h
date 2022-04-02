#pragma once
#include <Utils/Utils.h>

namespace Pine {

	class Image {
	public:
		Image();
		Image(const char* path);
		const void* getPixelsPtr();
		inline int getWidth() const { return m_width; };
		inline int getHeight() const { return m_height; };

		bool Create(const char* path);
	private:
		int m_width;
		int m_height;
		int m_numColorCh;

		unsigned char* m_bytes;
	};

}