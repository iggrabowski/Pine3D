#pragma once
#include "Platform/OpenGL/GLFWWindow.h"
#include "Core/Application.h"


namespace Pine {

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		//--------------CONTROLS--------------//
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			inputHandler->MoveLeft();
		}

		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
			inputHandler->MoveRight();
		}

		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
			inputHandler->MoveUp();
		}

		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
			inputHandler->MoveDown();
		}
	}

	GLFWWindow::GLFWWindow(const WindowSettings& windowSettings)
	{
		_settings = windowSettings;
		_LastMousePosition = { 0, 0 };

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
			NULL, 
			NULL
		);

		glfwMakeContextCurrent(_window);

		glfwSetKeyCallback(_window, KeyCallback);
	}

	GLFWWindow::~GLFWWindow()
	{
		glfwTerminate();
		//delete m_Window;
	}

	void GLFWWindow::OnUpdate()
	{
		// Swap buffers
		glfwSwapBuffers(_window);

		// TODO: some actual event handling
		HandleEvents();
	}

	glm::ivec2 GLFWWindow::GetMousePosition()
	{
		double xPos, yPos;
		glfwGetCursorPos(_window, &xPos, &yPos);

		// TODO: check if the values are correct
		glm::ivec2 pos(xPos, yPos);
		return pos;
	}

	glm::ivec2 GLFWWindow::GetSize()
	{
		return glm::ivec2(_settings.width, _settings.height);
	}

	bool GLFWWindow::IsOpen()
	{
		return !glfwWindowShouldClose(_window);
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