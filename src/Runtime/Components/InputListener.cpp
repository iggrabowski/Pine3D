#include "Runtime/Components/InputListener.h"
#include "Core/Application.h"

namespace pine {
	InputListener::InputListener()
	{
		Application::input_handler->AddListener(this);
	}
	InputListener::~InputListener()
	{
		Application::input_handler->RemoveListener(this);
	}
}
