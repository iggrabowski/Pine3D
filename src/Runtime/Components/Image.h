#pragma once
#include <Utils/Utils.h>

namespace pine {
	enum PixelFormat
	{
		PIXEL_FORMAT_UNKNOWN = 0,
		PIXEL_FORMAT_R8G8B8A8, // 32-bit RGBA
		PIXEL_FORMAT_R8G8B8, // 24-bit RGB
		PIXEL_FORMAT_R8, // 8-bit grayscale (transformed to RGB by default)
		PIXEL_FORMAT_R16F, // 16-bit float
		PIXEL_FORMAT_R32F, // 32-bit float
	};

	const char* enum_to_string(PixelFormat e);
	
	class Image {
	public:
		Image();
		~Image();
		explicit Image(const char* path);
		void SoftCopyFrom(const Image& other); // copy metadata but not pixel data
		[[nodiscard]] int GetWidth() const { return _width; };
		[[nodiscard]] int GetHeight() const { return _height; };
		[[nodiscard]] int GetNumColorCh() const { return _numColorCh; };
		[[nodiscard]] void* GetPixels() { return _pixels; };
		[[nodiscard]] std::string ReadImageExtension(const char* path);
		[[nodiscard]] PixelFormat GetPixelFormat() const { return _pixelFormat; };
		void SetPixels(void* pixels, PixelFormat format, int width, int height, int numColorCh);
		bool Load(const char* path);

	private:
		void ProcessBytes();
		std::string m_path;
		int _width = -1;
		int _height = -1;
		int _numColorCh = -1;
		PixelFormat _pixelFormat = PIXEL_FORMAT_UNKNOWN;

		void* _pixels = nullptr;
		// std::string m_extension; // TODO: might be redundant here
	}; 
}