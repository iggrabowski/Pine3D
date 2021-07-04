#pragma once
#include "Platform/SFML/SFMLWindow.h"
#include "Core/Application.h"

namespace Pine {

	SFMLWindow::SFMLWindow(const WindowSettings& windowSettings)
	{
		m_Settings = windowSettings;

		sf::ContextSettings cs;
		cs.depthBits = 24;
		cs.stencilBits = 8;
		cs.antialiasingLevel = 2;
		cs.majorVersion = 4;
		cs.minorVersion = 0;
		cs.attributeFlags = sf::ContextSettings::Default;

		m_Window = new sf::RenderWindow(
			sf::VideoMode(
				m_Settings.Width,
				m_Settings.Height
			),
			m_Settings.Title,
			sf::Style::Resize | sf::Style::Close,
			cs
		);
		m_Window->setVerticalSyncEnabled(m_Settings.VSync);

		m_Window->setActive();
		m_IsActive = true;
		//m_Window->setKeyRepeatEnabled(false);
	}

	SFMLWindow::~SFMLWindow()
	{
		m_Window->close();
		delete m_Window;
	}

	void SFMLWindow::OnUpdate()
	{
		//WindowEvent we = WindowEvent::None;

		//For now SFML window events will be polled here
		//TODO: event dispatchers
		HandleEvents();

		//return we;
	}

	Vec2i SFMLWindow::GetMousePosition()
	{
		sf::Vector2i pos = sf::Mouse::getPosition(*m_Window);
		return Vec2i(pos.x, pos.y);
	}

	Vec2i SFMLWindow::GetSize()
	{
		return Vec2i(m_Settings.Width, m_Settings.Height);
	}

	void SFMLWindow::HandleEvents()
	{
		sf::Event event;
		//bool mouseRightButtonPressed = false;

		while (m_Window->pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				m_Window->close();
				m_IsActive = false;
				break;

				// key pressed
			case sf::Event::Resized:
				std::cout << "ERROR: RESIZED EVENT HANDLING NOT IMPLEMENTED." << std::endl;
				break;

			case sf::Event::MouseWheelMoved:
				/*std::cout << "wheel movement: " << event.mouseWheel.delta << std::endl;
				std::cout << "mouse x: " << event.mouseWheel.x << std::endl;
				std::cout << "mouse y: " << event.mouseWheel.y << std::endl;*/
				controls->Zoom(event.mouseWheel.delta);
				break;

			case sf::Event::MouseMoved:
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					/*std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
					std::cout << "new mouse y: " << event.mouseMove.y << std::endl;*/
					controls->ChangeDirection(m_LastMousePosition.x -  event.mouseMove.x, m_LastMousePosition.y - event.mouseMove.y);
				}
				m_LastMousePosition.x = event.mouseMove.x;
				m_LastMousePosition.y = event.mouseMove.y;
				break;

				// we don't process other types of events
			default:
				break;
			}
		}

		//--------------CONTROLS--------------//
		//Direct device access responses
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			controls->MoveLeft();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			controls->MoveRight();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			controls->MoveUp();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			controls->MoveDown();
		}
	}

	void SFMLWindow::Sleep(float seconds)
	{
		sf::sleep(sf::seconds(seconds));
	}

	void SFMLWindow::Display()
	{
		m_Window->display();
	}

}