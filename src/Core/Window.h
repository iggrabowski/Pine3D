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
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		bool VSync;

		WindowSettings(
			const std::string& title = "Pine",
			unsigned int width = 1200,
			unsigned int height = 900,
			bool vsync = true
		) : Title(title), Width(width), Height(height), VSync(vsync) {}
	};

	class Window {
		//friend class Application;
	public:
		static UniquePtr<Window> Init(const WindowSettings& windowSettings);
		//static Window* s_Instance;

		virtual Vec2i GetMousePosition() = 0;
		virtual Vec2i GetSize() = 0;
		virtual void OnUpdate() = 0;
		virtual void Display() = 0;
		virtual void Sleep(float seconds) = 0;

		bool GetIsActive();
	protected:
		WindowSettings m_Settings;
		bool m_IsActive;
	private:
		//static UniquePtr<Window> Create(const WindowSettings& windowSettings);
	};
		
}