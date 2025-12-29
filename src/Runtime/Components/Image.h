#pragma once
#include <Utils/Utils.h>

namespace pine {

	class Image {
	public:
		Image();
		~Image();
		explicit Image(const char* path);
		[[nodiscard]] const void* GetPixelsPtr() const;
		[[nodiscard]] const void* GetModifiedPtr() const;
		int GetWidth() const { return _width; };
		int GetHeight() const { return _height; };
		int GetNumColorCh() const { return _numColorCh; };
		unsigned char* GetBytes() const { return _bytes; };

		bool Create(const char* path);
		unsigned char* _modifiedBytes = nullptr; // this is used for 8bit image data, TODO: for node editor purposes textures are all turned 24bit, migh want to dupe 
	private:
		int _width;
		int _height;
		int _numColorCh;

		unsigned char* _bytes = nullptr; }; 
}