#pragma once
#include "Utils/Utils.h"
//#include "Core/Application.h"

#include <string>

namespace pine {

	//extern class Application;

	struct WindowSettings {
		const char* title;
		int width;
		int height;
		bool v_sync;

		explicit WindowSettings(
			const char title[] = "Pine3D",
			const int width = 1200,
			const int height = 900,
			const bool vsync = true
		) : title(title), width(width), height(height), v_sync(vsync) {}
	};

	class Window {
		//friend class Application;
	public:
		virtual ~Window() = default;
		static UniquePtr<Window> Init(const WindowSettings& windowSettings);
		virtual void Startup() = 0;
		//virtual void RegisterInputCallback(int key, int scancode, int action, int mods) = 0;
		virtual void SetCursorDisabled(bool hidden) = 0;
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
		bool _cursorDisabled = false;
	private:
		//static UniquePtr<Window> Create(const WindowSettings& windowSettings);
	};
		
}