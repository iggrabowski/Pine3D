#pragma once
#include "Platform/OpenGL/GLFWWindow.h"
#include "Core/Application.h"
#include "Utils/Logger.h"


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

void GlfwWindow::Startup()
{
	// Starting up the GLFW window
	Logger::Instance().Info("GLFW Window : starting window...");

	// assign input_handler as window user pointer
	//glfwSetWindowUserPointer(_window, &Application::input_handler);

	// set input callbacks
	// set keyboard callbacks
	glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		float value = 0.0f;
		if (action == GLFW_PRESS) {
			value = 1.0f; // key pressed
		} else if (action == GLFW_RELEASE) {
			value = 0.0f; // key released
		} else if (action == GLFW_REPEAT) {
			value = 1.0f; // key held down
		}
		Application::input_handler->UpdateKeyboardState(0, static_cast<KeyCode>(key), {
			.value = value
		}); 
	});

	// set mouse callbacks
	glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
			float value = 0.0f;
			if (action == GLFW_PRESS) {
				value = 1.0f; // key pressed
			} else if (action == GLFW_RELEASE) {
				value = 0.0f; // key released
			}
			Application::input_handler->UpdateMouseState(0, static_cast<KeyCode>(button), {
				// TODO: does mouse raise GLFW_REPEAT on hold?
				.value = value
			}); 
	});

	// TODO:
	// set mouse position callback
	// set gamepad callbacks
	
	// Register the keyboard as an input device
	const auto default_keyboard = std::make_shared<InputDevice>();
	default_keyboard->index = 0;
	default_keyboard->type = InputDeviceType::KEYBOARD;
	default_keyboard->states = {};
	default_keyboard->state_func = []
	{
		return Application::input_handler->GetKeyboardState();
	};
	Application::input_handler->RegisterDevice(default_keyboard);

	
	const auto default_mouse = std::make_shared<InputDevice>();
	default_mouse->index = 1;
	default_mouse->type = InputDeviceType::MOUSE;
	default_mouse->states = {};

	//NOTE: mouse button codes are kept with the keys in the KeyCodes.h
	default_mouse->state_func = []
	{
		return Application::input_handler->GetMouseState();
	};
	Application::input_handler->RegisterDevice(default_mouse);

	Logger::Instance().Success("GLFW Window : ...startup complete.");
}

void GlfwWindow::RegisterInputCallback(int key, int scancode, int action, int mods)
{
	//glfwGetWindowUserPointer();
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

GLFWwindow* GlfwWindow::GetWindow() const
{
	return _window;
}

glm::ivec2 GlfwWindow::GetMousePosition()
{
	double x_pos, y_pos;
	glfwGetCursorPos(_window, &x_pos, &y_pos);

	// TODO: check if the values are correct
	glm::ivec2 pos(x_pos, y_pos);
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