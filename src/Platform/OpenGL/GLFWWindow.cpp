#pragma once
#include "Platform/OpenGL/GLFWWindow.h"
#include "Core/Application.h"


namespace pine {
	GlfwWindow::GlfwWindow()
	{
		_settings = WindowSettings();
		_lastMousePosition = { 0, 0 };
		glfwInit();
		_window = glfwCreateWindow(
			_settings.width, 
			_settings.height,
			_settings.title,
			nullptr,
			nullptr
		);
		glfwMakeContextCurrent(_window);

		//register input devices?
		//add callbacks?
	}

	GlfwWindow::GlfwWindow(const WindowSettings& windowSettings)
	{
		_settings = windowSettings;
		_lastMousePosition = { 0, 0 };

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
		_window = glfwCreateWindow(
			_settings.width, 
			_settings.height,
			_settings.title,
			nullptr,
			nullptr
		);

		glfwMakeContextCurrent(_window);
	}

	GlfwWindow::~GlfwWindow()
	{
		glfwTerminate();
		//delete m_Window;
	}

	void GlfwWindow::OnUpdate()
	{
		// Swap buffers
		glfwSwapBuffers(_window);

		// TODO: some actual event handling
		HandleEvents();
	}

	glm::ivec2 GlfwWindow::GetMousePosition()
	{
		double xPos, yPos;
		glfwGetCursorPos(_window, &xPos, &yPos);

		// TODO: check if the values are correct
		glm::ivec2 pos(xPos, yPos);
		return pos;
	}

	glm::ivec2 GlfwWindow::GetSize()
	{
		return glm::ivec2(_settings.width, _settings.height);
	}

	bool GlfwWindow::IsOpen()
	{
		return !glfwWindowShouldClose(_window);
	}

	void GlfwWindow::HandleEvents()
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