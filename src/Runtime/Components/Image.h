#pragma once
#include <Utils/Utils.h>

namespace pine {

	class Image {
	public:
		Image();
		explicit Image(const char* path);
		[[nodiscard]] const void* GetPixelsPtr() const;
		inline int GetWidth() const { return _width; };
		inline int GetHeight() const { return _height; };

		bool Create(const char* path);
	private:
		int _width;
		int _height;
		int _numColorCh;

		unsigned char* _bytes;
	};

}