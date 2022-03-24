#pragma once
#include "Platform/OpenGL/GLFWWindow.h"
#include "Core/Application.h"

namespace Pine {

	GLFWWindow::GLFWWindow(const WindowSettings& windowSettings)
	{
		m_Settings = windowSettings;

		// TODO: perform these checks:
		///* Initialize the library */
		//if (!glfwInit())
		//	return -1;

		///* Create a windowed mode window and its OpenGL context */
		//window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		//if (!window)
		//{
		//	glfwTerminate();
		//	return -1;
		//}

		// Initialize GLFW
		glfwInit();

		// TODO: vsync settings
		m_Window = glfwCreateWindow(
			m_Settings.Width, 
			m_Settings.Height,
			m_Settings.Title, 
			NULL, 
			NULL
		);

		glfwMakeContextCurrent(m_Window);
	}

	GLFWWindow::~GLFWWindow()
	{
		glfwTerminate();
		delete m_Window;
	}

	void GLFWWindow::OnUpdate()
	{
		// Swap buffers
		glfwSwapBuffers(m_Window);

		// TODO: some actual event handling
		HandleEvents();
	}

	Vec2i GLFWWindow::GetMousePosition()
	{
		double xPos, yPos;
		glfwGetCursorPos(m_Window, &xPos, &yPos);

		// TODO: check if the values are correct
		Vec2i pos(xPos, yPos);
		return pos;
	}

	Vec2i GLFWWindow::GetSize()
	{
		return Vec2i(m_Settings.Width, m_Settings.Height);
	}

	bool GLFWWindow::IsOpen()
	{
		return !glfwWindowShouldClose(m_Window);
	}

	void GLFWWindow::HandleEvents()
	{
		glfwPollEvents();
		//sf::Event event;
		////bool mouseRightButtonPressed = false;

		//while (m_Window->pollEvent(event))
		//{
		//	// check the type of the event...
		//	switch (event.type)
		//	{
		//		// window closed
		//	case sf::Event::Closed:
		//		m_Window->close();
		//		m_IsActive = false;
		//		break;

		//		// key pressed
		//	case sf::Event::Resized:
		//		std::cout << "ERROR: RESIZED EVENT HANDLING NOT IMPLEMENTED." << std::endl;
		//		break;

		//	case sf::Event::MouseWheelMoved:
		//		/*std::cout << "wheel movement: " << event.mouseWheel.delta << std::endl;
		//		std::cout << "mouse x: " << event.mouseWheel.x << std::endl;
		//		std::cout << "mouse y: " << event.mouseWheel.y << std::endl;*/
		//		controls->Zoom(event.mouseWheel.delta);
		//		break;

		//	case sf::Event::MouseMoved:
		//		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		//		{
		//			/*std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
		//			std::cout << "new mouse y: " << event.mouseMove.y << std::endl;*/
		//			controls->ChangeDirection(m_LastMousePosition.x -  event.mouseMove.x, m_LastMousePosition.y - event.mouseMove.y);
		//		}
		//		m_LastMousePosition.x = event.mouseMove.x;
		//		m_LastMousePosition.y = event.mouseMove.y;
		//		break;

		//		// we don't process other types of events
		//	default:
		//		break;
		//	}
		//}

		////--------------CONTROLS--------------//
		////Direct device access responses
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		//{
		//	controls->MoveLeft();
		//}

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		//{
		//	controls->MoveRight();
		//}

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		//{
		//	controls->MoveUp();
		//}

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		//{
		//	controls->MoveDown();
		//}
	}

	/*void GLFWWindow::Sleep(float seconds)
	{
		sf::sleep(sf::seconds(seconds));
	}*/

}