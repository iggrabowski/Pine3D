#pragma once

#include "Core/Window.h"
#include "Utils/Utils.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace Pine {
	
	struct SFMLWindowSettings
	{
		sf::ContextSettings contextSettings;
		bool VSync;
	};

	class SFMLWindow : public Window {
	public:
		SFMLWindow(const WindowSettings& windowSettings);
		~SFMLWindow();

		//void Init() override;
		void OnUpdate() override;
		void Sleep(float seconds) override;
		void Display() override;

		Vec2i GetMousePosition() override;
		Vec2i GetSize() override;
	private:
		sf::RenderWindow* m_Window;
		Vec2 m_LastMousePosition;

		void HandleEvents();
	};

}