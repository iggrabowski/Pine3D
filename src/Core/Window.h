#pragma once
#include "Utils/Utils.h"
//#include "Core/Application.h"

#include <string>

namespace pine {

	//extern class Application;

	////flags for window response
	//enum class WindowEvent : unsigned int {
	//	None = 0,
	//	Closed = 1,
	//	Resized = 1 << 1,
	//	First = Closed,
	//	Last = Resized
	//};

	//constexpr inline WindowEvent operator|(WindowEvent a, WindowEvent b)
	//{
	//	return (enum WindowEvent)((unsigned int)(a) | (unsigned int)(b));
	//}

	//constexpr inline WindowEvent operator&(WindowEvent a, WindowEvent b)
	//{
	//	return (enum WindowEvent)((unsigned int)(a) & (unsigned int)(b));
	//}

	struct WindowSettings {
		const char* title;
		unsigned int width;
		unsigned int height;
		bool v_sync;

		explicit WindowSettings(
			const char title[] = "Pine3D",
			const unsigned int width = 1200,
			const unsigned int height = 900,
			const bool vsync = true
		) : title(title), width(width), height(height), v_sync(vsync) {}
	};

	class Window {
		//friend class Application;
	public:
		virtual ~Window() = default;
		static UniquePtr<Window> Init(const WindowSettings& windowSettings);
		//static Window* s_Instance;

		virtual glm::ivec2 GetMousePosition() = 0;
		virtual glm::ivec2 GetSize() = 0;
		virtual void OnUpdate() = 0;
		//virtual void Display() = 0;
		//virtual void Sleep(float seconds) = 0;
		virtual bool IsOpen() = 0;
	protected:
		WindowSettings _settings;
		bool _isActive = false;
	private:
		//static UniquePtr<Window> Create(const WindowSettings& windowSettings);
	};
		
}