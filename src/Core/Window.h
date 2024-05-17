#pragma once
#include "Utils/Utils.h"
//#include "Core/Application.h"

#include <string>

namespace Pine {

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
		bool vSync;

		WindowSettings(
			const char title[] = "Pine3D",
			unsigned int width = 1200,
			unsigned int height = 900,
			bool vsync = true
		) : title(title), width(width), height(height), vSync(vsync) {}
	};

	class Window {
		//friend class Application;
	public:
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
		bool _isActive;
	private:
		//static UniquePtr<Window> Create(const WindowSettings& windowSettings);
	};
		
}